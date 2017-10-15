/*
 * Author: Bradley M. Small
 * Copyright (c) 2014 All rights reserver
 *
 * Body code for menu functionality.
 */
#include "menu.h"
#include <stdio.h>

/* Displays a title and waits for the user to enter a number.
 * Then clears stdin of all remaining characters including the
 * newline \n
 *
 * Returns the numeric value
 */

int Menu_Prompt_Int(const char *title) {
    int entry = -1;
    int retval = 0;
    char c = '\0';

    while (entry < 0) {
        puts(title);
        retval = scanf("%d", &entry);

        if (retval == EOF) {
            entry = -1;
        } else {
            do {
                c = (char)getchar();
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
char Menu_Prompt_Char(const char *title, const char *choices, const char begin,
                      const char end) {
    char entry = begin - 1;
    char c = '\0';

    while (entry < begin || entry > end) {
        puts(title);
        puts(choices);
        c = entry = (char) getchar();
        while (c != '\n' && c != EOF) {
            c = (char)getchar();
        }
    }

    return entry;
}
