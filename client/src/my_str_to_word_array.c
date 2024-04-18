/*
** EPITECH PROJECT, 2022
** my_str_to_word_array
** File description:
** strnonalphanumerics
*/
#include "client.h"

int number_back(const char *str, char separator)
{
    int count = 0;
    int inside_quotes = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '"') {
            inside_quotes = !inside_quotes;
            continue;
        }
        if (str[i] == separator && !inside_quotes) {
            count++;
        }
    }
    return count + 1;
}

void copy_to_string(char *remaining, int space, char **gen, char const *str)
{
    char *trimmed_str = remaining + 1;

    gen[0] = my_malloc(sizeof(char) * (space + 1));
    for (int j = 0; j < space; j++)
        gen[0][j] = str[j];
    gen[0][space] = '\0';
    gen[1] = trimmed_str;
    gen[2] = NULL;
}

char **my_str_to_word_array(char const *str, char separator)
{
    int scale_y = number_back(str, separator);
    char **generator = my_malloc(sizeof(char *) * (scale_y + 1));
    int first_space_index = 0;
    int remaining_length = 0;
    char *remaining_str = NULL;
    int i = 0;

    while (str[first_space_index] != ' ' && str[first_space_index] != '\0')
        first_space_index++;
    while (str[first_space_index + remaining_length] != '\0')
        remaining_length++;
    remaining_str = my_malloc(sizeof(char) * (remaining_length + 1));
    while (str[first_space_index + i] != '\0') {
        remaining_str[i] = str[first_space_index + i];
        i++;
    }
    remaining_str[i] = '\0';
    copy_to_string(remaining_str, first_space_index, generator, str);
    return generator;
}
