/*
** EPITECH PROJECT, 2022
** my_str_to_word_array
** File description:
** strnonalphanumerics
*/
#include "client.h"

int number_back(char const *str, char separator)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == separator) {
            return 2;
        }
    }
    return 1;
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
    int first_space_index = 0;

    while (str[first_space_index] != ' ' && str[first_space_index] != '\0')
        first_space_index++;
    if (str[first_space_index] == '\0') {
        generator[0] = copy_word(str, 0, first_space_index);
        generator[1] = NULL;
        return generator;
    }
    generator[0] = copy_word(str, 0, first_space_index);
    generator[1] = copy_word(str, first_space_index + 1, strlen(str));
    generator[2] = NULL;
    return generator;
}
