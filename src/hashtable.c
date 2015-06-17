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

unsigned int hash(struct hash_table* table, char* str)
{
    unsigned int hashval = 0;

    for (int i = 0; *str != '\0'; i++, str++) {
        hashval += str[i];
    }

    return (hashval % table->size);
}

struct list* lookup_string(struct hash_table* table, char* str)
{
    struct list* new_list;
    unsigned int val = hash(table, str);

    for (new_list = table->table[val]; new_list != NULL; new_list = new_list->next) {
        if (strcmp(str, new_list->string) == 0) {
            return new_list;
        }
    }
    return NULL;
}

int add_string(struct hash_table* table, char* str)
{
    return 0;
}
