/*
 * Lispy function file.
 *
 * @filename: func.c
 *
 * @version: 0.14
 *
 * @date: 2014-11-14
 *
 * @description: Lispy various functions file.
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

#include "func.h"
#include <string.h>

char* strrev(char *s)
{
    int length = strlen(s);
    int c, i, j;

    for (i = 0, j = length - 1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }

    return s;
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

