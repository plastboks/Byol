/*
 * Lispy lval file.
 *
 * @filename: lval.c
 *
 * @version: 0.14
 *
 * @date: 2014-11-14
 *
 * @description: Lispy lval source file.
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

#include "lval.h"

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
