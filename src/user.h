/*
 * Author: Bradley M. Small
 * Copyright (c) 2014 All rights reserver
 *
 * Holds the type definition for UserType 
 */
#ifndef USER_H
#define USER_H 1

typedef enum _UserType {
	USERTYPE_WORKER   = 0, 
	USERTYPE_STANDARD,
	USERTYPE_STUDENT,
	USERTYPE_ELDERLY
} UserType;

#endif
