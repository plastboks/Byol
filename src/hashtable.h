/**
 * Lispy hashtable header file
 *
 * @filename: hashtable.h
 *
 * @version: 0.16
 *
 * @date: 2014-11-14
 *
 * @description: Lispy version header file
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
#include <string.h>
#include <openssl/sha.h>

struct list 
{
    char* string;
    struct list* next;
    struct list* last;
};

struct hash_table
{
    int size;
    struct list** table;
};

struct hash_table* create_hash_table(int size);
unsigned int hash(struct hash_table* table, char* str);
struct list* lookup_string(struct hash_table* table, char* str);
int add_string(struct hash_table* table, char* str);
