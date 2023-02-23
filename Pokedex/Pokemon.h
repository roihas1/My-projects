//
// Created by roihas on 12/2/21.
//

#ifndef HW2_POKEMON_H
#define HW2_POKEMON_H
#endif //HW2_POKEMON_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Defs.h"


typedef  struct  type_of_Pokemon{
    char *type;
    int num_of_type;
    int countMe;
    int countOthers;
    struct type_of_Pokemon** effective_against_others;
    struct type_of_Pokemon** effective_against_me;
}type_of;

typedef struct biological_info{
    double height;
    double weight;
    int attack;
} bio_info;

 typedef struct  pokemon_a{
    char *name;
    char *species;
    struct type_of_Pokemon pokemon_type;
    struct biological_info pokemon_bio;
}Pokemon;

Pokemon *create_pokemon(char* name,char* species,type_of* pokemon_type, bio_info* pokemon_bio);
type_of *create_type(char* type);
bio_info *create_bio(double height,double weight,int attack);
status add_to_against_me(type_of* a,type_of* b);
status add_to_against_others(type_of* a, type_of* b);
status delete_from_against_me(type_of* a, char* b);
status delete_from_against_others(type_of* a,char* b);
status to_string_pokemon(Pokemon*);
status to_string_type(type_of*);
void delete_pokemon(Pokemon * p);
void delete_types(type_of * p);
void delete_bio(bio_info* b);

