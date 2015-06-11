/*
 * Lispy config header file
 *
 * @filename: config.h
 *
 * @version: 0.16
 *
 * @date: 2015-06-10
 *
 * @description: Lispy config header file.
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

#ifndef CONFIG
#define CONFIG
typedef struct
{
    int splash;
    int decimal_count;
} config;
#endif

int get_splash();
void set_splash(int val);

int get_decimal();
void set_decimal(int val);
