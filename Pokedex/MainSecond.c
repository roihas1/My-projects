#include <stdio.h>
#include "LinkedList.h"
#include "Defs.h"
#include "Pokemon.h"
#include "BattleByCategory.h"



element copyElement (element elem)
{
    return copyPokemon((Pokemon*) elem);

}

status freeElement (element elem)
{
   return delete_pokemon((Pokemon *)elem);
}

int equalElement(element e1 , element e2){
    if(e1 == NULL || e2 == NULL)
        return -2;
    if(getPokemonAttack((Pokemon *)e1) > getPokemonAttack((Pokemon *)e2))
        return 1;
    if(getPokemonAttack((Pokemon *)e1) == getPokemonAttack((Pokemon *)e2))
        return 0;
    return -1;
}

status printElement(element elem)
{
    printPokemon((Pokemon *)elem);
    return success;
}
// return the first attack - second attack . also
//produce the attack of each element, The function transmits the information
//through the pointers received in the function.
int getAttack(element firstElem ,element secondElem ,int *attackFirst,int *attackSecond){

    if (firstElem == NULL)
        *attackFirst = 0;
    if (secondElem == NULL)
        *attackSecond = 0;
    if(inAgainstMeList((Pokemon*)firstElem,(Pokemon*)secondElem) == true){
        *attackFirst =  (getPokemonAttack((Pokemon *) firstElem) - 10);
    }
    else
        *attackFirst = getPokemonAttack((Pokemon *) firstElem);

    if(inAgainstMeList((Pokemon*)secondElem,(Pokemon*)firstElem) == true){
        *attackSecond = getPokemonAttack((Pokemon *) secondElem) - 10;
    }
    else
        *attackSecond = getPokemonAttack((Pokemon *) secondElem);

    return *attackFirst - *attackSecond;
}

char* getCategory(element element1){
    return getPokemonType((Pokemon *)element1);
}

type_of * type_by_name(type_of** t,char * name){
    //searching type by name in the type list.
    int i=0;
    while(t[i]!=NULL){
        if(strcmp(t[i]->type,name)==0)
            return t[i];
        i++;
    }
    return NULL;
}
// function to get pokemon details from the user.
//use in case 3 and 5 in the menu.
Pokemon * user_create_poke(type_of** t,char* type) {
    char pokeName[300];
    char pokeSpecies[300] ;
    char general[300];
    char *temp ;
    double height = 0;
    double weight = 0;
    int attack = 0;

    printf("Please enter Pokemon name:\n");
    scanf("%s", pokeName);
    printf("Please enter Pokemon species:\n");
    scanf("%s", pokeSpecies);
    printf("Please enter Pokemon height:\n");
    scanf("%s", general);
    height = strtod(general, &temp);
    printf("Please enter Pokemon weight:\n");
    scanf("%s", general);
    weight = strtod(general, &temp);
    printf("Please enter Pokemon attack:\n");
    scanf("%s", general);
    attack = (int) strtol(general, &temp, 10);

    bio_info *newBio = create_bio(height, weight, attack);
    if (newBio == NULL)
        return NULL;
    Pokemon *newPoke = create_pokemon(pokeName, pokeSpecies, type_by_name(t,type), newBio);
    if (newPoke == NULL)
        return NULL;
    delete_bio(newBio);
    return newPoke;
}

/////////////*************************************************************
int main(int argc,char*argv[]){

    type_of **pTypeOf=NULL;
    pTypeOf = (type_of **)calloc(atoi(argv[1]),sizeof(type_of));
    if(pTypeOf ==NULL){
        printf("No memory available.\n");
        return -1;
    }
    char *categories = " " ;//store all the line of categories to be sent to create battle
    char *temp1 =NULL;
    char types[300];
    char str[300];
    int num_of_categories = atoi(argv[1]);
    int capacity_in_type= atoi(argv[2]);
    FILE * file = fopen(argv[3],"r");
    if(file==NULL)
        return 0;
    int p_pokemons =0;
    bool end_file = false;
    fgets(str, 300, file);
    temp1 = fgets(types, 300, file);//store the categories for the battle
    categories = strdup(temp1);
    char *c;
    c = strtok(types, ",\n\r");
    int index1 = 0;
    if(strcmp(c,"Pokemons") == 0){//when the file is empty from pokemons and types
        c = NULL;
        end_file =true;
    }

    while (c != NULL) {
        pTypeOf[index1] = create_type(c);
        if (pTypeOf[index1] == NULL) {//if malloc func return NULL finish the file reading,Memory Problem.
            end_file = true;
            break;
        }
        c = strtok(NULL, ",\n\r");
        index1++;
    }

    Battle PokemonsBattles = createBattleByCategory(capacity_in_type, num_of_categories, categories, equalElement,
                                                    copyElement,
                                                    (freeFunction) freeElement, getCategory,
                                                        (getAttackFunction) getAttack,
                                                        (printFunction) printElement);

    if (PokemonsBattles == NULL && num_of_categories != 0) {
        printf("No memory available.\n");
        return -1;
    }

    while (end_file == false) {
        fgets(str, 300, file);
        if (strcmp(str, "Pokemons\r\n") != 0) {
            char *p = NULL;
            p = strtok(str, "\t ,-:\n\r");
            int index = 0;
            int other_me = 0;
            type_of *t1;
            while (p != NULL) {
                if (index == 0) {
                    t1 = type_by_name(pTypeOf, p);
                } else if (index == 3 && strcmp(p, "me") == 0) {//where to add the type according to the other_me flag
                    other_me = 1;
                } else if (index == 3 && strcmp(p, "other") == 0)
                    other_me = 2;
                if (other_me == 1 && strcmp(p, "me") != 0) {
                    if (add_to_against_me(t1, type_by_name(pTypeOf, p)) == failure) {
                        end_file = true;
                        break;
                    }
                }
                if (other_me == 2 && strcmp(p, "other") != 0) {
                    if (add_to_against_others(t1, type_by_name(pTypeOf, p)) == failure) {
                        end_file = true;
                        break;
                    }
                }
                p = strtok(NULL, "\t ,-:\n\r");
                index++;
            }

        } else if (strcmp(str, "Pokemons\r\n") == 0) {
            char *poke;
            char *po;
            char *name_poke = NULL;
            char *species = NULL;
            double height ;
            double weight ;
            int attack ;

            int i;

            while (feof(file) ==0) {//running all over the pokemons lines and phrasing 6 times to extract the values
                poke = fgets(str, 300, file);
                name_poke = NULL;
                name_poke = strtok(poke, ",");
                species = NULL;
                species = strtok(NULL, ",");
                po = strtok(NULL, ",");
                height = strtod(po, &po);
                po = strtok(NULL, ",");
                weight = strtod(po, &po);
                po = strtok(NULL, ",");
                attack = atoi(po);
                po = strtok(NULL, ",\n\r");
                for (i = 0; i < num_of_categories; i++) {
                    if (strcmp(pTypeOf[i]->type, po) == 0) {
                        bio_info *bio = create_bio(height, weight, attack);
                        Pokemon *New_p = create_pokemon(name_poke, species, pTypeOf[i], bio);
                        if (New_p == NULL || bio == NULL) {
                            //if creat Pokémon return NULL, fail malloc.
                            printf("Memory Problem\n");
                            end_file = true;
                            break;
                        }
                        //insert the pokemon to the battle structure
                        insertObject(PokemonsBattles, New_p);
                        p_pokemons++;
                        delete_bio(bio);

                    }

                }
            }
                // when finish creating all pokemons that sign to end the file readin
                end_file = true;
        }

    }
    fclose(file);

    int i;
    char s_name[300];
    char ch = 0;
    while(ch!='6') {

        printf("Please choose one of the following numbers:\n");
        printf("1 : Print all Pokemons by types\n");
        printf("2 : Print all Pokemons types\n");
        printf("3 : Insert Pokemon to battles training camp\n");
        printf("4 : Remove strongest Pokemon by type\n");
        printf("5 : Fight\n");
        printf("6 : Exit\n");

        scanf("%s", &ch);
        if (ch != '6') {
            switch (ch) {
                default:
                    printf("Please choose a valid number.\n");
                    break;
                case '1':{
                    displayObjectsByCategories(PokemonsBattles);
                    break;
                }
                case '2':{
                    //Print all Pokemon types
                    i =0;
                    for(i=0;i<num_of_categories;i++){
                        if(printType(pTypeOf[i]) == failure){
                            ch = 6;
                            break;
                        }
                    }
                    break;
                }
                case '3':{
                    // insert new pokemon to the battle camp
                     printf("Please enter Pokemon type name:\n");
                     scanf("%s",s_name);
                     if(type_by_name(pTypeOf,s_name) == NULL){
                        printf("Type name doesn't exist.\n");
                        break;
                    }
                     // check if the chosen category is full
                    if( getNumberOfObjectsInCategory(PokemonsBattles,s_name) == capacity_in_type){
                        printf("Type at full capacity.\n");
                        break;
                    }

                    Pokemon *newPoke = user_create_poke(pTypeOf,s_name); // create new pokemon
                    if(newPoke == NULL) {
                        printf("No memory available.\n");
                        ch = 6;
                        break;
                    }
                    if(insertObject(PokemonsBattles,newPoke) == failure){
                        delete_pokemon(newPoke);
                        break;
                    }
                    else{
                        printf("The Pokemon was successfully added.\n");
                        printPokemon(newPoke);
                        p_pokemons++;
                        break;
                    }
                }


                case '4':{
                    // remove the powerful pokemon from user's category
                    printf("Please enter type name:\n");
                    scanf("%s",s_name);
                    if(type_by_name(pTypeOf,s_name) == NULL){
                        printf("Type name doesn't exist.\n");
                        break;
                    }
                    if(getNumberOfObjectsInCategory(PokemonsBattles,s_name) == 0){
                        printf("There is no Pokemon to remove.\n");
                        break;
                    }
                    Pokemon *temp = removeMaxByCategory(PokemonsBattles,s_name);
                    if(temp != NULL) {
                        printf("The strongest Pokemon was removed:\n");
                        printPokemon(temp);
                        type_of *t = type_by_name(pTypeOf, temp->pokemon_type.type);// decrease the number of pokemons from the type
                        t->num_of_type--;
                        delete_pokemon(temp);
                        p_pokemons--;
                    }
                    else{
                        printf("There is no Pokemon to remove\n");
                    }
                    break;

                }


                case '5':{
                    // execute a fight between user pokemon and the strongest pokemon from the battle camp
                    printf("Please enter Pokemon type name:\n");
                    scanf("%s",s_name);
                    if(type_by_name(pTypeOf,s_name) == NULL){
                        printf("Type name doesn't exist.\n");
                        break;
                    }

                    Pokemon *newPoke = user_create_poke(pTypeOf,s_name);
                    if(newPoke == NULL) {
                        printf("No memory available.\n");
                        ch = 6;
                        break;
                    }

                    printf("You choose to fight with:\n");
                    printPokemon(newPoke);
                    if(p_pokemons == 0){
                        printf("There are no Pokemons to fight against you.\n");

                    }
                    else {
                         element  e =fight(PokemonsBattles, newPoke);
                         if(e != newPoke)
                            free(e);
                    }
                    type_of *t = type_by_name(pTypeOf, newPoke->pokemon_type.type);
                    t->num_of_type--;
                    delete_pokemon(newPoke);
                    break;

                }

            }
        }

    }
    // case 6 deleting all the allocated memory
    int j;
    for (j = 0; j < num_of_categories; ++j) {
        delete_types(pTypeOf[j]);
    }
    destroyBattleByCategory(PokemonsBattles);
    free(categories);
    free(pTypeOf);
    printf("All the memory cleaned and the program is safely closed.\n");
    return 0;
    }
