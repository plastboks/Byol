/*
 * Lispy macros header file.
 *
 * @filename: macros.h
 *
 * @version: 0.16
 *
 * @date: 2013-11-04
 *
 * @description: Lispy macros header file.
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

#ifndef LASSERTS
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
#endif
