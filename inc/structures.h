/*
 * Lispy structures header file
 *
 * @filename: structures.h
 *
 * @version: 0.16
 *
 * @date: 2013-11-05
 *
 * @description: Lispy structures header file.
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

#ifndef LSPY_STRUCTURES
#define LSPY_STRUCTURES
struct lval;
struct lenv;
typedef struct lval lval;
typedef struct lenv lenv;
typedef lval*(*lbuiltin)(lenv*, lval*);

enum { LVAL_ERR, LVAL_NUM, LVAL_DEC, LVAL_SYM,
    LVAL_STR, LVAL_FUN, LVAL_SEXPR, LVAL_QEXPR,
    LVAL_BOOL};

struct lval
{
    int type;
    int is_builtin;

    /* Basics */
    long num;
    double decimal;
    char* err;
    char* sym;
    char* str;
    int bool;

    /* Functions */
    lbuiltin builtin;
    lenv* env;
    lval* formals;
    lval* body;

    /* Expressions */
    int count;
    lval** cell;
};

struct lenv
{
    lenv* par;
    int count;
    char** syms;
    lval** vals;
};
#endif
