#include "Pokemon.h"
#include "BattleByCategory.h"

Type **typeList = NULL;

/** Add against functions */
// Add against from line (Type)
status addAgainstFromLine(char *line, Type **type, int numOfTypes)
{
    char *me = strtok(line+1 , " ");
    Type *tmpType = isTypeExist(type, me, numOfTypes, 0);
    if (tmpType!=NULL){
        char *againatWho = strtok(NULL,":");
        char *restOfLine = strtok(NULL, "\r\n");
        if(strstr(againatWho,"me")!=NULL)
        {
            addAgainstMeFromLine(tmpType, restOfLine, type, numOfTypes);
        }

        else {
            addAgainstOthersFromLine(tmpType, restOfLine, type, numOfTypes);
        }
        return success;
    }
    return failure;
}

// Add against me from line (Type)
status addAgainstMeFromLine(Type *me , char * against,Type **typelist,int numoftypes){
    if (me!=NULL){
        int comma = 0;
        for (int i=0; i<strlen(against); i++) {
            if (',' == against[i]) comma++;
        }


        Type *TmpAgainst;
        if(comma==0)
        {
            TmpAgainst = isTypeExist(typelist, strtok(against, "\r\n"), numoftypes, 0);
            if (TmpAgainst==NULL){
                //printf("Type name doesn't exist in list.\n");
                return failure;
            }
            addAgainstMe(me,TmpAgainst);
            return success;
        }
        if(comma==1)
        {
            TmpAgainst = isTypeExist(typelist, strtok(against, ","), numoftypes, 0);
            if (TmpAgainst==NULL){
                printf("Type name doesn't exist in list.\n");
                return failure;
            }
            addAgainstMe(me,TmpAgainst);

            TmpAgainst = isTypeExist(typelist, strtok(NULL, "\r\n"), numoftypes, 0);
            if (TmpAgainst==NULL){
                //printf("Type name doesn't exist in list.\n");
                return failure;
            }
            addAgainstMe(me,TmpAgainst);
            return success;
        }

        else
        {
            TmpAgainst = isTypeExist(typelist, strtok(against, ","), numoftypes, 0);
            if (TmpAgainst==NULL){
                //printf("Type name doesn't exist in list.\n");
                return failure;
            }
            addAgainstMe(me,TmpAgainst);

            for (int i = 1; i<comma; i++){
                TmpAgainst = isTypeExist(typelist, strtok(NULL, ","), numoftypes, 0);
                if (TmpAgainst==NULL){
                    //printf("Type name doesn't exist in list.\n");
                    return failure;
                }
                addAgainstMe(me,TmpAgainst);
            }


            TmpAgainst = isTypeExist(typelist, strtok(NULL, "\r\n"), numoftypes, 0);
            if (TmpAgainst==NULL){
                printf("Type name doesn't exist in list.\n");
                return failure;
            }
            addAgainstMe(me,TmpAgainst);

        }
        return success;
    }
    return failure;
}

// Add against other from line (Type)
status addAgainstOthersFromLine(Type *me , char * against,Type **typelist,int numoftypes){
    if (me!=NULL){
        int comma = 0;
        for (int i=0; i<strlen(against); i++) {
            if (',' == against[i]) comma++;
        }

        Type *TmpAgainst;
        if(comma==0)
        {
            TmpAgainst = isTypeExist(typelist, strtok(against, "\r\n"), numoftypes, 0);
            if (TmpAgainst==NULL){
                //printf("Type name doesn't exist in list.\n");
                return failure;
            }
            addAgainstOthers(me,TmpAgainst);
            return success;
        }
        if(comma==1)
        {
            TmpAgainst = isTypeExist(typelist, strtok(against, ","), numoftypes, 0);
            if (TmpAgainst==NULL){
                //printf("Type name doesn't exist in list.\n");
                return failure;
            }
            addAgainstOthers(me,TmpAgainst);

            TmpAgainst = isTypeExist(typelist, strtok(NULL, "\r\n"), numoftypes, 0);
            if (TmpAgainst==NULL){
                //printf("Type name doesn't exist in list.\n");
                return failure;
            }
            addAgainstOthers(me,TmpAgainst);
            return success;
        }

        else
        {
            TmpAgainst = isTypeExist(typelist, strtok(against, ","), numoftypes, 0);
            if (TmpAgainst==NULL){
                //printf("Type name doesn't exist in list.\n");
                return failure;
            }
            addAgainstOthers(me,TmpAgainst);

            for (int i = 1; i<comma; i++){
                TmpAgainst = isTypeExist(typelist, strtok(NULL, ","), numoftypes, 0);
                if (TmpAgainst==NULL){
                    //printf("Type name doesn't exist in list.\n");
                    return failure;
                }
                addAgainstOthers(me,TmpAgainst);
            }


            TmpAgainst = isTypeExist(typelist, strtok(NULL, "\r\n"), numoftypes, 0);
            if (TmpAgainst==NULL){
                //printf("Type name doesn't exist in list.\n");
                return failure;
            }
            addAgainstOthers(me,TmpAgainst);

        }
        return success;
    }
    return failure;
}

/** Add From Lines: Pokemon, Type, Against-Me, Against-Others */

// Add new type from line
status addTypeFromLine(char *line, Type **type, int numOfTypes)
{
    if(numOfTypes==0) return success;
    if(numOfTypes==1){
        char* tmpName = strtok(line, "\r\n");
        char* name = (char*)malloc(sizeof(strlen(tmpName))+1);
        strcpy(name,tmpName);
        type[0] = createType(name);
        return success;
    }

    if (numOfTypes==2){
        char* tmpName = strtok(line, ",");
        char* name = (char*)malloc(sizeof(strlen(tmpName))+1);
        strcpy(name,tmpName);
        type[0] = createType(name);
        tmpName = strtok(NULL, "\r\n");
        name = (char*)malloc(sizeof(strlen(tmpName))+1);
        strcpy(name,tmpName);
        type[1] = createType(name);
        return success;
    }

    char* tmpName = strtok(line, ",");
    char* name = (char*)malloc(sizeof(strlen(tmpName))+1);
    strcpy(name,tmpName);

    type[0] = createType(name);
    for (int i = 1; i< numOfTypes-1; i++){
        tmpName = strtok(NULL,",");
        name = (char*)malloc(sizeof(strlen(tmpName))+1);
        strcpy(name,tmpName);
        type[i] = createType(name);
    }
    tmpName = strtok(NULL, "\r\n");
    name = (char*)malloc(sizeof(strlen(tmpName))+1);
    strcpy(name,tmpName);

    type[numOfTypes-1] = createType(name);

    for(int i=0;i<numOfTypes;i++){
        if(type[i]==NULL) return failure;
    }

    return success;
}

// Add New Pokemon From line
status addPokemonFromLine(char *line,Pokemon **pokemon,int pokemonIndex,Type **typelist,int numoftypes)
{
    char* tmpName = strtok(line, ",");
    char* name = malloc((strlen(tmpName))+1);
    if (name==NULL){
        free(name);
        name = NULL;
        printf("No Memory Available");
        return failure;
    }
    strcpy(name,tmpName);

    char* tmpSpecies = strtok(NULL, ",");
    char* spicies = malloc((strlen(tmpSpecies))+1);
    if (spicies==NULL){
        free(spicies);
        spicies = NULL;
        printf("No Memory Available");
        return failure;
    }
    strcpy(spicies,tmpSpecies);

    float  Height = atof(strtok(NULL,","));
    float  Weight = atof(strtok(NULL,","));
    int Attack = atoi(strtok(NULL,","));

    char* tmptype = strtok(NULL, "\r\n");
    char* type = (char*)malloc(sizeof(strlen(tmptype))+1);
    if (type==NULL){
        free(type);
        type = NULL;
        printf("No Memory Available");
        return failure;
    }
    strcpy(type,tmptype);

    pokemon[pokemonIndex] = createPokemon(name, spicies, Height, Weight, Attack, type);
    if (pokemon[pokemonIndex] == NULL){
        return failure;
    }

    Type *tmpType = isTypeExist(typelist,pokemon[pokemonIndex]->type,numoftypes, 0);
    if(tmpType!=NULL) {
        tmpType->numOfPokemons++;
    }



    return  success;
}

/** Print Functions */

// Print All Pokemons
status printAllPokemons(Pokemon** pokemonList, int numOfPokemons) {
    if (pokemonList != NULL) {
        int i;
        for(i = 0; i < numOfPokemons; i++)
        {
            printByIndex(i, pokemonList, numOfPokemons);
        }
        return success;
    }
    return failure;

}

// Print All Types
status printAllTypes(Type **typeList , int numOfTypes)
{
    if (typeList != NULL) {
        int i;
        for(i = 0; i < numOfTypes; i++)
        {
            printByIndexType(i, typeList, numOfTypes);
        }
        return success;
    }
    return failure;
}

// Print Type by Index
status printByIndexType(int index ,Type **typeList , int numOfTypes)
{
    if(typeList!=NULL){
        printf("Type %s -- %d pokemons\n", typeList[index]->typeName, typeList[index]->numOfPokemons);
        if(typeList[index]->numOf_effectife_against_me>0) {
            printf("\tThese types are super-effective against %s:", typeList[index]->typeName);
            for(int j=0; j<typeList[index]->numOf_effectife_against_me;j++)
            {
                if(j!=0) printf(" ,");
                printf("%s", typeList[index]->effective_against_me[j]->typeName);
            }
            printf("\n");
        }

        if(typeList[index]->numOf_effectife_against_others>0) {
            printf("\t%s moves are super-effective against:", typeList[index]->typeName);
            for(int j=0; j<typeList[index]->numOf_effectife_against_others;j++)
            {
                if(j!=0) printf(" ,");
                printf("%s", typeList[index]->effective_against_others[j]->typeName);
            }
            printf("\n");
        }
        printf("\n");

        return success;
    }
    return failure;
}

// Print Pokemon By Index
status printByIndex(int index, Pokemon **pokemonList, int numOfPokemons)
{
    Pokemon* tmpPokemon = pokemonList[index];
    if (tmpPokemon != NULL){
        BioDetails *tmpBio = tmpPokemon->bio;
        printf("%s :\n%s, %s Type.\nHeight: %.2f m    Weight: %.2f kg    Attack: %d\n\n",
               tmpPokemon->name, tmpPokemon->species, tmpPokemon->type, tmpBio->height,tmpBio->weight, tmpBio->attack);
        return  success;
    }
    else{
        printf("The Pokemon doesn't exist.");
        return failure;
    }
    return failure;
}


/** Validation Functions */
// is type Exist
Type* isTypeExist(Type **type, char *typeName, int numOfTypes, int inList)
{
    for(int i = 0; i<numOfTypes; i++){
        if(strcmp(type[i]->typeName, typeName)==0){
            return type[i];
        }
    }
    if (inList == 1){ printf("Type name dosen't exist in list.\n");}
    if (inList == 0){ printf("Type name dosen't exist.\n");}
    return NULL;
}

//is type exsit + counting num of types (istype is using this func)
Type* isTypeExist2(Type **type, char *typeName, int inList)
{
    int i=0;
    while(type[i]!=NULL){
        if(strcmp(type[i]->typeName, typeName)==0){
            return type[i];
        }
        i++;
    }
    if (inList == 1){ printf("Type name dosen't exist in list.\n");}
    if (inList == 0){ printf("Type name dosen't exist.\n");}
    return NULL;
}

//return Type of pokemon only by char(using in pokemon.c)
Type* istype(char* d)
{
    return isTypeExist2(typeList, d, 1);
}

/**  Free Functions */
// Free Type
void freeType(Type** typelist,int numoftypes)
{
    if(typelist!=NULL){
        for(int i=0;i<numoftypes;i++)
        {
            if(typelist[i]!=NULL) {
                if(typelist[i]->typeName!=NULL) {
                    free(typelist[i]->typeName);
                    typelist[i]->typeName = NULL;
                }

                if(typelist[i]->effective_against_me){
                    free(typelist[i]->effective_against_me);
                    typelist[i]->effective_against_me = NULL;
                }

                if(typelist[i]->effective_against_others) {
                    free(typelist[i]->effective_against_others);
                    typelist[i]->effective_against_others = NULL;
                }

                if(typelist[i]) {
                    free(typelist[i]);
                    typelist[i] = NULL;
                }
            }
        }
        free(typelist);
        typelist = NULL;
    }
}

// Free Pokemon
void freePokemonList(Pokemon** pokemon,int numofpokemons)
{
    if(pokemon!=NULL) {
        for (int i = 0; i < numofpokemons; i++) {
            if (pokemon[i]!=NULL) {

                if(pokemon[i]->name!=NULL) {
                    free(pokemon[i]->name);
                    pokemon[i]->name = NULL;
                }

                if(pokemon[i]->species!=NULL){
                    free(pokemon[i]->species);
                    pokemon[i]->species = NULL;
                }

                if(pokemon[i]->type) {
                    free(pokemon[i]->type);
                    pokemon[i]->type = NULL;
                }

                if(pokemon[i]->bio!=NULL) {
                    free(pokemon[i]->bio);
                    pokemon[i]->bio = NULL;
                }

                free(pokemon[i]);
                pokemon[i] = NULL;
            }
        }
        free(pokemon);
        pokemon = NULL;
    }
}



/** Start Main */
int main(int argc, char *argv[]) {

    int numOfTypes = 0;
    int numOfPokemons = 0;
    int capacity = 0;

    /** Get User Arguments */
    if (argv[1] != NULL && argv[2] != NULL) {
        numOfTypes = atoi(argv[1]);
        capacity = atoi(argv[2]);

    }


    typeList = (Type **) malloc(numOfTypes * sizeof(Type *));
    if(typeList == NULL)
    {
        printf("No Memory Available\n");
        freeType(typeList,numOfTypes);
        return EXIT_SUCCESS;
    }


    /** Declare File info */
    FILE *Pokemonfile;
    char curLine[MAXCHARLINE];
    if (argv[3] == NULL) {
        printf("Could not open file %s", argv[3]);
        return EXIT_SUCCESS;
    }


    /** Open File */
    char *fileName = argv[3];
    Pokemonfile = fopen(fileName, "r");
    if (Pokemonfile == NULL) {
        printf("Could not open file: %s", fileName);
        return EXIT_SUCCESS;
    }

    int indexLines = 0;
    /** Counting nummber of pokemons*/
    while (fgets(curLine, MAXCHARLINE, Pokemonfile) != NULL ) {
        if (strcmp(curLine, "Pokemons\r\n")!=0 && indexLines != 0 && indexLines != 1 && curLine[0] != '\t' )
        {
            numOfPokemons++;
        }
        indexLines++;
    }
    rewind(Pokemonfile);

    Pokemon **pokemonList = (Pokemon**) malloc(numOfPokemons * sizeof(Pokemon*));
    if(pokemonList == NULL)
    {
        printf("No Memory Available\n");
        freeType(typeList, numOfTypes);
        freePokemonList(pokemonList,numOfPokemons);
        //printf("All the memory cleaned and the program is safely closed.‬‬ \n");
        return EXIT_SUCCESS;
    }

    int pokemonIndex = 0;
    indexLines = 0;
    status lineStatus;
    lineStatus = failure;
    Battle battle = NULL;


    /** this while loop:  Send each Line from file to match function */
    while (fgets(curLine, MAXCHARLINE, Pokemonfile) != NULL ) {
        if (indexLines != 0) {
            if (indexLines == 1) {

                char tmpLine[strlen(curLine)+1];
                strcpy(tmpLine, curLine);
                battle = createBattleByCategory(capacity , numOfTypes, tmpLine, equalPokemon, copyPokemon, freePokemon, getCategory , getAttack, printPokemon);
                lineStatus = addTypeFromLine(curLine, typeList, numOfTypes);
                if (lineStatus == failure)
                {
                    printf("couldn't add types to types list\n");
                    return EXIT_SUCCESS;
                }
            }
            else {
                if (curLine[0] == '\t') {
                    lineStatus = addAgainstFromLine(curLine, typeList, numOfTypes);
                    if (lineStatus==failure)
                    {
                        printf("couldn't add effective against list\n");
                        return EXIT_SUCCESS;
                    }
                }
                else
                {
                    if (strcmp(curLine, "Pokemons\r\n")!=0)
                    {
                        lineStatus = addPokemonFromLine(curLine, pokemonList, pokemonIndex,typeList,numOfTypes);
                        if (lineStatus==failure)
                        {
                            printf("couldn't add pokemon to pokemon list\n");
                            return EXIT_SUCCESS;
                        }
                        pokemonIndex++;
                    }
                }
            }
        }
        indexLines++;
    }
    fclose(Pokemonfile);

    if(battle!=NULL) {
        for (int i=0;i<numOfPokemons;i++)
        {
            status insertStatus = insertObject(battle, (element)pokemonList[i]);
            if(insertStatus==failure) {
                destroyBattleByCategory(battle);
            }
        }
    }
    freePokemonList(pokemonList, numOfPokemons);

    /** interface menu */

    int menu,check;
    char dummy;
    Type *myType;
    //char *charMyType = NULL;
    menu =1;
    while (menu != 6) {

        printf("please choose one of the following numbers:\n");
        printf("1 : Print All Pokemons by types\n");
        printf("2 : Print All Pokemons types\n");
        printf("3 : Insert Pokemon to battles training camp\n");
        printf("4 : Remove strongest Pokemon by type\n");
        printf("5 : Fight\n");
        printf("6 : Exit\n");
        int error =scanf("%d", &check);
        if (error<1){
            scanf("%s",&dummy);
            menu = 0;
        }
        else menu=check;
        switch (menu) {
            case 1: // Print All Pokemons by types
                displayObjectsByCategories(battle);
                break;

            case 2: //Print All Pokemons types
                printAllTypes(typeList , numOfTypes);
                break;

            case 3: //Insert pokemon to battle training camp
                if(true == false){break;}
                char *charMyType3 = (char *)malloc(sizeof(char)*MAXCHARLINE);
                if (charMyType3 == NULL)
                {
                    printf("No Memory Available\n");
                    free(charMyType3);
                    return EXIT_SUCCESS;
                }
                printf("Please enter Pokemon type name:\n");
                scanf("%s", charMyType3);
                myType = isTypeExist(typeList, charMyType3, numOfTypes, 0);
                if(myType==NULL)
                {
                    free(myType);
                    free(charMyType3);
                }
                else{
                    char *name = (char *)malloc(sizeof(char)*MAXCHARLINE);
                    printf("Please enter Pokemon name:\n");
                    scanf("%s",name);
                    char *spiceis = (char *)malloc(sizeof(char)*MAXCHARLINE);
                    printf("Please enter Pokemon species:\n");
                    scanf("%s",spiceis);
                    float  height, weight;
                    int attack;
                    printf("Please enter Pokemon height:\n");
                    scanf("%f",&height);
                    printf("Please enter Pokemon weight:\n");
                    scanf("%f",&weight);
                    printf("Please enter Pokemon attack:\n");
                    scanf("%d",&attack);
                    Pokemon *p = createPokemon(name, spiceis, height, weight, attack, charMyType3);
                    if(p==NULL){
                        puts("Pokemon not available.\n");
                    }
                    status insert = insertObject(battle, p);
                    if(insert == success){
                        printf("The Pokemon was successfully added.\n");
                        myType->numOfPokemons++;
                        printPokemon((element)p);
                    }
                    freePokemon((element)p);
                }
                break;

            case 4: //remove stongest pokemon
                if(true == false){break;}
                char *charMyType4 = (char *)malloc(sizeof(char)*MAXCHARLINE);
                if (charMyType4 == NULL)
                {
                    printf("No Memory Available\n");
                    free(charMyType4);
                    return EXIT_SUCCESS;
                }
                printf("Please enter Pokemon type name:\n");
                scanf("%s", charMyType4);
                myType = isTypeExist(typeList, charMyType4, numOfTypes, 0);
                if(myType==NULL)
                {
                    free(myType);
                    free(charMyType4);
                }
                else {
                    element e = removeMaxByCategory(battle, charMyType4);
                    if(e!=NULL){
                        printf("the strongest Pokemon was removed:\n");
                        myType->numOfPokemons--;
                        printPokemon(e);
                        freePokemon(e);
                    }
                }
                free(charMyType4);

                break;

            case 5: //Fight
                if(true == false){break;}
                char *charMyType5 = (char *)malloc(sizeof(char)*MAXCHARLINE);
                if (charMyType5 == NULL)
                {
                    printf("No Memory Available\n");
                    free(charMyType5);
                    return EXIT_SUCCESS;
                }
                printf("Please enter Pokemon type name:\n");
                scanf("%s", charMyType5);
                myType = isTypeExist(typeList, charMyType5, numOfTypes, 0);
                if(myType==NULL)
                {
                    free(myType);
                    free(charMyType5);
                }
                else{
                    char *name = (char *)malloc(sizeof(char)*MAXCHARLINE);
                    printf("Please enter Pokemon name:\n");
                    scanf("%s",name);
                    char *spiceis = (char *)malloc(sizeof(char)*MAXCHARLINE);
                    printf("Please enter Pokemon species:\n");
                    scanf("%s",spiceis);
                    float  height, weight;
                    int attack;
                    printf("Please enter Pokemon height:\n");
                    scanf("%f",&height);
                    printf("Please enter Pokemon weight:\n");
                    scanf("%f",&weight);
                    printf("Please enter Pokemon attack:\n");
                    scanf("%d",&attack);
                    Pokemon *p = createPokemon(name, spiceis, height, weight, attack, charMyType5);
                    if(p==NULL){
                        puts("Pokemon not available");
                    }
                    fight(battle, p);
                    freePokemon((element)p);
                }
                break;

            case 6:
                break;

            default:
                printf("Please‬‬ ‫‪choose‬‬ ‫‪a‬‬ ‫‪valid‬‬ ‫‪number.\n");
                break;
        }
    }

    //free Mem
    freeType(typeList,numOfTypes);
    destroyBattleByCategory(battle);
    printf("All the memory cleaned and the program is safely closed.\n");

    return EXIT_SUCCESS;
}
