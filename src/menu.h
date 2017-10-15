/*
 * Author: Bradley M. Small
 * Copyright (c) 2014 All rights reserver
 *
 * Holds the prototypes for Menu functionality. There is no Type definition to
 * support
 */
#ifndef MENU_H
#define MENU_H 1

int Menu_Prompt_Int(const char *title);
char Menu_Prompt_Char(const char *title, const char *choices, const char begin,
                      const char end);

#endif
