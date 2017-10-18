/*
 * Author: Bradley M. Small
 * Copyright (c) 2014 All rights reserver
 *
 * body and code for the pass type
 */
#include "pass.h"
#include <stdio.h>

/* buys a pass
 *
 * returns the id of the newly created Pass
 */
int Pass_Buy(Pass *pass, const UserType user, const TermType term,
             TransType const trans, int const amount, time_t const expires) {
    pass->balance = amount;
    pass->trans = trans;
    pass->term = term;
    pass->user = user;
    pass->id = get_next_id();
    pass->expires = expires;

    return pass->id;
}

/* Uses a pass
 * returns success of failure of the action
 * reduced the balance where appropriate
 *
 * This does not follow standard best practices of structured programming
 * but the version below shows that when written that way, this is more
 * readable, and maintainable.
 */
bool Pass_Use(Pass *pass, TransType const trans) {
    /***** SPECIAL CASE FOR WORKERS ****/
    if (pass->user == USERTYPE_WORKER) {
        /* short circuit for workers */
        return true;
    }

    /***** Handle wrong trans type ****/
    if (!(pass->trans & trans)) {
        /* inappropriate trans tyep */
        return false;
    }

    /****** Handle Monthly ***********/
    if (pass->term == TERMTYPE_MONTHLY) {

        if (pass->expires > time(NULL)) {
            return true;
        }
        puts("Expired \n");
        return false;
    }

    /***** Handle Per Ride   ********/
    int rate = Trans_Ride_Rate(trans, pass->user);

    if (rate <= pass->balance) {
        pass->balance -= rate;
        return true;
    }
    /* insuficient funds */
    puts("NSF \n");
    return false;
}

/* checks a pass
 *
 * Simply returns the balance. This may be a bit lacking in functionality
 * but it is as specified.
 */
int Pass_Check(Pass const *pass) { return pass->balance; }

/* Gets an ordinal id for the Pass id's. It is utilitarian and would more likely
 * be a call to a database or algorithmic method of establishing card id's.
 *
 * It simply maintains a static that is incremented each time it is used.
 */
int get_next_id(void) {
    static int id = 999;

    return ++id;
}

/* Follows Structured programming standards
 * but is not nearly as clear. Would make
 * for difficult time adding or changing
 * logic
 * */
/*
bool Pass_Use(Pass * pass, TransType trans)
{
        bool retval = false;

        if ( pass->user == USERTYPE_WORKER ) {
                retval =  true;
        } else {

                if ( (pass->trans & trans) ) {
                        if (pass->term == TERMTYPE_MONTHLY) {
                                if(pass->expires > time(NULL)) {
                                        retval = true;
                                }
                        } else {
                                int rate = Trans_Ride_Rate(trans, pass->user);

                                if (rate <= pass->balance) {
                                        pass->balance -= rate;
                                        retval =  true;
                                }
                        }
                }
        }
        return retval;
}
*/
