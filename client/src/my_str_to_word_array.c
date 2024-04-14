/*
** EPITECH PROJECT, 2022
** my_str_to_word_array
** File description:
** strnonalphanumerics
*/
#include "client.h"

int number_back(char const *str, char separator)
{
    int i = 0;
    int n = 1;

    while (str[i] != '\0') {
        if (str[i] == separator) {
            n = n + 1;
        }
        i++;
    }
    return (n);
}

char **my_str_to_word_array(char const *str, char separator)
{
    int scale_y = number_back(str, separator);
    int y = 0;
    int x = 0;
    int index = 0;
    char **generator = malloc(sizeof(char *) * (scale_y + 1));

    for (int tmp = 0; str[index]; y++) {
        x = 0;
    for (tmp = 0; str[index + tmp] != separator && str[index + tmp]; tmp++);
    generator[y] = malloc(sizeof(char) * (tmp + 1));
        for (; str[index] != separator && str[index]; x++) {
            generator[y][x] = str[index];
            index++;
    }
        generator[y][x] = '\0';
        if (str[index])
            index++;
    }
    generator[y] = NULL;
    return (generator);
}
