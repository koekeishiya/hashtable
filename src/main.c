#include <stdio.h>

#define HASHTABLE_IMPLEMENTATION
#include "hashtable.h"

int compare_string(const char *a, const char *b)
{
    if(a && b) {
        while(*a && *b && *a == *b) {
            ++a;
            ++b;
        }
        return *a == '\0' && *b == '\0';
    }
    return 0;
}

unsigned long hash_string(char *key)
{
    unsigned long hash = 0, high;
    while(*key) {
        hash = (hash << 4) + *key++;
        high = hash & 0xF0000000;
        if(high) {
            hash ^= (high >> 24);
        }
        hash &= ~high;
    }
    return hash;
}

int main()
{
    struct table table;
    int *value;

    const char *keys[] =  { "key1", "key2", "key3" };
    int values[3] = { 5, 6, 7 };

    table_init(&table, 128, (table_hash_func)hash_string, (table_compare_func)compare_string);

    for(int i = 0; i < 3; ++i) {
        table_add(&table, (void*)keys[i], (void*)&values[i]);
    }

    for(int i = 0; i < 3; ++i) {
        value = table_find(&table, (void*)keys[i]);
        printf("key '%s' -> %d\n", keys[i], *value);
    }

    table_remove(&table, "key1");
    table_remove(&table, "key2");

    for(int i = 0; i < 3; ++i) {
        value = table_find(&table, (void*)keys[i]);
        if(value) {
            printf("key '%s' -> %d\n", keys[i], *value);
        } else {
            printf("key '%s' -> <not found>\n", keys[i]);
        }
    }

    table_free(&table);
    return 0;
}
