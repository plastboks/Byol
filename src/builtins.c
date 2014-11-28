/*
 * Lispy builtins source file.
 *
 * @filename: builtins.c
 *
 * @version: 0.14
 *
 * @date: 2014-11-14
 *
 * @description: Lispy builtins source file.
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

#include "builtins.h"

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

lval* builtin_put(lenv* e, lval* a)
{
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
            return lval_err("Cannot operate on non-number. %s or %s expected",
                    ltype_name(LVAL_NUM), ltype_name(LVAL_DEC));
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
            if (strcmp(op, "^") == 0) { x->num = pow(x->num, y->num); }
            if (strcmp(op, "min") == 0) { x->num = min(x->num, y->num); }
            if (strcmp(op, "max") == 0) { x->num = max(x->num, y->num); }
            if (strcmp(op, "%") == 0) {
                if (y->num == 0) {
                    lval_del(x); lval_del(y);
                    x = lval_err("Modulus by zero!");
                    break;
                }
                x->num = x->num % y->num;
            }
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
            if (strcmp(op, "^") == 0) { x->decimal = pow(x->decimal, y->decimal); }
            if (strcmp(op, "min") == 0) { x->decimal = fmin(x->decimal, y->decimal); }
            if (strcmp(op, "max") == 0) { x->decimal = fmax(x->decimal, y->decimal); }
            if (strcmp(op, "%") == 0) {
                if (y->decimal == 0) {
                    lval_del(x); lval_del(y);
                    x = lval_err("Modulus by zero!");
                    break;
                }
                x->decimal = fmod(x->decimal, y->decimal);
            }
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
