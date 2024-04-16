/*
** EPITECH PROJECT, 2022
** my_str_to_word_array
** File description:
** strnonalphanumerics
*/
#include "server.h"

int number_back(char const *str, char separator)
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

int find_end_of_word(char const *str, char separator)
{
    int index = 0;
    int inside_quotes = 0;

    while (str[index] != '\0') {
        if (str[index] == '"')
            inside_quotes = !inside_quotes;
        if (str[index] == separator && !inside_quotes)
            break;
        index++;
    }
    return index;
}

char *copy_word(char const *str, int start_index, int end_index)
{
    int word_length = end_index - start_index;
    char *word = malloc(sizeof(char) * (word_length + 1));

    for (int i = 0; i < word_length; i++)
        word[i] = str[start_index + i];
    word[word_length] = '\0';
    return word;
}

char **my_str_to_word_array(char const *str, char separator)
{
    int scale_y = number_back(str, separator);
    char **generator = malloc(sizeof(char *) * (scale_y + 1));
    int index = 0;
    int start_index = 0;
    int end_index = 0;

    for (int y = 0; y < scale_y; y++) {
        start_index = index;
        end_index = find_end_of_word(str + index, separator) + index;
        generator[y] = copy_word(str, start_index, end_index);
        while (str[end_index] == separator)
            end_index++;
        index = end_index;
    }
    generator[scale_y] = NULL;
    return generator;
}
