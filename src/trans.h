/*
 * Author: Bradley M. Small
 * Copyright (c) 2014 All rights reserver
 *
 * Holds the type defintion for the trans (portation) type
 * 0 - worker
 * 1 - bus
 * 2 - subway
 * 4 - rail
 * 8 - elderly bus
 *
 * The rest are simply or'ed combinations. Ths provides for future expansion to
 * potentially handle multiples.
 *
 * Holds the function prototypes
 *
 */
#ifndef C_QUOIN_TRANS_H
#define C_QUOIN_TRANS_H 1

#include "user.h"

typedef enum _TransType {
    TRANSTYPE_WORKER = 0,
    TRANSTYPE_BUS = 1,
    TRANSTYPE_SUBWAY = 2,

    TRANSTYPE_BUS_SUBWAY = 3,

    TRANSTYPE_RAIL = 4,

    TRANSTYPE_BUS_RAIL = 5,
    TRANSTYPE_SUBWAY_RAIL = 6,
    TRANSTYPE_BUS_SUBWAY_RAIL = 7,

    TRANSTYPE_ELDERLYBUS = 8,

    TRANSTYPE_BUS_ELDERLYBUS = 9,
    TRANSTYPE_SUBWAY_ELDERLYBUS = 10,
    TRANSTYPE_BUS_SUBWAY_ELDERLYBUS = 11,
    TRANSTYPE_RAIL_ELDERLYBUS = 12,
    TRANSTYPE_BUS_RAIL_ELDERLYBUS = 13,
    TRANSTYPE_SUBWAY_RAIL_ELDERLYBUS = 14,
    TRANSTYPE_BUS_SUBWAY_RAIL_ELDERLYBUS = 15

} TransType;

int Trans_Ride_Rate(TransType trans, UserType user);
int Trans_Month_Rate(TransType trans, UserType user, int dom);

#endif
