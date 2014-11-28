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

#include "structures.h"
#include "macros.h"
#include "lenv.h"
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
lval* lval_builtin(lbuiltin func);

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

lval* lenv_get(lenv* e, lval* k);

int lval_eq(lval* x, lval* y);

void lval_del(lval* v);
void lval_print(lval* v);
void lval_println(lval* v);
void lval_print_str(lval* v);

void lval_expr_print(lval* v, char open, char close);
char* ltype_name(int t);
