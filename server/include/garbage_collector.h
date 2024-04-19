/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** garbage_collector.h
*/

#ifndef GARBAGE_COLLECTOR_H
    #define GARBAGE_COLLECTOR_H
    #define MAX_OBJECTS 2000

    #include <stdio.h>
    #include <stdlib.h>

typedef struct ObjectEntry {
    void *ptr;
    int active;
} object_entry_t;

void *my_malloc(size_t size);

void my_free_all(void);
#endif /* GARBAGE_COLLECTOR_H */
