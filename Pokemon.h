//
// Created by tom on 26.11.2019.
//

#ifndef POKEMON_POKEMON_H
#define POKEMON_POKEMON_H
#define MAXCHARLINE 300
/** includes */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Defs.h"


/** typedef declarations*/
typedef struct Type Type;
typedef struct BioDetails BioDetails;
typedef struct Pokemon Pokemon;

/**  Structs */
struct Type {
    char *typeName;
    int numOfPokemons;
    int numOf_effectife_against_me;
    int numOf_effectife_against_others;
    Type **effective_against_me;
    Type **effective_against_others;
};
struct Pokemon
{
    char *name;
    char *species;
    BioDetails *bio;
    char *type;
} ;
struct BioDetails
{
    float height;
    float weight;
    int attack;
} ;


/** interface functions */
status printAllTypes(Type**, int);
status addAgainstMe(Type*, Type*);
status addAgainstMeFromLine(Type*,char*,Type**,int);
status addAgainstOthers(Type*,Type*);
status addAgainstOthersFromLine(Type*,char*,Type**,int);

// add types of pokemons
status addTypeFromLine(char*, Type**, int);
Type* createType(char*);

// add pokemons
status addPokemonFromLine(char*, Pokemon **, int,Type **,int);
Pokemon *createPokemon(char *, char *, float , float , int , char *);
static BioDetails *createBio(float, float, int);
status addAgainstFromLine(char*, Type** ,int);


status printByIndex(int , Pokemon **, int);
status printByIndexType(int , Type **, int);

//check if type exist
Type* isTypeExist(Type**, char*, int, int);
Type* isTypeExist2(Type **type, char *typeName, int inList);

/** free funcs */
void freeType(Type**,int);
void freePokemonList(Pokemon**,int);

/** Generic function */
status freePokemon(element elem);
char* getCategory(element elem);
status printPokemon(element elem);
int equalPokemon (element elem1 , element elem2);
element  copyPokemon(element elem);
int getAttack(element firstElem, element secondElem , int* attackFirst, int* attackSecond);
Type* istype(char *);

#endif //POKEMON_POKEMON_H
