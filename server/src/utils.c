/*
** EPITECH PROJECT, 2022
** my_str_to_word_array
** File description:
** strnonalphanumerics
*/
#include "server.h"

bool check_quotes(const char *str)
{
    // à modifier en fonction de '\r\n' ou '\n' ou '\0'
    if (str[0] == '"' && str[strlen(str) - 3] == '"')
        return true;
    else
        return false;
}

char *remove_quotes(const char *str)
{
    int length = strlen(str);
    char *new_str = malloc(length - 1);

    strncpy(new_str, str + 1, length - 2);
    // à modifier en fonction de '\r\n' ou '\n' ou '\0'
    new_str[length - 4] = '\0';
    return new_str;
}

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
