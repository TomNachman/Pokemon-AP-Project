//
// Created by tom on 26.11.2019.
//

#ifndef POKEMON_DEFS_H
#define POKEMON_DEFS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum e_bool {false, true} bool;
typedef enum e_status {success, failure} status;

typedef void * element;

typedef element (*copyFunction)(element );
typedef status (*freeFunction)(element);
typedef status (*printFunction)(element);
typedef int (*equalFunction)(element, element); // 1 first bigger, 0 equals, -1 second bigger.

typedef char*(*getCategoryFunction)(element);
typedef int(*getAttackFunction)(element firstElem, element secondElem , int* attackFirst, int* attackSecond); // return the first attack-second attack. also produce the attack of each element.

#endif //POKEMON_DEFS_H
