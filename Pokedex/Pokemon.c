//
// Created by roihas on 12/2/21.
//

//
// Created by ise on 11/19/21.
//
#include <string.h>
#include <stddef.h>
#include "Pokemon.h"
#include "Defs.h"


Pokemon *create_pokemon(char* name,char* species, type_of* pokemon_type, bio_info* pokemon_bio){
    Pokemon* poke =(Pokemon*)malloc(sizeof(Pokemon));
    if(poke ==NULL){
        printf("Memory Problem\n");
        return NULL;
    }
    poke->name = (char *) malloc(strlen(name)+1);
    if(poke->name == NULL){
        free(poke);
        printf("Memory Problem\n");
        return NULL;
    }
    strcpy(poke->name,name);
    poke->species = (char *) malloc(strlen(species)+1);
    if(poke->species == NULL){
        free(poke);
        free(poke->name);
        printf("Memory Problem\n");
        return NULL;
    }
    strcpy(poke->species, species);
    pokemon_type->num_of_type++;
    poke->pokemon_type =  *pokemon_type;
    poke->pokemon_bio = *pokemon_bio;
    return poke;
}

type_of *create_type(char * type){
    type_of* type_o = (type_of*) malloc(sizeof(type_of));
    if(type_o == NULL){
        printf("Memory Problem\n");
        return NULL;
    }
    type_o->type = (char*)malloc(strlen(type)+1);
    if(type_o->type == NULL){
        free(type_o);
        printf("Memory Problem\n");
        return NULL;
    }
    strcpy(type_o->type,type);
    type_o->num_of_type=0;
    type_o->countMe = 0;
    type_o->countOthers= 0;
    type_o->effective_against_me = NULL;
    type_o->effective_against_others = NULL;
    return type_o;
}
bio_info *create_bio(double height,double weight,int attack){

    bio_info * bioInfo = (bio_info*) malloc(sizeof(bio_info));
    if(bioInfo == NULL){
        printf("Memory Problem\n");
        return NULL;
    }
    bioInfo->height = height;
    bioInfo->weight = weight;
    bioInfo->attack = attack;
    return bioInfo;
}
status add_to_against_me(type_of* a,type_of* b){
    if(a == NULL || b == NULL)
        return failure;
    int i;
    for(i = 0; i<a->countMe;i++){
        if(strcmp(a->type,b->type)==0)
            return failure;
    }
    if(a->countMe == 0) {
        a->effective_against_me = (type_of **) malloc(sizeof(type_of ));
        if(a->effective_against_me == NULL) {//malloc returned NULL.
            printf("Memory Problem\n");
            return failure;
        }
        a->countMe++;
        a->effective_against_me[a->countMe-1] = b;
        return success;
    }

    a->effective_against_me = (type_of**) realloc(a->effective_against_me, sizeof(a->effective_against_me)+
                                                                           sizeof(type_of));

    a->effective_against_me[a->countMe] = b;
    a->countMe++;
    return success;
}
status add_to_against_others(type_of* a, type_of* b){
    if(a == NULL || b == NULL)
        return failure;
    int i;
    for (i=0;i<a->countOthers;i++){
        if(strcmp(a->type,b->type)==0)
            return failure;
    }
    if(a->countOthers ==0){
        a->effective_against_others= (type_of**) malloc(sizeof(type_of));
        if(a->effective_against_others ==NULL){
            printf("Memory Problem\n");
            return failure;
        }
        a->countOthers++;
        a->effective_against_others[a->countOthers-1] = b;

        return success;
    }

    a->effective_against_others = (type_of**) realloc(a->effective_against_others, sizeof(a->effective_against_others)+
                                                                                   sizeof(type_of));

    a->effective_against_others[a->countOthers] = b;
    a->countOthers++;
    return success;
}

status delete_from_against_me(type_of*  a,char * b ){
    if(a == NULL)
        return failure;
    int i ;
    for (i=0;i< a->countMe;i++){
        if(strcmp(a->effective_against_me[i]->type,b ) == 0){
            if( i == a->countMe-1) {
                a->effective_against_me[i] =NULL;
                a->effective_against_me = (type_of **) realloc(a->effective_against_me,
                                                               sizeof(type_of) * (a->countMe - 1));

                a->countMe--;
                return success;
            }
            for(int j=i;j<a->countMe-1;j++) {
                a->effective_against_me[j] = a->effective_against_me[j+1];
            }
            a->effective_against_me = (type_of**) realloc(a->effective_against_me , sizeof(type_of)*(a->countMe-1));

            a->countMe--;

            return success;
        }
    }
    return failure;
}
status delete_from_against_others(type_of* a,char *b){
    if( a == NULL)
        return failure;
    int i;
    for(i=0;i<a->countOthers;i++) {
        if (strcmp(a->effective_against_others[i]->type, b) == 0) {
            if(i == a->countOthers-1)
            {
                a->effective_against_others[i] = NULL;
                a->effective_against_others = (type_of **) realloc(a->effective_against_others,
                                                                   sizeof(type_of) * (a->countOthers - 1));

                a->countOthers--;
                return success;
            }
            for (int j = i; j < a->countOthers-1; ++j) {
                a->effective_against_others[j] = a->effective_against_others[j+1];
            }

            a->effective_against_others = (type_of **) realloc(a->effective_against_others,
                                                               sizeof(type_of) * (a->countOthers - 1));

            a->countOthers--;
            return success;
        }
    }

    return failure;
}

status to_string_pokemon(Pokemon* pokemon){
    if(pokemon == NULL)
        return failure;
    type_of t = pokemon->pokemon_type;
    bio_info bTmp =  pokemon->pokemon_bio;
    printf("%s :\n",pokemon->name);
    printf("%s, %s Type.\n",pokemon->species,t.type);
    printf("Height: %.2f m    Weight: %.2f kg    Attack: %d\n\n",bTmp.height,bTmp.weight,bTmp.attack);

    return success;
}

status to_string_type(type_of* typeOf){
    if(typeOf ==NULL)
        return failure;
    printf("Type %s -- %d pokemons\n",typeOf->type,typeOf->num_of_type );
    if(typeOf->countMe !=0 ){

        printf("\tThese types are super-effective against %s:",typeOf->type);
        for(int i = 0; i < typeOf->countMe-1; ++i) {
            printf("%s ,", typeOf->effective_against_me[i]->type);
        }
        printf("%s\n",typeOf->effective_against_me[typeOf->countMe-1]->type);
    }

    if(typeOf->countOthers !=0){

        printf("\t%s moves are super-effective against:",typeOf->type);
        for (int i = 0; i < typeOf->countOthers-1; ++i) {
            printf("%s ,",typeOf->effective_against_others[i]->type);

        }
        printf("%s\n",typeOf->effective_against_others[typeOf->countOthers-1]->type);

    }
    printf("\n");
    return success;
}
void delete_pokemon(Pokemon* p){
    free(p->name);
    free(p->species);
    free(p);

}
void delete_types(type_of * p){

    free(p->effective_against_others);
    free(p->effective_against_me);
    free(p->type);
    free(p);
}

void delete_bio(bio_info* b){
    free(b);
}