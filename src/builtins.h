/**
 * Lispy builtins header file
 *
 * @filename: builtins.h
 *
 * @version: 0.16
 *
 * @date: 2014-11-14
 *
 * @description: Lispy builtins header file.
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
#include <time.h>

#include "structures.h"
#include "func.h"
#include "macros.h"
#include "lispy.h"
#include "lval.h"
#include "mpc.h"

void lenv_add_builtin(lenv* e, char* name, lbuiltin func);
void lenv_add_builtin_var(lenv* e, char* name, lval* val);
void lenv_add_builtins(lenv* e);

/* Builtin vars */

/* String Functions */
lval* builtin_load(lenv* e, lval* a);
lval* builtin_include(lenv* e, lval* a);
lval* builtin_error(lenv* e, lval* a);
lval* builtin_print(lenv* e, lval* a);
lval* builtin_eval(lenv* e, lval* a);

/* Assignments */
lval* builtin_lambda(lenv* e, lval* a);
lval* builtin_def(lenv* e, lval* a);
lval* builtin_put(lenv* e, lval* a);
lval* builtin_env(lenv* e, lval* a);

/* List operations */
lval* builtin_list(lenv* e, lval* a);
lval* builtin_head(lenv* e, lval* a);
lval* builtin_tail(lenv* e, lval* a);
lval* builtin_cons(lenv* e, lval* a);
lval* builtin_join(lenv* e, lval* a);
lval* builtin_init(lenv* e, lval* a);

/* Arithmetic */
lval* builtin_op(lenv* e, lval* a, char* op);
lval* builtin_add(lenv* e, lval* a);
lval* builtin_sub(lenv* e, lval* a);
lval* builtin_mul(lenv* e, lval* a);
lval* builtin_div(lenv* e, lval* a);
lval* builtin_mod(lenv* e, lval* a);
lval* builtin_inc(lenv* e, lval* a);
lval* builtin_dec(lenv* e, lval* a);
lval* builtin_pow(lenv* e, lval* a);
lval* builtin_ln(lenv* e, lval* a);
lval* builtin_log(lenv* e, lval* a);
lval* builtin_ceil(lenv* e, lval* a);
lval* builtin_floor(lenv* e, lval* a);
lval* builtin_min(lenv* e, lval* a);
lval* builtin_max(lenv* e, lval* a);
lval* builtin_rand(lenv* e, lval* a);

/* Trigonometry */
lval* builtin_sin(lenv* e, lval* a);
lval* builtin_sinh(lenv* e, lval* a);
lval* builtin_cos(lenv* e, lval* a);
lval* builtin_cosh(lenv* e, lval* a);
lval* builtin_tan(lenv* e, lval* a);
lval* builtin_tanh(lenv* e, lval* a);

/* Bit shift */
lval* builtin_leftshift(lenv* e, lval* a);
lval* builtin_rightshift(lenv* e, lval* a);
lval* builtin_bitwiseand(lenv* e, lval* a);
lval* builtin_bitwiseor(lenv* e, lval* a);
lval* builtin_bitwisexor(lenv* e, lval* a);

/* Conditionals */
lval* builtin_ord(lenv* e, lval* a, char* op);
lval* builtin_cmp(lenv* e, lval* a, char* op);
lval* builtin_if(lenv* e, lval* a);
lval* builtin_eq(lenv* e, lval* a);
lval* builtin_ne(lenv* e, lval* a);
lval* builtin_gt(lenv* e, lval* a);
lval* builtin_lt(lenv* e, lval* a);
lval* builtin_ge(lenv* e, lval* a);
lval* builtin_le(lenv* e, lval* a);
lval* builtin_and(lenv* e, lval* a);
lval* builtin_or(lenv* e, lval* a);
lval* builtin_not(lenv* e, lval* a);
lval* builtin_xor(lenv* e, lval* a);

/* Other functions */
lval* builtin_exit(lenv* e, lval* a);
lval* builtin_set(lenv* e, lval* a);
lval* builtin_get(lenv* e, lval* a);
lval* builtin_version(lenv* e, lval* a);
