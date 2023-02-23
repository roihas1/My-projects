//
// Created by roihas on 12/10/21.
//

#ifndef HW3_POKEMON_H
#define HW3_POKEMON_H
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
status printPokemon(Pokemon*);
status printType(type_of*);
status delete_pokemon(Pokemon * p);
void delete_types(type_of * p);
void delete_bio(bio_info* b);

int getPokemonAttack(Pokemon *p);
char* getPokemonType(Pokemon *p);
bool inAgainstMeList(Pokemon *pokemon,Pokemon *p2);
Pokemon *copyPokemon(Pokemon *elem);
#endif //HW3_POKEMON_H
