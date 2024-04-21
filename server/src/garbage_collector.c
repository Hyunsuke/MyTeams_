/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** garbage_collector.c
*/
#include "garbage_collector.h"

static object_entry_t *get_object_table(void)
{
    static object_entry_t object_table[MAX_OBJECTS];

    return object_table;
}

static void initialize_gc(void)
{
    object_entry_t *object_table = get_object_table();

    for (int i = 0; i < MAX_OBJECTS; ++i) {
        object_table[i].ptr = NULL;
        object_table[i].active = 0;
    }
}

static void *my_malloc_zero(size_t size)
{
    char *ptr = malloc(size);

    while (size > 0) {
        size--;
        ptr[size] = 0;
    }
    return ptr;
}

static void *my_malloc_allocate(size_t size)
{
    int index = -1;
    object_entry_t *object_table;
    void *ptr;

    object_table = get_object_table();
    for (int i = 0; i < MAX_OBJECTS; ++i)
        if (!object_table[i].active) {
            index = i;
            break;
        }
    if (index == -1) {
        printf("Erreur d'allocation.\n");
        return NULL;
    }
    ptr = my_malloc_zero(size);
    if (ptr != NULL) {
        object_table[index].ptr = ptr;
        object_table[index].active = 1;
    }
    return ptr;
}

void *my_malloc(size_t size)
{
    static int gc_initialized = 0;

    if (!gc_initialized) {
        initialize_gc();
        gc_initialized = 1;
    }
    return my_malloc_allocate(size);
}

void my_free_all(void)
{
    object_entry_t *object_table = get_object_table();

    for (int i = 0; i < MAX_OBJECTS; ++i) {
        if (object_table[i].active) {
            free(object_table[i].ptr);
            object_table[i].ptr = NULL;
            object_table[i].active = 0;
        }
    }
}
