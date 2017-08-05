#include <stdio.h>
#include <stdlib.h>

#define HASHTABLE_IMPLEMENTATION
#include "hashtable.h"

int count_string(const char *s)
{
    int count = 0;
    while(s && *s) {
        ++count;
        ++s;
    }
    return count;
}

char *copy_string(const char *s)
{
    int s_len = count_string(s);
    char *result = malloc(s_len + 1);
    memcpy(result, s, s_len);
    result[s_len] = '\0';
    return result;
}

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
    void *value;
    struct table table;
    table_init(&table, 128, hash_string, compare_string);

    table_insert(&table, copy_string("key1"), 5);
    table_insert(&table, copy_string("key2"), 6);
    table_insert(&table, copy_string("key3"), 7);

    value = table_find(&table, "key1");
    if(value) {
        printf("value: %d\n", (int)value);
    }

    value = table_find(&table, "key2");
    if(value) {
        printf("value: %d\n", (int)value);
    }

    value = table_find(&table, "key3");
    if(value) {
        printf("value: %d\n", (int)value);
    }

    value = table_remove(&table, "key1");
    if(value) {
        printf("value: %d\n", (int)value);
    }

    value = table_find(&table, "key1");
    if(value) {
        printf("value: %d\n", (int)value);
    }

    table_free(&table);
    return 0;
}
