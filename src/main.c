#include <stdio.h>

#define HASHTABLE_IMPLEMENTATION
#include "hashtable.h"

static TABLE_HASH_FUNC(hash_string)
{
    unsigned long hash = 0;
    unsigned long high = 0;
    char *k = key;

    while (*k) {
        hash = (hash << 4) + *k++;
        high = hash & 0xF0000000;

        if (high) {
            hash ^= (high >> 24);
        }

        hash &= ~high;
    }

    return hash;
}

static TABLE_COMPARE_FUNC(compare_string)
{
    char *a = key_a;
    char *b = key_b;

    while (*a && *b && *a == *b) {
        ++a;
        ++b;
    }

    return *a == '\0' && *b == '\0';
}

struct point
{
    float x, y;
};

int main()
{
    struct table table;
    struct point *value;

    const char *keys[] =  { "key1", "key2", "key3" };
    struct point values[3] = { {5,5}, {6,6}, {7,7} };

    table_init(&table, 128, hash_string, compare_string);

    for (int i = 0; i < 3; ++i) {
        table_add(&table, &keys[i], &values[i]);
    }

    for (int i = 0; i < 3; ++i) {
        value = table_find(&table, &keys[i]);
        printf("key '%s' -> %f, %f\n", keys[i], value->x, value->y);
    }

    table_remove(&table, &keys[0]);
    table_remove(&table, &keys[1]);

    for (int i = 0; i < 3; ++i) {
        value = table_find(&table, &keys[i]);
        if (value) {
            printf("key '%s' -> %f, %f\n", keys[i], value->x, value->y);
        } else {
            printf("key '%s' -> <not found>\n", keys[i]);
        }
    }

    table_free(&table);
    return 0;
}
