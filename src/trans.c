/*
 * Author: Bradley M. Small
 * Copyright (c) 2014 All rights reserver
 *
 * provides code to the trans (portation) type
 *
 * lookup tables for managing base rates and discounts. Those could merely be
 * changed here.
 *
 * provides the functionality for looking up the discounted rates
 */
#include "trans.h"
#include <time.h>

/* Base rate table */
static int Trans_Bases[16] = {0,  10, 15, -1, 20, -1, -1, -1,
                              25, -1, -1, -1, -1, -1, -1, -1};

/* Monthly Base rate table */
static int Trans_Monthly[16] = {0,   200, 300, -1, 400, -1, -1, -1,
                                500, -1,  -1,  -1, -1,  -1, -1, -1};

/* day of month discount */
static float DOM_Discount[31] = {1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
                                 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.5, 0.5,
                                 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5,
                                 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5};

/* user type discount */
static float User_Discounts[4] = {0, 1.0, 0.5, 0.5};

/* day of week discount */
static float DOW_Discounts[7] = {0.75, 1.0, 1.0, 1.0, 1.0, 1.0, 0.75};

/* Returns Per Ride price,
 * discounted by the user type
 * discounted by the day of the week
 *
 * day of week is calculated here
 *
 * -1 indicates a currently unused value
 *    it would be useful for future expansion
 * */
int Trans_Ride_Rate(const TransType trans, const UserType user) {
    int base = Trans_Bases[trans];
    float usr_disc = User_Discounts[user];

    /* calculate day of week*/
    time_t now = time(NULL);
    int dow = localtime(&now)->tm_wday;

    float dow_disc = DOW_Discounts[dow];

    return (base == -1) ? -1 : (int)(base * usr_disc * dow_disc);
}

/* Returns Monthly price,
 * discounted by the user type
 * discounted by the day of the month
 *
 * day of month is passed in as a parm
 *
 * -1 indicates a currently unused value
 *    it would be useful for future expansion
 * */
int Trans_Month_Rate(const TransType trans, const UserType user,
                     const int dom) {
    int base = Trans_Monthly[trans];
    float usr_disc = User_Discounts[user];
    float dom_disc = DOM_Discount[dom];

    return (base == -1) ? -1 : (int)(base * usr_disc * dom_disc);
}
