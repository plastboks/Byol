/*
 * Lispy hashtable source file
 *
 * @filename: hashtable.h
 *
 * @version: 0.16
 *
 * @date: 2014-11-14
 *
 * @description: Lispy hashtable file
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

#include "hashtable.h"

struct hash_table* create_hash_table(int size)
{
    if (size < 1) { return NULL; }

    struct hash_table* new_table;

    new_table = malloc(sizeof(struct hash_table));
    if (new_table == NULL) { return NULL; }

    new_table->table = malloc(sizeof(struct list *) * size);
    if (new_table->table == NULL) { return NULL; }

    for (int i = 0; i<size; i++) {
        new_table->table[i] = '\0';
    }

    new_table->size = size;

    return new_table;
}

unsigned int hash(struct hash_table* table, lval* v)
{
    unsigned int hashval = 0;

    // find unique information and generate int

    return (hashval % table->size);
}

struct list* lookup_hashed_lval(struct hash_table* table, unsigned int val, lval* )
{
    struct list* new_list;

    // find lval
    return NULL;
}

int add_lval(struct hash_table* table, lval* v)
{
    unsigned int hashval = hash(table, v);

    if (lookup_hashed_lval(table, hashval, v)) { return 2; }

    struct list* new_list = malloc(sizeof(struct list));

    if (new_list == NULL) { return -1; }

    new_list->lval = v;
    new_list->next = table->table[hashval];

    table->table[hashval] = new_list;

    return 0;
}
