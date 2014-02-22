/*
 * Author: Bradley M. Small
 * Copyright (c) 2014 All rights reserver
 *
 * Holds the type definition for UserType 
 */
#ifndef _USER_H_
#define _USER_H_

typedef enum _UserType {
	USERTYPE_WORKER   = 0, 
	USERTYPE_STANDARD,
	USERTYPE_STUDENT,
	USERTYPE_ELDERLY
} UserType;

#endif
