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
#include "macros.h"

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

void lval_println(lval* v);
void lval_print(lval* v);
void lval_expr_print(lval* v, char open, char close);

mpc_parser_t* Number;
mpc_parser_t* Decimal;
mpc_parser_t* Range;
mpc_parser_t* String;
mpc_parser_t* Symbol;
mpc_parser_t* Comment;
mpc_parser_t* Sexpr;
mpc_parser_t* Qexpr;
mpc_parser_t* Expr;
mpc_parser_t* Lispy;
