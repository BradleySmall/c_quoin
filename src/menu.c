/*
 * Author: Bradley M. Small
 * Copyright (c) 2014 All rights reserver
 *
 * Body code for menu functionality.
 */
#include "menu.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Displays a title and waits for the user to enter a number.
 * Then clears stdin of all remaining characters including the
 * newline \n
 *
 * Returns the numeric value
 */

int Menu_Prompt_Int(char const *title) {
    int entry = -1;
    int retval = 0;
    int c = '\0';
    char line[2] = "";

    while (entry < 0) {
        puts(title);
        fgets(line, sizeof line, stdin);
        retval = strtol(line, NULL, 10);

        if (retval == EOF) {
            entry = -1;
        } else {
            do {
                c = getchar();
            } while (c != '\n' && c != EOF);
        }
    }

    return entry;
}

/* displays a title, and prompt values, then loops until one of the values
 * between begin and end are entered. It returns the value entered.
 *
 * This also clears the stdin including the \n.
 */
char Menu_Prompt_Char(char const *title, char const *choices, char const begin,
                      char const end) {
    int entry = begin - 1;
    int c = '\0';

    while (entry < begin || entry > end) {
        puts(title);
        puts(choices);
        c = entry = getchar();
        while (c != '\n' && c != EOF) {
            c = getchar();
        }
    }

    return entry;
}
