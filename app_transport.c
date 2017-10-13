/*
 * Author: Bradley M. Small
 * Copyright (c) 2014 All rights reserver
 *
 * Application main driver code
 *
 * Displays a menu of choices
 * Reacts to each choice
 * Quits when 'q' is entered
 *
 * Memory allocation is done here
 * Memory cleanup is also done here
 *
 * There is an arbitrary array of Passes done so simply for example. There is no
 * testing of it overrunning its boundaries. The storage would be better done in
 * a dynamic memory structure like a list or tree, or even better a database.
 *
 *
 */
#include "app_transport.h"
#include "menu.h"
#include "pass.h"
#include "term.h"
#include "trans.h"
#include "user.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Arbitrary storage for the passes */
Pass *passes[100] = {0};
int passIndex = 0;

int main(void) {
    unsigned char action = '\0';

    /* main loop to run until the q is entered */
    while (tolower(action) != 'q') {
        /* do stuff */

        switch (tolower(action)) {
        case 'b':
            Buy_A_Pass();

            break;
        case 'u':
            Use_A_Pass();

            break;
        case 'c':
            Check_A_Pass();

            break;
        default:
            break;
        }

        /* the current menu routines handle data in a range
         * this does not work that way. I chose to leave it
         * like this for aesthetics.
         */
        puts("(B)uy, (U)se, (C)heck, (Q)uit");
        char c = action = getchar();
        while (c != '\n' && c != EOF) {
            c = getchar();
        }
    }

    /* on exiting the program, all the memory allocated
     * is now freed. The remaining balances which are
     * lost because they are not serialized are displayed
     * as well.
     */
    for (int i = 0; i < passIndex; ++i) {
        printf("Pass #%d Balance %d\n", passes[i]->id, passes[i]->balance);
        free(passes[i]);
    }

    puts("Goodbye!");
    return 0;
}

/* Helper function for the message pump
 *
 * Performs POS logic and interactively simulates
 * teller entry.
 *
 * Uses the Passes code functions on the Pass type
 * Mostly handles display logic.
 *
 * It is possible that memory allocation is inappropriate here,
 * it might better be handled with a more constructor like
 * function, and simply built into the Pass_Buy() funtion.
 *
 *
 */
void Buy_A_Pass(void) {
    UserType user = {0};
    TermType term = {0};
    TransType trans = {0};
    int amount = 0;
    time_t expires = 0;
    int dom = 0;

    /* get user type */
    char entry = Menu_Prompt_Char(
        "What type of user?",
        "(1) Standard, (2) Student, (3) Elderly, (0) Worker", '0', '3');
    switch (entry) {
    case '0':
        user = USERTYPE_WORKER;
        break;
    case '1':
        user = USERTYPE_STANDARD;
        break;
    case '2':
        user = USERTYPE_STUDENT;
        break;
    case '3':
        user = USERTYPE_ELDERLY;
        break;
    }

    /* short circuit for efficiency if the user type is a worker
     * otherwise determine what the term type is.
     */
    if (user != USERTYPE_WORKER) {
        entry = Menu_Prompt_Char("What type of term?",
                                 "(1) Monthly, (2) Per Ride", '1', '2');
        switch (entry) {
        case '1':
            term = TERMTYPE_MONTHLY;

            time_t now = time(NULL);
            struct tm *timeinfo = localtime(&now);
            /* because we have the day of month now, store it and pass it into
             * the rate calculation instead of recalculating it later.
             *
             * However, I would think all of the date calculations should be
             * moved away from here.
             */
            dom = timeinfo->tm_mday;

            /* calculate the expiration of monthly passes
             * by going to the first day of the next month.
             * when we cross December, incrememt the year too.
             */
            timeinfo->tm_mday = 1;
            if (timeinfo->tm_mon == 12) {
                timeinfo->tm_mon = 1;
                timeinfo->tm_year += 1;
            } else {
                timeinfo->tm_mon += 1;
            }

            expires = mktime(timeinfo);
            break;
        case '2':
            term = TERMTYPE_PERRIDE;
            break;
        }
        /* determine the trans (portation) type */
        entry = Menu_Prompt_Char(
            "What type of trans?",
            "(1) Bus, (2) Subway, (3) Rail, (4) Elderly Bus", '1', '4');
        switch (entry) {
        case '1':
            trans = TRANSTYPE_BUS;
            break;
        case '2':
            trans = TRANSTYPE_SUBWAY;
            break;
        case '3':
            trans = TRANSTYPE_RAIL;
            break;
        case '4':
            trans = TRANSTYPE_ELDERLYBUS;
            break;
        }
    } else {
        /* when shortcircuiting for the worker, the term and trans are set to
         * special values here */
        term = TERMTYPE_WORKER;
        trans = TRANSTYPE_WORKER;
    }

    /* here is where the allocation happens -- probably not a good idea */
    Pass *p = (Pass *)malloc(sizeof(Pass));
    passes[passIndex++] = p;

    /* calculate the price of the monthly */
    if (term == TERMTYPE_MONTHLY) {
        amount = Trans_Month_Rate(trans, user, dom);
    } else {
        /* calculate the price per ride, then query the user
         * for how many he would like. Perhaps they might want
         * fries with that too. :)
         */
        amount = Trans_Ride_Rate(trans, user);
        int rides = Menu_Prompt_Int("How many rides would you like?");

        amount *= rides;
    }

    /* actually use the Pass function for buying the pass with
     * the collected data
     */
    int id = Pass_Buy(p, user, term, trans, amount, expires);

    /* it never hurts to be polite :) */
    printf("Thanks for buying pass #%d! with balance %d\n", id, p->balance);
}

/* Helper function for the message pump
 *
 * performs (POS) consumption logic
 *
 * uses the pass code logic on the Pass
 */
void Use_A_Pass(void) {
    /* determine the trans (portation) type to be used */
    TransType trans = {0};
    char entry = Menu_Prompt_Char(
        "What type of trans?", "(1) Bus, (2) Subway, (3) Rail, (4) Elderly Bus",
        '1', '4');
    switch (entry) {
    case '1':
        trans = TRANSTYPE_BUS;
        break;
    case '2':
        trans = TRANSTYPE_SUBWAY;
        break;
    case '3':
        trans = TRANSTYPE_RAIL;
        break;
    case '4':
        trans = TRANSTYPE_ELDERLYBUS;
        break;
    }

    /* determines the specific pass to use
     * likely this is a card reader for safety
     * of not being able to enter arbitrary pass
     * id's until something works.
     *
     */
    int id = Menu_Prompt_Int("Please enter pass id?");

    bool found = false;
    for (int i = 0; i < passIndex; ++i) {
        if (passes[i]->id == id) {
            found = true;
            /* actual Pass function */
            if (Pass_Use(passes[i], trans)) {
                /* success */
                puts("Thanks for using a pass!\n");
            } else {
                /* Failure
                 *
                 * Rather than bools I could be returning an int that shows -1
                 * for NSF and -2 for invalid transit etc. That may or may not
                 * be an improvement, but I could them return a more specific
                 * message in the event of the card being rejected.
                 * */
                puts("This pass may not have a high enough balance, or it may "
                     "not be valid for this transit!\n");
            }
        }
    }
    /* however, if the pass is not in the system, do give that message
     * specifically */
    if (!found) {
        puts("Invalid pass ID\n");
    }
}

/* Helper for message pump
 *
 * calls the Pass function to return the balance
 *
 * it is thin, but satisfies the specification. One could dump all of the
 * available info on the pass at this point, but that was not asked for.
 */
void Check_A_Pass(void) {
    /* determine the pass id */
    int id = Menu_Prompt_Int("Please enter pass id?");

    bool found = false;
    for (int i = 0; i < passIndex; ++i) {
        if (passes[i]->id == id) {
            found = true;
            /* use the actual pass function to return the balance */
            printf("Balance = %d\n", Pass_Check(passes[i]));
        }
    }
    /* report invalid ID */
    if (!found) {
        puts("Invalid pass ID\n");
    } else {
        /* once again, it doens't cost anything to be polite */
        puts("Thanks for checking a pass!\n");
    }
}
