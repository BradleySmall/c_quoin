/*
 * Author: Bradley M. Small
 * Copyright (c) 2014 All rights reserver
 *
 * Holds the prototypes for Menu functionality. There is no Type definition to
 * support
 */
#ifndef C_QUOIN_MENU_H
#define C_QUOIN_MENU_H 1

int Menu_Prompt_Int(char const *title);
char Menu_Prompt_Char(char const *title, char const *choices, char begin,
                      char end);

#endif
