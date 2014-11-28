/**
 * Lispy lval header file
 *
 * @filename: lval.h
 *
 * @version: 0.14
 *
 * @date: 2014-11-14
 *
 * @description: Lispy lval header file.
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

#include <string.h>
#include <math.h>

#include "structures.h"
#include "func.h"
#include "macros.h"
#include "lispy.h"
#include "mpc.h"

lval* lval_fun(lbuiltin builtin);
lval* lval_lambda(lval* formals, lval* body);

lval* lval_qexpr(void);
lval* lval_range(long x, long y);
lval* lval_sexpr(void);
lval* lval_sym(char* s);
lval* lval_str(char* s);
lval* lval_err(char* fmt, ...);
lval* lval_dec(double x);
lval* lval_num(long x);
lval* lval_bool(int val);

lval* lval_add(lval* v, lval* x);
lval* lval_eval(lenv* e, lval* v);
lval* lval_eval_sexpr(lenv*e, lval* v);
lval* lval_pop(lval* v, int i);
lval* lval_take(lval* v, int i);
lval* lval_join(lval* x, lval* y);
lval* lval_copy(lval* v);
lval* lval_call(lenv* e, lval* f, lval* a);

lval* lval_read_num(mpc_ast_t* t);
lval* lval_read_dec(mpc_ast_t* t);
lval* lval_read_range(mpc_ast_t* t);
lval* lval_read_str(mpc_ast_t* t);
lval* lval_read(mpc_ast_t* t);

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
lval* builtin_error(lenv* e, lval* a);
lval* builtin_def(lenv* e, lval* a);
lval* builtin_put(lenv* e, lval* a);
lval* builtin_add(lenv* e, lval* a);
lval* builtin_sub(lenv* e, lval* a);
lval* builtin_mul(lenv* e, lval* a);
lval* builtin_div(lenv* e, lval* a);
lval* builtin_mod(lenv* e, lval* a);
lval* builtin_pow(lenv* e, lval* a);
lval* builtin_min(lenv* e, lval* a);
lval* builtin_max(lenv* e, lval* a);

void lval_del(lval* v);
char* ltype_name(int t);
