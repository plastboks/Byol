/*
 * Lispy header file.
 *
 * @filename: lispy.h
 *
 * @version: 0.14
 *
 * @date: 2013-11-04
 *
 * @description: Lispy main header file.
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

#include <stdio.h>
#include <stdlib.h>

#include <editline/readline.h>
#include <histedit.h>
#include <math.h>

#include "structures.h"

#define LASSERT(args, cond, fmt, ...) \
    if (!(cond)) { \
        lval* err = lval_err(fmt, ##__VA_ARGS__); \
        lval_del(args); \
        return err; \
    }

#define LASSERT_TYPE(builtin, args, index, expect) \
    LASSERT(args, args->cell[index]->type == expect, \
            "Function '%s' passed incorrect type for argument %i. Got %s, expected %s.",\
            builtin, index, ltype_name(args->cell[index]->type), ltype_name(expect))

#define LASSERT_NUM(builtin, args, num) \
    LASSERT(args, args->count == num, \
            "Function '%s' passed incorrect number for arguments. Got %i, expected %i.",\
            builtin, args->count, num)

#define LASSERT_NOT_EMPTY(builtin, args, index) \
    LASSERT(args, args->cell[index]->count != 0, \
            "Function '%s' passed {} for argument %i.",\
            builtin, index)

lval* lval_eval(lenv* e, lval* v);
lval* lval_eval_sexpr(lenv*e, lval* v);
lval* lval_pop(lval* v, int i);
lval* lval_take(lval* v, int i);
lval* lval_join(lval* x, lval* y);
lval* lval_copy(lval* v);
lval* lval_call(lenv* e, lval* f, lval* a);
int lval_eq(lval* x, lval* y);
lval* lenv_get(lenv* e, lval* k);
lenv* lenv_new(void);
lenv* lenv_copy(lenv* e);
void lenv_def(lenv* e, lval* k, lval* v);
char* ltype_name(int t);
void lenv_put(lenv* e, lval* k, lval* v);
void lenv_del(lenv* e);
void lval_del(lval* v);
lval* builtin_head(lenv* e, lval* a);
lval* builtin_tail(lenv* e, lval* a);
lval* builtin_cons(lenv* e, lval* a);
lval* builtin_take(lenv* e, lval* a);
lval* builtin_drop(lenv* e, lval* a);
lval* builtin_rev(lenv* e, lval* a);
lval* builtin_sort(lenv* e, lval* a);
lval* builtin_last(lenv* e, lval* a);
lval* builtin_list(lenv* e, lval* a);
lval* builtin_eval(lenv* e, lval* a);
lval* builtin_join(lenv* e, lval* a);
lval* builtin_len(lenv* e, lval* a);
lval* builtin_init(lenv* e, lval* a);
lval* builtin_sum(lenv* e, lval* a);
lval* builtin_prod(lenv* e, lval* a);
lval* builtin_nth(lenv* e, lval* a);
lval* builtin_lambda(lenv* e, lval* a);
lval* builtin_op(lenv* e, lval* a, char* op);
lval* builtin_ord(lenv* e, lval* a, char* op);
lval* builtin_gt(lenv* e, lval* a);
lval* builtin_lt(lenv* e, lval* a);
lval* builtin_ge(lenv* e, lval* a);
lval* builtin_le(lenv* e, lval* a);
lval* builtin_cmp(lenv* e, lval* a, char* op);
lval* builtin_eq(lenv* e, lval* a);
lval* builtin_ne(lenv* e, lval* a);
lval* builtin_and(lenv* e, lval* a);
lval* builtin_or(lenv* e, lval* a);
lval* builtin_not(lenv* e, lval* a);
lval* builtin_if(lenv* e, lval* a);
lval* builtin_load(lenv* e, lval* a);
lval* builtin_print(lenv* e, lval* a);
lval* builtin_exit(lenv* e, lval* a);
lval* builtin_env(lenv* e, lval* a);
int min(int x, int y);
int max(int x, int y);
void lval_println(lval* v);
void lval_print(lval* v);
void lval_expr_print(lval* v, char open, char close);

mpc_parser_t* Number;
mpc_parser_t* Decimal;
mpc_parser_t* String;
mpc_parser_t* Symbol;
mpc_parser_t* Comment;
mpc_parser_t* Sexpr;
mpc_parser_t* Qexpr;
mpc_parser_t* Expr;
mpc_parser_t* Lispy;
