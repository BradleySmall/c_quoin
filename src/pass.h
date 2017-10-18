/*
 * Author: Bradley M. Small
 * Copyright (c) 2014 All rights reserver
 *
 * Holds the type definition of the Pass type
 *
 * holds the prototypes
 */
#ifndef PASS_H
#define PASS_H 1

#include "term.h"
#include "trans.h"
#include "user.h"
#include <stdbool.h>
#include <time.h>

typedef struct Transport_Pass {
    int id;
    int balance;
    time_t expires;
    UserType user;
    TermType term;
    TransType trans;
} Pass;

int Pass_Buy(Pass *pass, UserType user, TermType term,
             TransType trans, int amount, time_t expires);
bool Pass_Use(Pass *pass, TransType trans);
int Pass_Check(Pass const *pass);
int get_next_id(void);

#endif
