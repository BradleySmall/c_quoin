/*
 * Author: Bradley M. Small
 * Copyright (c) 2014 All rights reserver
 *
 * Holds the type definition of the Pass type
 *
 * holds the prototypes 
 */
#ifndef _PASS_H_
#define _PASS_H_

#include <time.h>
#include <stdbool.h>
#include "user.h"
#include "term.h"
#include "trans.h"

typedef struct Transport_Pass {
	int 		id;
	int 		balance;
	time_t      expires;
	UserType 	user;
	TermType 	term;
	TransType 	trans;
} Pass;

int  Pass_Buy(Pass * pass, const UserType user, const TermType term, const TransType trans, const int amount, const time_t expires);
bool Pass_Use(Pass * pass, const TransType trans);
int  Pass_Check(const Pass * pass);
int  get_next_id(void);

#endif
