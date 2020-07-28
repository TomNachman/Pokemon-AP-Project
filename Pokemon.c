#include "Pokemon.h"


/** Create new Pokemon, Type, Bio Details */

// Create new type of BioDetail
static BioDetails *createBio(float Height, float Weight, int Attack){

    //allocate memory for BioDetails
    BioDetails *newBio = (BioDetails *) malloc(sizeof(BioDetails));
    if(newBio==NULL){
        printf("No Memory Available");
        free(newBio);
        newBio = NULL;
        return NULL;
    }
    newBio->height=Height;
    newBio->weight=Weight;
    newBio->attack=Attack;

    return newBio;
}

// Create new Pokemon
Pokemon* createPokemon(char *name, char *spieces, float Hieght, float Wieght, int attack, char *pokeType){

    //allocate memory for pokemon
    Pokemon *newPokemon = (Pokemon*) malloc(sizeof(struct Pokemon));
    if(newPokemon==NULL){
        printf("No Memory Available");
        free(newPokemon);
        newPokemon = NULL;
        return NULL;
    }

    newPokemon->name = name;
    newPokemon->type = pokeType;
    newPokemon->species = spieces;

    newPokemon->bio = createBio(Hieght, Wieght, attack);
    if(newPokemon->bio == NULL) {
        free(newPokemon->bio);
        newPokemon->bio = NULL;
        printf("No Memory Available");
        return NULL;
    }
    return newPokemon;
}

// Create new type of Pokemon
Type* createType(char *Name){

    //allocate memory for Type
    Type* newType = (Type*) malloc(sizeof(Type));
    if(newType==NULL){
        free(newType);
        newType = NULL;
        printf("No Memory Available");
        return NULL;
    }

    newType->typeName = Name;
    newType->numOfPokemons = 0;
    newType->numOf_effectife_against_others =0;
    newType->numOf_effectife_against_me=0;
    newType->effective_against_me = NULL;
    newType->effective_against_others = NULL;
    return newType;
}


/** Add Against*/

// Add against me
status addAgainstMe(Type *me , Type *against)
{
    if (me!=NULL){
        for(int i=0; i<me->numOf_effectife_against_me;i++) {
            if (strcmp(me->effective_against_me[i]->typeName, against->typeName) == 0) {
                printf("This type already exist in list.\n");
                return failure;
            }
        }

        if (me->numOf_effectife_against_me ==0 ){
            me->numOf_effectife_against_me++;
            me->effective_against_me = (Type** ) malloc(sizeof(Type*)* me->numOf_effectife_against_me);
        }
        else {
            me->numOf_effectife_against_me++;
            me->effective_against_me = (Type** ) realloc(me->effective_against_me , me->numOf_effectife_against_me*sizeof(Type*));

        }
        if(me->effective_against_me==NULL){
            printf("No Memory Available\n");
            free(me->effective_against_me);
            me->effective_against_me = NULL;
            return failure;
        }

        if (against==NULL){
            printf("Type name doesn't exist in list.\n");
            return failure;
        }

        me->effective_against_me[me->numOf_effectife_against_me-1] = against;
        return success;

    }
    return failure;
}

// Add against other
status addAgainstOthers(Type *me , Type *against)
{
    if (me!=NULL){
        for(int i=0; i<me->numOf_effectife_against_others;i++) {
            if (strcmp(me->effective_against_others[i]->typeName, against->typeName) == 0) {
                printf("This type already exist in list.\n");
                return failure;
            }
        }
        if (me->numOf_effectife_against_others ==0 ){
            me->numOf_effectife_against_others++;
            me->effective_against_others = (Type** ) malloc(sizeof(Type*)* me->numOf_effectife_against_others);
        }
        else {
            me->numOf_effectife_against_others++;
            me->effective_against_others = (Type** ) realloc(me->effective_against_others , me->numOf_effectife_against_others*sizeof(Type*));

        }
        if(me->effective_against_others==NULL){
            printf("No Memory Available\n");
            free(me->effective_against_others);
            me->effective_against_me = NULL;
            return failure;
        }

        if (against==NULL){
            printf("Type name doesn't exist in list.\n");
            return failure;
        }

        me->effective_against_others[me->numOf_effectife_against_others-1] = against;
        return success;

    }
    return failure;
}

/** generic function */

//free pokomen function
status freePokemon(element elem) {
    if (elem != NULL) {
        Pokemon *p = (Pokemon *) elem;
        free(p->name);
        free(p->type);
        free(p->species);
        free(p->bio);
        free(p);
        return success;
    }
    return failure;
}

//given a elem(pokemon) return the category(type) of the pokemon
char* getCategory(element elem)
{
    Pokemon *p = (Pokemon *) elem;
    return p->type;
}

//print pokemon
status printPokemon(element elem){
    Pokemon *p = (Pokemon *) elem;
    if (p != NULL){
        printf("%s :\n%s, %s Type.\nHeight: %.2f m    Weight: %.2f kg    Attack: %d\n\n",
               p->name, p->species, p->type, p->bio->height,p->bio->weight, p->bio->attack);
        return  success;
    }
    else{
        printf("The Pokemon doesn't exist.\n");
        return failure;
    }
}

//compare by attack func of pokemons -- 0 if equal, 1 if elem1 is bigger,-1 otherwise
int equalPokemon (element elem1 , element elem2)
{
    Pokemon *p1 = (Pokemon *) elem1;
    Pokemon *p2 = (Pokemon *) elem2;

    if(p2==NULL){
        return 1;
    }

    if(p1==NULL) {
        return -1;
    }

    //if (p1 != NULL && p2 != NULL) {
        BioDetails *tmpBio1 = p1->bio;
        BioDetails *tmpBio2 = p2->bio;

        if (tmpBio1->attack > tmpBio2->attack) { return 1; }
        if (tmpBio1->attack == tmpBio2->attack) { return 0; }
        return -1;
    //}
}

//copy pokemon function
element copyPokemon(element elem)
{
    Pokemon *p = (Pokemon *)elem;

    Pokemon *tmp ;
    char *name = (char *)malloc((strlen(p->name))+1);
    strcpy(name, p->name);
    char *species = (char *)malloc((strlen(p->species))+1);
    strcpy(species, p->species);
    char *type = (char *)malloc((strlen(p->type))+1);
    strcpy(type, p->type);
    tmp = createPokemon(name,species,p->bio->height,p->bio->weight,p->bio->attack,type);
    return (element)tmp;
}

//the function retuens the |Attack of firstElem - Attack of secondElem| and changes the given (int) pointer to the new attack
//according to the given instructions
int getAttack(element firstElem, element secondElem , int* attackFirst, int* attackSecond) {
    Pokemon *p1 = (Pokemon *) firstElem;
    Pokemon *p2 = (Pokemon *) secondElem;
    Type *new_type1 = istype(p1->type);
    Type *new_type2 = istype(p1->type);

    int attack1 = p1->bio->attack;
    int attack2 = p2->bio->attack;

    int numOfEAM1 = new_type1->numOf_effectife_against_me;
    int numOfEAM2 = new_type2->numOf_effectife_against_me;

    for (int i = 0; i < numOfEAM1; i++) {
        if (strcmp(new_type1->effective_against_me[i]->typeName, p2->type) == 0) {
            attack1 -= 10;
        }
    }

    for (int i = 0; i < numOfEAM2; i++) {
        if (strcmp(new_type2->effective_against_me[i]->typeName, p1->type) == 0) {
            attack2 -= 10;
        }
    }

    *attackFirst = attack1;
    *attackSecond = attack2;

    return attack1 - attack2;
}