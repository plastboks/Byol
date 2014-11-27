/**
 * Lispy main source file.
 *
 * @filename: lispy.c
 *
 * @version: 0.15
 *
 * @date: 2014-11-04
 *
 * @description: Lispy main source code file.
 *
 * @author: Alexander Skjolden
 *
 * @webpage: https://github.com/plastboks/Lispy
 *
 * This file is part of Lispy.
 *
 * Lispy is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Lispy is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Lispy.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "mpc.h"
#include "func.h"
#include "colors.h"
#include "lispy.h"

lval* lval_fun(lbuiltin builtin)
{
    lval* v = malloc(sizeof(lval));
    v->type = LVAL_FUN;
    v->builtin = builtin;
    return v;
}

lval* lval_lambda(lval* formals, lval* body)
{
    lval* v = malloc(sizeof(lval));
    v->type = LVAL_FUN;

    v->builtin = NULL;

    v->env = lenv_new();
    v->formals = formals;
    v->body = body;
    return v;
}

lval* lval_bool(int val) {
    lval* v = malloc(sizeof(lval));
    v->type = LVAL_BOOL;
    v->bool = val;

    return v;
}

lval* lval_num(long x)
{
    lval* v = malloc(sizeof(lval));
    v->type = LVAL_NUM;
    v->num = x;
    return v;
}

lval* lval_dec(double x)
{
    lval* v = malloc(sizeof(lval));
    v->type = LVAL_DEC;
    v->decimal = x;
    return v;
}

lval* lval_str(char* s)
{
    lval* v = malloc(sizeof(lval));
    v->type = LVAL_STR;
    v->str = malloc(strlen(s) + 1);
    strcpy(v->str, s);
    return v;
}

lval* lval_err(char* fmt, ...)
{
    lval* v = malloc(sizeof(lval));
    v->type = LVAL_ERR;

    va_list va;
    va_start(va, fmt);

    v->err = malloc(512);

    vsnprintf(v->err, 511, fmt, va);

    v->err = realloc(v->err, strlen(v->err)+1);

    va_end(va);

    return v;
}

lval* lval_sym(char* s)
{
    lval* v = malloc(sizeof(lval));
    v->type = LVAL_SYM;
    v->sym = malloc(strlen(s) + 1);
    strcpy(v->sym, s);
    return v;
}

lval* lval_sexpr(void)
{
    lval* v = malloc(sizeof(lval));
    v->type = LVAL_SEXPR;
    v->count = 0;
    v->cell = NULL;
    return v;
}

lval* lval_qexpr(void)
{
    lval* v = malloc(sizeof(lval));
    v->type = LVAL_QEXPR;
    v->count = 0;
    v->cell = NULL;
    return v;
}

lval* lval_add(lval* v, lval* x)
{
    v->count++;
    v->cell = realloc(v->cell, sizeof(lval*) * v->count);
    v->cell[v->count-1] = x;
    return v;
}

lval* lval_read_num(mpc_ast_t* t)
{
    errno = 0;
    long x = strtol(t->contents, NULL, 10);
    return errno != ERANGE ? lval_num(x) : lval_err("invalid number");
}

lval* lval_read_dec(mpc_ast_t* t)
{
    errno = 0;
    double x = strtod(t->contents, NULL);
    return errno != ERANGE ? lval_dec(x) : lval_err("invalid number");
}

lval* lval_read_range(mpc_ast_t* t)
{
    long y = strtol(strstr(t->contents, "..") + 2, NULL, 10);
    long x = strtol(strrev(strstr(strrev(t->contents), "..") + 2), NULL, 10);
    return lval_err("%li + %li", x, y);
}

lval* lval_read_str(mpc_ast_t* t)
{
    t->contents[strlen(t->contents) - 1] = '\0';
    char* unescaped = malloc(strlen(t->contents + 1) + 1);
    strcpy(unescaped, t->contents + 1);

    unescaped = mpcf_unescape(unescaped);

    lval* str = lval_str(unescaped);

    free(unescaped);
    return str;
}

lval* lval_read(mpc_ast_t* t)
{
    if (strstr(t->tag, "number")) { return lval_read_num(t); }
    if (strstr(t->tag, "decimal")) { return lval_read_dec(t); }
    if (strstr(t->tag, "range")) { return lval_read_range(t); }
    if (strstr(t->tag, "string")) { return lval_read_str(t); }
    if (strstr(t->tag, "symbol")) { return lval_sym(t->contents); }

    lval* x = NULL;
    if (strcmp(t->tag, ">") == 0) { x = lval_sexpr(); }
    if (strstr(t->tag, "sexpr")) { x = lval_sexpr(); }
    if (strstr(t->tag, "qexpr")) { x = lval_qexpr(); }

    for (int i = 0; i < t->children_num; i++) {
        if (strcmp(t->children[i]->contents, "(") == 0) { continue; }
        if (strcmp(t->children[i]->contents, ")") == 0) { continue; }
        if (strcmp(t->children[i]->contents, "{") == 0) { continue; }
        if (strcmp(t->children[i]->contents, "}") == 0) { continue; }
        if (strcmp(t->children[i]->tag, "regex") == 0) { continue; }
        if (strstr(t->children[i]->tag, "comment")) { continue; }
        x = lval_add(x, lval_read(t->children[i]));
    }

    return x;
}

lval* lval_copy(lval* v)
{
    lval* x = malloc(sizeof(lval));
    x->type = v->type;
    x->is_builtin = v->is_builtin;

    switch (v->type) {
        case LVAL_FUN:
            if (v->builtin) {
                x->builtin = v->builtin;
            } else {
                x->builtin = NULL;
                x->env = lenv_copy(v->env);
                x->formals = lval_copy(v->formals);
                x->body = lval_copy(v->body);
            }
            break;
        case LVAL_NUM:
            x->num = v->num;
            break;
        case LVAL_DEC:
            x->decimal = v->decimal;
            break;
        case LVAL_BOOL:
            x->bool = v->bool;
            break;
        case LVAL_STR:
            x->str = malloc(strlen(v->str) + 1);
            strcpy(x->str, v->str);
            break;
        case LVAL_ERR:
            x->err = malloc(strlen(v->err) + 1);
            strcpy(x->err, v->err);
            break;
        case LVAL_SYM:
            x->sym = malloc(strlen(v->sym) + 1);
            strcpy(x->sym, v->sym);
            break;
        case LVAL_SEXPR:
        case LVAL_QEXPR:
            x->count = v->count;
            x->cell = malloc(sizeof(lval*) * x->count);
            for (int i = 0; i < x->count; i++) {
                x->cell[i] = lval_copy(v->cell[i]);
            }
            break;
    }

    return x;
}

lval* lval_call(lenv* e, lval* f, lval* a)
{
    if (f->builtin) {
        return f->builtin(e, a);
    }

    int given = a->count;
    int total = f->formals->count;

    while (a->count) {
        if (f->formals->count == 0) {
            lval_del(a);
            return lval_err("Function passed to many arguments. Got %i, expected %i",
                    given, total);
        }

        lval* sym = lval_pop(f->formals, 0);

        if (strcmp(sym->sym, "&") == 0) {
            if (f->formals->count != 1) {
                lval_del(a);
                return lval_err("Function format is invalid. Symbol '&' not followed\
                        by single symbol.");
            }

            lval* nsym = lval_pop(f->formals, 0);
            lenv_put(f->env, nsym, builtin_list(e, a));
            lval_del(sym);
            lval_del(nsym);
            break;
        }
        lval* val = lval_pop(a, 0);

        lenv_put(f->env, sym, val);

        lval_del(sym);
        lval_del(val);
    }

    lval_del(a);

    if (f->formals->count > 0 &&
        strcmp(f->formals->cell[0]->sym, "&") == 0) {

        if (f->formals->count != 2) {
            return lval_err("Function format invalid. Symbol '&' not followed\
                    by single symbol");
        }
        lval_del(lval_pop(f->formals, 0));

        lval* sym = lval_pop(f->formals, 0);
        lval* val = lval_qexpr();

        lenv_put(f->env, sym, val);
        lval_del(sym);
        lval_del(val);
    }

    if (f->formals->count == 0) {
        f->env->par = e;
        return builtin_eval(f->env, lval_add(lval_sexpr(), lval_copy(f->body)));
    } else {
        return lval_copy(f);
    }
}

int lval_eq(lval* x, lval* y)
{
    if (x->type != y->type) {
        return 0;
    }

    switch (x->type) {
        case LVAL_NUM:
            return (x->num == y->num);
        case LVAL_STR:
            return (strcmp(x->str, y->str) == 0);
        case LVAL_BOOL:
            return (x->bool == y->bool);
        case LVAL_SYM:
            return (strcmp(x->sym, y->sym) == 0);
        case LVAL_ERR:
            return (strcmp(x->err, y->err) == 0);
        case LVAL_FUN:
            if (x->builtin || y->builtin) {
                return x->builtin == y->builtin;
            } else {
                return lval_eq(x->formals, y->formals)
                    && lval_eq(x->body, y->body);
            }
        case LVAL_QEXPR:
        case LVAL_SEXPR:
            if (x->count != y->count) {
                return 0;
            }
            for (int i = 0; i < x->count; i++) {
                if (!(lval_eq(x->cell[i], y->cell[i]))) {
                    return 0;
                }
            }
            return 1;
        break;
    }
    return 0;
}

lval* lenv_get(lenv* e, lval* k)
{
    /* Iterate over all items in the env */
    for (int i = 0; i < e->count; i++) {
        /**
         * Check if the stored string matches the symbol string.
         * If it does, return a copy of the value.
         */
        if (strcmp(e->syms[i], k->sym) == 0) {
            return lval_copy(e->vals[i]);
        }
    }

    if (e->par) {
        return lenv_get(e->par, k);
    } else {
        return lval_err("Unbound symbol '%s'", k->sym);
    }
}

lval* lval_builtin(lbuiltin func)
{
    lval* v = malloc(sizeof(lval));
    v->type = LVAL_FUN;
    v->builtin = func;
    return v;
}

lenv* lenv_new(void)
{
    lenv* e = malloc(sizeof(lenv));
    e->par = NULL;
    e->count = 0;
    e->syms = NULL;
    e->vals = NULL;
    return e;
}

lenv* lenv_copy(lenv* e)
{
    lenv* n = malloc(sizeof(lenv));
    n->par = e->par;
    n->count = e->count;
    n->syms = malloc(sizeof(char*) * n->count);
    n->vals = malloc(sizeof(lval*) * n->count);

    for (int i = 0; i < e->count; i++) {
        n->syms[i] = malloc(strlen(e->syms[i]) + 1);
        strcpy(n->syms[i], e->syms[i]);
        n->vals[i] = lval_copy(e->vals[i]);
    }

    return n;
}

void lenv_def(lenv* e, lval* k, lval* v)
{
    /* Iterate till e has no parent */
    while (e->par) {
        e = e->par;
    }
    lenv_put(e, k, v);
}

char* ltype_name(int t)
{
    switch (t) {
        case LVAL_FUN: return "Function";
        case LVAL_NUM: return "Integer number";
        case LVAL_DEC: return "Decimal number";
        case LVAL_STR: return "String";
        case LVAL_ERR: return "Error";
        case LVAL_SYM: return "Symbol";
        case LVAL_SEXPR: return "S-Expression";
        case LVAL_QEXPR: return "Q-Expression";
        case LVAL_BOOL: return "Boolean";
        default: return "Unknown";
    }
}

void lenv_put(lenv* e, lval* k, lval* v)
{
    /**
     * Iterate over all items in the environment.
     * This is to see if the variable already exists.
     */
    for (int i = 0; i < e->count; i++) {
        /**
         * If variable is found, delete item at that position,
         * and replace it with variable supplied.
         */
        if (strcmp(e->syms[i], k->sym) == 0) {
            lval_del(e->vals[i]);
            e->vals[i] = lval_copy(v);
            return;
        }
    }

    /* No match found */
    e->count++;
    e->vals = realloc(e->vals, sizeof(lval*) * e->count);
    e->syms = realloc(e->syms, sizeof(char*) * e->count);

    /* Copy contents of lval and symbol into new location */
    e->vals[e->count - 1] = lval_copy(v);
    e->syms[e->count - 1] = malloc(strlen(k->sym) + 1);
    strcpy(e->syms[e->count - 1], k->sym);
}

void lenv_del(lenv* e)
{
    for (int i = 0; i < e->count; i++) {
        free(e->syms[i]);
        lval_del(e->vals[i]);
    }
    free(e->syms);
    free(e->vals);
    free(e);
}

void lval_del(lval* v)
{
    switch (v->type) {
        case LVAL_BOOL:
        case LVAL_DEC:
        case LVAL_NUM:
            break;
        case LVAL_ERR:
            free(v->err);
            break;
        case LVAL_SYM:
            free(v->sym);
            break;
        case LVAL_STR:
            free(v->str);
            break;
        case LVAL_QEXPR:
        case LVAL_SEXPR:
            for (int i = 0; i < v->count; i++) {
                lval_del(v->cell[i]);
            }
            free(v->cell);
            break;
        case LVAL_FUN:
            if (!v->builtin) {
                lenv_del(v->env);
                lval_del(v->formals);
                lval_del(v->body);
            }
            break;
    }
    free(v);
}

void lval_print_str(lval* v)
{
    char* escaped = malloc(strlen(v->str) + 1);

    strcpy(escaped, v->str);

    escaped = mpcf_escape(escaped);

    printf("\"%s\"", escaped);

    free(escaped);
}

void lval_print(lval* v)
{
    switch (v->type) {
        case LVAL_NUM:
            printf("%li", v->num);
            break;
        case LVAL_DEC:
            printf("%f", v->decimal);
            break;
        case LVAL_ERR:
            printf("Error: %s", v->err);
            break;
        case LVAL_STR:
            lval_print_str(v);
            break;
        case LVAL_BOOL:
            printf("%s", v->bool ? "True" : "False");
            break;
        case LVAL_SYM:
            printf("%s", v->sym);
            break;
        case LVAL_SEXPR:
            lval_expr_print(v, '(', ')');
            break;
        case LVAL_QEXPR:
            lval_expr_print(v, '{', '}');
            break;
        case LVAL_FUN:
            if (v->builtin) {
                printf("<function>");
            } else {
                printf("(\\ ");
                lval_print(v->formals);
                putchar(' ');
                lval_print(v->body);
                putchar(')');
            }
            break;
    }
}

void lval_expr_print(lval* v, char open, char close)
{
    putchar(open);
    for (int i = 0; i < v->count; i++) {
        lval_print(v->cell[i]);

        if (i != (v->count-1)) {
            putchar(' ');
        }
    }
    putchar(close);
}

void lval_println(lval* v)
{
    lval_print(v);
    putchar('\n');
}

lval* lval_eval_sexpr(lenv*e, lval* v)
{
    /* Evaluate children */
    for (int i = 0; i < v->count; i++) {
        v->cell[i] = lval_eval(e, v->cell[i]);
    }

    /* Error checking */
    for (int i = 0; i < v->count; i++) {
        if (v->cell[i]->type == LVAL_ERR) {
            return lval_take(v, i);
        }
    }

    /* Empty expression */
    if (v->count == 0) { return v; }

    /* Single expression */
    if (v->count == 1) { return lval_eval(e, lval_take(v, 0)); }

    /* Ensure first element is symbol */
    lval* f = lval_pop(v, 0);
    if (f->type != LVAL_FUN) {
        lval* err = lval_err(
                "S-Expression starts with incorrect type. Got %s, expected %s.",
                ltype_name(f->type), ltype_name(LVAL_FUN));
        lval_del(v);
        lval_del(f);
        return err;
    }

    /* Call builtin with operator */
    lval* result = lval_call(e, f, v);
    lval_del(f);
    return result;
}

lval* lval_eval(lenv* e, lval* v)
{
    if (v->type == LVAL_SYM) {
        lval* x = lenv_get(e, v);
        lval_del(v);
        return x;
    }
    if (v->type == LVAL_SEXPR) {
        return lval_eval_sexpr(e, v);
    }
    return v;
}

lval* lval_pop(lval* v, int i)
{
    lval* x = v->cell[i];
    
    /* Shift the memory following the item at "i" over the top if it */
    memmove(&v->cell[i], &v->cell[i+1], sizeof(lval*) * (v->count-i-1));

    v->count--;

    v->cell = realloc(v->cell, sizeof(lval*) * v->count);

    return x;
}

lval* lval_take(lval* v, int i)
{
    lval* x = lval_pop(v, i);
    lval_del(v);
    return x;
}

lval* lval_join(lval* x, lval* y)
{
    /* for each cell in y, add it to x */
    while (y->count) {
        x = lval_add(x, lval_pop(y, 0));
    }

    lval_del(y);
    return x;
}

lval* builtin_head(lenv* e, lval* a)
{
    /* Check error conditions */
    LASSERT_NUM("head", a, 1);
    LASSERT_TYPE("head", a, 0, LVAL_QEXPR);
    LASSERT_NOT_EMPTY("head", a, 0);

    lval* v = lval_take(a, 0);

    while (v->count > 1) {
        lval_del(lval_pop(v, 1));
    }
    return v;
}

lval* builtin_tail(lenv* e, lval* a)
{
    /* check error conditions */
    LASSERT_NUM("tail", a, 1);
    LASSERT_TYPE("tail", a, 0, LVAL_QEXPR);
    LASSERT_NOT_EMPTY("tail", a, 0);

    lval* v = lval_take(a, 0);

    lval_del(lval_pop(v, 0));
    return v;
}

lval* builtin_cons(lenv* e, lval* a)
{
    /* check error conditions */
    LASSERT_NUM("cons", a, 2);
    LASSERT_TYPE("cons", a, 0, LVAL_NUM);
    LASSERT_TYPE("cons", a, 1, LVAL_QEXPR);
    LASSERT_NOT_EMPTY("cons", a, 0);

    lval* x = lval_qexpr();
    x = lval_add(x, lval_pop(a, 0));
    x = lval_join(x, lval_pop(a, 0));

    lval_del(a);
    return x;
}

lval* builtin_take(lenv* e, lval* a)
{
    /* check error conditions */
    LASSERT_NUM("take", a, 2);
    LASSERT_TYPE("take", a, 0, LVAL_NUM);
    LASSERT_TYPE("take", a, 1, LVAL_QEXPR);
    LASSERT_NOT_EMPTY("take", a, 0);

    lval* c = lval_pop(a, 0);
    lval* v = lval_pop(a, 0);

    if (c->num < v->count) {
        for (int i = v->count - 1; i >= c->num; i--) {
            lval_del(lval_pop(v, i));
        }
    }

    lval_del(a);
    lval_del(c);
    return v;
}

lval* builtin_drop(lenv* e, lval* a)
{
    /* check error conditions */
    LASSERT_NUM("drop", a, 2);
    LASSERT_TYPE("drop", a, 0, LVAL_NUM);
    LASSERT_TYPE("drop", a, 1, LVAL_QEXPR);
    LASSERT_NOT_EMPTY("drop", a, 0);

    lval* c = lval_pop(a, 0);
    lval* v = lval_pop(a, 0);

    if (c->num > v->count) { c->num = v->count; }

    for (int i = 0; i < c->num; i++) {
        lval_del(lval_pop(v, 0));
    }

    lval_del(a);
    lval_del(c);
    return v;
}

lval* builtin_rev(lenv* e, lval* a)
{
    /* check error conditions */
    LASSERT_NUM("rev", a, 1);
    LASSERT_TYPE("rev", a, 0, LVAL_QEXPR);
    LASSERT_NOT_EMPTY("rev", a, 0);

    lval* x = lval_qexpr();
    lval* v = lval_pop(a, 0);

    for (int i = v->count - 1; i >= 0; i--) {
        x = lval_add(x, lval_pop(v, i));
    }

    lval_del(a);
    lval_del(v);
    return x;
}

lval* builtin_sort(lenv* e, lval* a)
{
    /* check error conditions */
    LASSERT_NUM("sort", a, 1);
    LASSERT_TYPE("sort", a, 0, LVAL_QEXPR);
    LASSERT_NOT_EMPTY("sort", a, 0);

    lval* v = lval_pop(a, 0);

    int intcmp(const void *a, const void *b)
    {
        const int *ia = (int *)a, *ib = (int *)b;
        return *ia - *ib;
    }

    //qsort(array, array_count, sizeof(array[0]), intcmp);

    return lval_err("Not implemented yet...");

    lval_del(a);
    return v;
}

lval* builtin_last(lenv* e, lval* a)
{
    /* check error conditions */
    LASSERT_NUM("last", a, 1);
    LASSERT_TYPE("last", a, 0, LVAL_QEXPR);
    LASSERT_NOT_EMPTY("last", a, 0);

    lval* v = lval_take(a, 0);

    while (v->count > 1) {
        lval_del(lval_pop(v, 0));
    }

    return v;
}

lval* builtin_list(lenv* e, lval* a)
{
    a->type = LVAL_QEXPR;
    return a;
}

lval* builtin_eval(lenv* e, lval* a)
{
    LASSERT_NUM("eval", a, 1);
    LASSERT_TYPE("eval", a, 0, LVAL_QEXPR);

    lval* x = lval_take(a, 0);
    x->type = LVAL_SEXPR;
    return lval_eval(e, x);
}

lval* builtin_join(lenv* e, lval* a)
{
    for (int i = 0; i < a->count; i++) {
        LASSERT_TYPE("join", a, i, LVAL_QEXPR);
    }

    lval* x = lval_pop(a, 0);

    while (a->count) {
        x = lval_join(x, lval_pop(a, 0));
    }

    lval_del(a);
    return x;
}

/* get the length of an list */
lval* builtin_len(lenv* e, lval* a)
{
    /* Check error conditions */
    LASSERT_NUM("len", a, 1);
    LASSERT_TYPE("len", a, 0, LVAL_QEXPR);
    LASSERT_NOT_EMPTY("len", a, 0);

    /* pop out the first element */
    lval* v = lval_take(a, 0);

    int count;
    while(v->count > 1) {
        lval_del(lval_pop(v, 1));
        count++;
    }

    v->cell[0]->num = count;

    return v;
}

lval* builtin_cmp(lenv* e, lval* a, char* op)
{
    LASSERT_NUM(op, a, 2);
    int r;
    if (strcmp(op, "==") == 0) {
        r = lval_eq(a->cell[0], a->cell[1]);
    }
    if (strcmp(op, "!=") == 0) {
        r = !lval_eq(a->cell[0], a->cell[1]);
    }
    if (strcmp(op, "&&") == 0) {
    }
    lval_del(a);
    return lval_bool(r);
}

lval* builtin_eq(lenv* e, lval* a)
{
    return builtin_cmp(e, a, "==");
}

lval* builtin_ne(lenv* e, lval* a)
{
    return builtin_cmp(e, a, "!=");
}

lval* builtin_and(lenv* e, lval* a)
{
    LASSERT_NUM("&&", a, 2);
    LASSERT_TYPE("&&", a, 0, LVAL_BOOL);
    LASSERT_TYPE("&&", a, 1, LVAL_BOOL);

    int r = a->cell[0]->bool && a->cell[1]->bool;

    lval_del(a);
    return lval_bool(r);
}

lval* builtin_or(lenv* e, lval* a)
{
    LASSERT_NUM("||", a, 2);
    LASSERT_TYPE("||", a, 0, LVAL_BOOL);
    LASSERT_TYPE("||", a, 1, LVAL_BOOL);

    int r = a->cell[0]->bool || a->cell[1]->bool;

    lval_del(a);
    return lval_bool(r);
}

lval* builtin_not(lenv* e, lval* a)
{
    LASSERT_NUM("!", a, 1);
    LASSERT_TYPE("!", a, 0, LVAL_BOOL);

    int r = a->cell[0]->bool;
    lval_del(a);
    return lval_bool(!r);
}

lval* builtin_if(lenv* e, lval* a)
{
    LASSERT_NUM("if", a, 3);
    LASSERT_TYPE("if", a, 0, LVAL_BOOL);
    LASSERT_TYPE("if", a, 1, LVAL_QEXPR);
    LASSERT_TYPE("if", a, 2, LVAL_QEXPR);

    lval* x;
    a->cell[1]->type = LVAL_SEXPR;
    a->cell[2]->type = LVAL_SEXPR;

    if (a->cell[0]->bool) {
        x = lval_eval(e, lval_pop(a, 1));
    } else {
        x = lval_eval(e, lval_pop(a, 2));
    }

    lval_del(a);
    return x;
}

/* pop out the last element */
lval* builtin_init(lenv* e, lval* a)
{
    /* Check error conditions */
    LASSERT_NUM("init", a, 1);
    LASSERT_TYPE("init", a, 0, LVAL_QEXPR);
    LASSERT_NOT_EMPTY("init", a, 0);

    lval* v = lval_take(a ,0);

    lval_del(lval_pop(v, v->count -1));

    return v;
}

lval* builtin_sum(lenv* e, lval* a)
{
    /* Check error conditions */
    LASSERT_NUM("sum", a, 1);
    LASSERT_TYPE("sum", a, 0, LVAL_QEXPR);
    LASSERT_NOT_EMPTY("sum", a, 0);

    lval* v = lval_pop(a, 0);
    lval_del(a);
    return builtin_op(e, v, "+");
}

lval* builtin_prod(lenv* e, lval* a)
{
    /* Check error conditions */
    LASSERT_NUM("prod", a, 1);
    LASSERT_TYPE("prod", a, 0, LVAL_QEXPR);
    LASSERT_NOT_EMPTY("prod", a, 0);

    lval* v = lval_pop(a, 0);
    lval_del(a);
    return builtin_op(e, v, "*");
}

lval* builtin_nth(lenv* e, lval* a)
{
    /* Check error conditions */
    LASSERT_NUM("nth", a, 2);
    LASSERT_TYPE("nth", a, 0, LVAL_NUM);
    LASSERT_TYPE("nth", a, 1, LVAL_QEXPR);
    LASSERT_NOT_EMPTY("nth", a, 0);

    lval* n = lval_qexpr();
    lval* c = lval_pop(a, 0);
    lval* v = lval_pop(a, 0);

    if (c->num < v->count) {
        n = lval_add(n, lval_pop(v, c->num));
    }

    lval_del(v);
    lval_del(c);
    lval_del(a);
    return n;
}

lval* builtin_lambda(lenv* e, lval* a)
{
    LASSERT_NUM("\\", a, 2);
    LASSERT_TYPE("\\", a, 0, LVAL_QEXPR);
    LASSERT_TYPE("\\", a, 1, LVAL_QEXPR);

    for (int i = 0; i < a->cell[0]->count; i++) {
        LASSERT(a, (a->cell[0]->cell[i]->type == LVAL_SYM),
                "Cannot define non-symbol. Got %s, expected %s.",
                ltype_name(a->cell[0]->cell[i]->type), ltype_name(LVAL_SYM));
    }

    lval* formals = lval_pop(a, 0);
    lval* body = lval_pop(a, 0);
    lval_del(a);

    return lval_lambda(formals, body);
}

lval* builtin_var(lenv* e, lval* a, char* func)
{
    LASSERT_TYPE(func, a, 0, LVAL_QEXPR);

    lval* syms = a->cell[0];
    for (int i = 0; i < syms->count; i++) {
        LASSERT(a, (syms->cell[i]->type == LVAL_SYM),
                "Function '%s' cannot define non-symbol. Got %s, expected %s.",
                func, ltype_name(syms->cell[i]->type), ltype_name(LVAL_SYM));
    }

    LASSERT(a, (syms->count == a->count - 1),
            "Function '%s' passed to many arguments for symbols. Got %i, expected %i",
            func, syms->count, a->count - 1);

    for (int i = 0; i< syms->count; i++) {
        if (strcmp(func, "def") == 0) {
            lenv_def(e, syms->cell[i], a->cell[i+1]);
        }
        if (strcmp(func, "=") == 0) {
            lenv_put(e, syms->cell[i], a->cell[i+1]);
        }
    }

    lval_del(a);
    return lval_sexpr();
}

lval* builtin_def(lenv* e, lval* a)
{
    return builtin_var(e, a, "def");
}

lval* builtin_put(lenv* e, lval* a) {
    return builtin_var(e, a, "=");
}

lval* builtin_env(lenv* e, lval* a)
{
    for (int i = 0; i < e->count; i++) {
        printf("%s\n", e->syms[i]);
    }
    return lval_pop(a, 0);
}

lval* builtin_add(lenv* e, lval* a)
{
    return builtin_op(e, a, "+");
}

lval* builtin_sub(lenv* e, lval* a)
{
    return builtin_op(e, a, "-");
}

lval* builtin_mul(lenv* e, lval* a)
{
    return builtin_op(e, a, "*");
}

lval* builtin_div(lenv* e, lval* a)
{
    return builtin_op(e, a, "/");
}

lval* builtin_mod(lenv* e, lval* a)
{
    return builtin_op(e, a, "%");
}

lval* builtin_pow(lenv* e, lval* a)
{
    return builtin_op(e, a, "^");
}

lval* builtin_min(lenv* e, lval* a)
{
    return builtin_op(e, a, "min");
}

lval* builtin_max(lenv* e, lval* a)
{
    return builtin_op(e, a, "max");
}

lval* builtin_op(lenv* e, lval* a, char* op)
{
    /* Ensure all arguments are numbers */
    for (int i = 0; i < a->count; i++) {
        if (a->cell[i]->type != LVAL_NUM && a->cell[i]->type != LVAL_DEC) {
            lval_del(a);
            return lval_err("Cannot operate on non-number. Integer\
                    or Decimal number expected");
        }
    }

    /* Pop the first element */
    lval* x = lval_pop(a, 0);

    if ((strcmp(op, "-") == 0) && (a->count == 0)) { 
        if (x->type == LVAL_NUM) x->num = -x->num;
        if (x->type == LVAL_DEC) x->decimal = -x->decimal;
    }

    while (a->count > 0) {
        lval* y = lval_pop(a, 0);

        if (x->type == LVAL_NUM && y->type == LVAL_NUM) {
            /* Operations */
            if (strcmp(op, "+") == 0) { x->num += y->num; }
            if (strcmp(op, "-") == 0) { x->num -= y->num; }
            if (strcmp(op, "*") == 0) { x->num *= y->num; }
            if (strcmp(op, "%") == 0) { x->num = x->num % y->num; }
            if (strcmp(op, "^") == 0) { x->num = pow(x->num, y->num); }
            if (strcmp(op, "min") == 0) { x->num = min(x->num, y->num); }
            if (strcmp(op, "max") == 0) { x->num = max(x->num, y->num); }
            if (strcmp(op, "/") == 0) {
                if (y->num == 0) {
                    lval_del(x); lval_del(y);
                    x = lval_err("Division by zero!");
                    break;
                }
                x->num /= y->num;
            }
        } else {
            /* One of the operands is a notnum */
            if (x->type == LVAL_DEC && y->type == LVAL_NUM) {
                y->type = LVAL_DEC;
                y->decimal = (double)(y->num);
            } else if (x->type == LVAL_NUM && y->type == LVAL_DEC) {
                x->type = LVAL_DEC;
                x->decimal = (double)(x->num);
            }
            /* Operations */
            if (strcmp(op, "+") == 0) { x->decimal += y->decimal; }
            if (strcmp(op, "-") == 0) { x->decimal -= y->decimal; }
            if (strcmp(op, "*") == 0) { x->decimal *= y->decimal; }
            if (strcmp(op, "%") == 0) { x->decimal = fmod(x->decimal, y->decimal); }
            if (strcmp(op, "^") == 0) { x->decimal = pow(x->decimal, y->decimal); }
            if (strcmp(op, "min") == 0) { x->decimal = fmin(x->decimal, y->decimal); }
            if (strcmp(op, "max") == 0) { x->decimal = fmax(x->decimal, y->decimal); }
            if (strcmp(op, "/") == 0) {
                if (y->decimal == 0) {
                    lval_del(x); lval_del(y);
                    x = lval_err("Division by zero!");
                    break;
                }
                x->decimal /= y->decimal;
            }
        }

        /* Delete y element */
        lval_del(y);
    }

    /* Delete input expression and return result */
    lval_del(a);
    return x;
}

lval* builtin_gt(lenv* e, lval* a)
{
    return builtin_ord(e, a, ">");
}

lval* builtin_lt(lenv* e, lval* a)
{
    return builtin_ord(e, a, "<");
}

lval* builtin_ge(lenv* e, lval* a)
{
    return builtin_ord(e, a, "<=");
}

lval* builtin_le(lenv* e, lval* a)
{
    return builtin_ord(e, a, ">=");
}

lval* builtin_ord(lenv* e, lval* a, char* op)
{
    LASSERT_NUM(op, a, 2);
    LASSERT_TYPE(op, a, 0, LVAL_NUM);
    LASSERT_TYPE(op, a, 1, LVAL_NUM);

    int r;
    if (strcmp(op, ">") == 0) {
        r = (a->cell[0]->num > a->cell[1]->num);
    }
    if (strcmp(op, "<") == 0) {
        r = (a->cell[0]->num < a->cell[1]->num);
    }
    if (strcmp(op, ">=") == 0) {
        r = (a->cell[0]->num >= a->cell[1]->num);
    }
    if (strcmp(op, "<=") == 0) {
        r = (a->cell[0]->num <= a->cell[1]->num);
    }

    lval_del(a);
    return lval_bool(r);
}

lval* builtin_load(lenv* e, lval* a)
{
    LASSERT_NUM("load", a, 1);
    LASSERT_TYPE("load", a, 0, LVAL_STR);

    mpc_result_t r;
    if (!strstr(a->cell[0]->str, ".lspy")) {
        strcat(a->cell[0]->str, ".lspy");
    }
    if (mpc_parse_contents(a->cell[0]->str, Lispy, &r)) {
        /* Read contents */
        lval* expr = lval_read(r.output);
        mpc_ast_delete(r.output);

        while (expr->count) {
            lval* x = lval_eval(e, lval_pop(expr, 0));
            if (x->type == LVAL_ERR) {
                lval_println(x);
            }
            lval_del(x);
        }

        lval_del(expr);
        lval_del(a);

        return lval_sexpr();
    } else {
        char* err_msg = mpc_err_string(r.error);
        mpc_err_delete(r.error);

        lval* err = lval_err("Could not load Library %s", err_msg);
        free(err_msg);
        lval_del(a);

        return err;
    }
}

lval* builtin_print(lenv* e, lval* a)
{
    for (int i = 0; i < a->count; i++) {
        lval_print(a->cell[i]);
        putchar(' ');
    }
    putchar('\n');
    lval_del(a);

    return lval_sexpr();
}

lval* builtin_exit(lenv* e, lval* a)
{
    lenv_del(e);
    lval_del(a);
    exit(0);
}

lval* builtin_error(lenv* e, lval* a)
{
    LASSERT_NUM("error", a, 1);
    LASSERT_TYPE("error", a, 0, LVAL_STR);

    lval* err = lval_err(a->cell[0]->str);

    lval_del(a);

    return err;
}

void lenv_add_builtin(lenv* e, char* name, lbuiltin builtin)
{
    lval* k = lval_sym(name);
    lval* v = lval_builtin(builtin);
    lenv_put(e, k ,v);
    lval_del(k);
    lval_del(v);
}

void lenv_add_builtin_var(lenv* e, char* name, lval* val)
{
    lval* k = lval_sym(name);
    lval* v = lval_copy(val);
    v->is_builtin = 1;
    lenv_put(e, k, v);
    lval_del(k);
    lval_del(v);
}

void lenv_add_builtins(lenv* e)
{
    /* Builtin vars */
    lenv_add_builtin_var(e, "True", lval_bool(1));
    lenv_add_builtin_var(e, "False", lval_bool(0));

    /* String Functions */
    lenv_add_builtin(e, "load", builtin_load);
    lenv_add_builtin(e, "error", builtin_error);
    lenv_add_builtin(e, "print", builtin_print);

    /* Assignments */
    lenv_add_builtin(e, "\\", builtin_lambda);
    lenv_add_builtin(e, "def", builtin_def);
    lenv_add_builtin(e, "=", builtin_put);
    lenv_add_builtin(e, "env", builtin_env);

    /* List operations */
    lenv_add_builtin(e, "list", builtin_list);
    lenv_add_builtin(e, "head", builtin_head);
    lenv_add_builtin(e, "tail", builtin_tail);
    lenv_add_builtin(e, "cons", builtin_cons);
    lenv_add_builtin(e, "last", builtin_last);
    lenv_add_builtin(e, "take", builtin_take);
    lenv_add_builtin(e, "drop", builtin_drop);
    lenv_add_builtin(e, "reverse", builtin_rev);
    lenv_add_builtin(e, "sort", builtin_sort);
    lenv_add_builtin(e, "eval", builtin_eval);
    lenv_add_builtin(e, "join", builtin_join);
    lenv_add_builtin(e, "len", builtin_len);
    lenv_add_builtin(e, "init", builtin_init);
    lenv_add_builtin(e, "sum", builtin_sum);
    lenv_add_builtin(e, "product", builtin_prod);
    lenv_add_builtin(e, "nth", builtin_nth);

    /* Arithmetic */
    lenv_add_builtin(e, "+", builtin_add);
    lenv_add_builtin(e, "-", builtin_sub);
    lenv_add_builtin(e, "*", builtin_mul);
    lenv_add_builtin(e, "/", builtin_div);
    lenv_add_builtin(e, "%", builtin_mod);
    lenv_add_builtin(e, "^", builtin_pow);
    lenv_add_builtin(e, "min", builtin_min);
    lenv_add_builtin(e, "max", builtin_max);

    /* Conditionals */
    lenv_add_builtin(e, "if", builtin_if);
    lenv_add_builtin(e, "==", builtin_eq);
    lenv_add_builtin(e, "!=", builtin_ne);
    lenv_add_builtin(e, ">", builtin_gt);
    lenv_add_builtin(e, "<", builtin_lt);
    lenv_add_builtin(e, ">=", builtin_ge);
    lenv_add_builtin(e, "<=", builtin_le);
    lenv_add_builtin(e, "&&", builtin_and);
    lenv_add_builtin(e, "||", builtin_or);
    lenv_add_builtin(e, "!", builtin_not);

    /* Other functions */
    lenv_add_builtin(e, "exit", builtin_exit);
}

int min(int x, int y)
{
    if (x < y) { return x; }
    return y;
}

double fmin(double x, double y)
{
    if (x < y) { return x; }
    return y;
}

int max(int x, int y)
{
    if (x > y) { return x; }
    return y;
}

double fmax(double x, double y)
{
    if (x > y) { return x; }
    return y;
}

int main(int argc, char** argv)
{
    Range    = mpc_new("range");
    Decimal  = mpc_new("decimal");
    Number   = mpc_new("number");
    String   = mpc_new("string");
    Symbol   = mpc_new("symbol");
    Comment  = mpc_new("comment");
    Sexpr    = mpc_new("sexpr");
    Qexpr    = mpc_new("qexpr");
    Expr     = mpc_new("expr");
    Lispy    = mpc_new("lispy");

    /* Define them with the following Language */
    mpca_lang(MPCA_LANG_DEFAULT,
      "                                                           \
        range    : /-?[0-9]+\\.\\.[0-9]+/;                        \
        decimal  : /-?[0-9]+\\.[0-9]+/;                           \
        number   : /-?[0-9]+/ ;                                   \
        string   : /\"(\\\\.|[^\"])*\"/ ;                         \
        symbol   : /[a-zA-Z0-9_+\\-*\\/\\\\=<>!&|%^]+/ ;          \
        comment  : /;[^\\r\\n]*/ ;                                \
        sexpr    : '(' <expr>* ')' ;                              \
        qexpr    : '{' <expr>* '}' ;                              \
        expr     : <range> | <decimal> | <number> | <string> |    \
                   <symbol> | <comment> | <sexpr> | <qexpr> ;     \
        lispy    : /^/ <expr>* /$/ ;                              \
      ",
      Range, Decimal, Number, String, Comment,
      Symbol, Sexpr, Qexpr, Expr, Lispy);

    lenv* e = lenv_new();
    lenv_add_builtins(e);

    lval* stdlib_file = lval_add(lval_sexpr(), lval_str("stdlib.lspy"));
    lval* stdlib_load = builtin_load(e, stdlib_file);
    if (stdlib_load->type == LVAL_ERR) {
        lval_println(stdlib_load);
    }
    lval_del(stdlib_load);

    if (argc == 1) {
        puts(BOLDMAGENTA);
        puts("    __    _                  ");
        puts("   / /   (_)________  __  __ ");
        puts("  / /   / / ___/ __ \\/ / / /");
        puts(" / /___/ (__  ) /_/ / /_/ /  ");
        puts("/_____/_/____/ .___/\\__, /  ");
        puts("            /_/    /____/    ");
        puts(RESET);

        puts(BOLDWHITE);
        puts("Version 0.15");
        puts("Press Ctrl+c , or type 'exit 1' to exit\n");
        puts(RESET);

        while (1) {
            char* input = readline("lispy> ");
            add_history(input);

            mpc_result_t r;
            if (mpc_parse("<stdin>", input, Lispy, &r)) {

                lval* x = lval_eval(e, lval_read(r.output));
                lval_println(x);
                lval_del(x);
                mpc_ast_delete(r.output);
            } else {
                mpc_err_print(r.error);
                mpc_err_delete(r.error);
            }

            free(input);
        }
    }

    if (argc >= 2) {
        for (int i = 1; i < argc; i++) {
            lval* args = lval_add(lval_sexpr(), lval_str(argv[i]));

            lval* x = builtin_load(e, args);

            if (x->type == LVAL_ERR) {
                lval_println(x);
            }
            lval_del(x);
        }
    }

    lenv_del(e);
    mpc_cleanup(10, Range, Decimal, Number, String, Comment,
            Symbol, Sexpr, Qexpr, Expr, Lispy);
    return 0;
}
