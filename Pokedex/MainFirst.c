#include <stdio.h>
#include "Defs.h"
#include "Pokemon.h"


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
int main(int argc,char*argv[]) {
    Pokemon **Pokedex =NULL;
    Pokedex = (Pokemon**) calloc(atoi(argv[2]),sizeof(Pokemon));
    if(Pokedex ==NULL){
        printf("Memory Problem\n");
        return 0;
    }

    type_of **pTypeOf=NULL;
    pTypeOf = (type_of **)calloc(atoi(argv[1]),sizeof(type_of));

    if(pTypeOf ==NULL){
        printf("Memory Problem\n");
        return 0;
    }
    char types[300] ;
    int num_of_type = atoi(argv[1]);
    int num_of_pokemon= atoi(argv[2]);

    char str[300];
    FILE * file = fopen(argv[3],"r");
    if(file==NULL)
        return 0;
    type_of * type;
    int line =1;
    bool end_file = false;
    while(end_file==false) {
        fgets(str, 300, file);
        line++;
        if(line ==2) {
            fgets(types, 300, file);
            char *c;
            c = strtok(types, ",\n\r");
            int p = 0;
            while (c != NULL) {
                pTypeOf[p] = create_type(c);
                if(pTypeOf[p]==NULL){//if malloc func return NULL finish the file reading,Memory Problem.
                    end_file =true;
                    break;
                }
                c = strtok(NULL, ",\n\r");
                p++;
            }
        }
        else if(strcmp(str, "Pokemons\r\n") != 0) {
            char *p = strtok(str, "\t ,-:\n\r");
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
                if (other_me == 1 && strcmp(p,"me")!=0) {
                    if(add_to_against_me(t1, type_by_name(pTypeOf, p)) == failure) {
                        end_file = true;
                        break;
                    }
                }
                if (other_me == 2 && strcmp(p,"other") != 0) {
                    if(add_to_against_others(t1, type_by_name(pTypeOf, p)) == failure){
                        end_file =true;
                        break;
                    }
                }
                p = strtok(NULL, "\t ,-:\n\r");
                index++;
            }
        }
        else if(strcmp(str, "Pokemons\r\n") == 0) {
            char * poke ;
            char *po;
            char *name_poke=NULL;
            char *species=NULL;
            double height=0;
            double weight=0;
            int attack =0;
            int p_pokemons =0;
            int i;
            int j;
            poke =fgets(str, 300, file);
            for(j=0;j<num_of_pokemon;j++) {//running all over the pokemons lines and phrasing 6 times to extract the values
                name_poke =NULL;
                name_poke =strtok(poke, ",");
                species =NULL;
                species = strtok(NULL, ",");
                po = strtok(NULL,",");
                height = strtod(po,&po);
                po = strtok(NULL,",");
                weight =strtod(po,&po);
                po =strtok(NULL,",");
                attack = atoi(po);
                po =strtok(NULL,",\n\r");
                for(i=0;i<num_of_type;i++){
                    if(strcmp(pTypeOf[i]->type,po)==0){
                        bio_info *bio = create_bio(height, weight, attack);
                        Pokemon *New_p = create_pokemon(name_poke, species, pTypeOf[i],bio);
                        if(New_p ==NULL||bio == NULL){
                            //if creat Pokémon return NULL, fail malloc.
                            end_file = true;
                            break;
                        }
                        Pokedex[p_pokemons] = New_p;
//                        delete_bio(bio);
                        free(bio);
                    }
                }
                p_pokemons++;
                poke = fgets(str, 300, file);
            }
            // when finish creating all pokemons that sign to end the file reading
            end_file =true;
        }

    }
    fclose(file);
    char s_name[300] ;
    char add_name[300];
    char name_print7[300];
    char type_to_print8[300];
    int i;
    int j;
    int k;
    char ch = 0;
    while(ch!='9'){

        printf("Please choose one of the following numbers:\n");
        printf("1 : Print all Pokemons\n");
        printf("2 : Print all Pokemons types\n");
        printf("3 : Add type to effective against me list\n");
        printf("4 : Add type to effective against others list\n");
        printf("5 : Remove type from effective against me list\n");
        printf("6 : Remove type from effective against others list\n");
        printf("7 : Print Pokemon by name\n");
        printf("8 : Print Pokemons by type\n");
        printf("9 : Exit\n");

        scanf("%s", &ch);
        if(ch !='9'){
            switch(ch) {
                default:
                    printf("Please choose a valid number.\n");
                    break;
                case '1': {
                    //Print all Pokémon in the Pokedex
                    for(i=0;i<num_of_pokemon;i++){
                        if(to_string_pokemon(Pokedex[i]) == failure){
                            ch =9;
                            break;
                        }
                    }
                    break;
                }
                case '2': {
                    //Print all Pokemon types
                    i =0;
                    for(i=0;i<num_of_type;i++){
                        if(to_string_type(pTypeOf[i]) == failure){
                            ch = 9;
                            break;
                        }
                    }
                    break;
                }

                case '3': {
                    // Add type to effective against me list
                    i = 0;
                    j = 0;
                    k = 0;
                    bool flag =false;
                    printf("Please enter type name:\n");
                    scanf("%s",s_name);
                    while(pTypeOf[i]!=NULL){//running over the type list to check if exist
                        if(strcmp(pTypeOf[i]->type,s_name)==0){
                            printf("Please enter type name to add to %s effective against me list:\n",s_name);
                            scanf("%s",add_name);
                            type_of * destType =pTypeOf[i];
                            while(pTypeOf[j]!= NULL){//checking if the 2th name exist in the type list
                                if(strcmp(pTypeOf[j]->type,add_name)==0 && destType->effective_against_me != NULL){
                                    while(destType->effective_against_me[k]!=NULL){//checkin if 2th name exist in the effective against me list
                                        if(strcmp(destType->effective_against_me[k]->type,add_name)==0){
                                            printf("This type already exist in the list.\n");
                                            flag =true;
                                            break;
                                        }
                                        else if(k == destType->countMe-1){
                                            if(add_to_against_me(destType,pTypeOf[j]) ==failure){
                                                ch =9;
                                                flag=true;
                                                break;
                                            }
                                            if(to_string_type(destType)==failure){
                                                ch =9;
                                            }
                                            flag=true;
                                            break;
                                        }
                                        k++;
                                    }//end while loop 3
                                }
                                else if(strcmp(pTypeOf[j]->type,add_name)==0 && destType->effective_against_me == NULL){
                                    if(add_to_against_me(destType,pTypeOf[j]) ==failure){
                                        ch =9;
                                    }
                                    if(to_string_type(destType)==failure){
                                        ch =9;
                                    }
                                    flag=true;
                                    break;
                                }
                                else if(j == num_of_type-1 && flag==false){
                                    printf("Type name doesn't exist.\n");
                                    flag =true;
                                    break;
                                }
                                j++;
                            }//end while loop 2
                        }
                        else if(i == num_of_type-1 && flag ==false){
                            printf("Type name doesn't exist.\n");
                            break;
                        }
                        i++;
                    }//end while loop 1
                    break;
                }

                case '4':{
                    // Add type to effective against others list
                    i = 0;
                    j =0;
                    k =0;
                    bool flag =false;
                    printf("Please enter type name:\n");
                    scanf("%str",s_name);
                    while(pTypeOf[i]!=NULL){//running over the type list to check if exist
                        if(strcmp(pTypeOf[i]->type,s_name)==0){
                            printf("Please enter type name to add to %s effective against others list:\n",pTypeOf[i]->type);
                            scanf("%str",add_name);
                            type_of * destType =pTypeOf[i];
                            while(pTypeOf[j]!= NULL){//checking if the 2th name exist in the type list
                                if(strcmp(pTypeOf[j]->type,add_name)==0 && destType->effective_against_others!= NULL){
                                    while(destType->effective_against_others[k]!=NULL){//checkin if 2th name exist in the effective against other list
                                        if(strcmp(destType->effective_against_others[k]->type,add_name)==0){
                                            printf("This type already exist in the list.\n");
                                            flag =true;
                                            break;
                                        }
                                        else if(k == destType->countOthers-1){
                                            if(add_to_against_others(destType,pTypeOf[j]) == failure){
                                                ch =9;
                                                flag=true;
                                                break;
                                            }
                                            if(to_string_type(destType) == failure){
                                                ch =9;
                                            }
                                            flag =true;
                                            break;
                                        }
                                        k++;
                                    }//end while loop 3
                                }
                                else if(strcmp(pTypeOf[j]->type,add_name)==0 && destType->effective_against_others== NULL){
                                    if(add_to_against_others(destType,pTypeOf[j])==failure){
                                        ch=9;
                                    }
                                    if(to_string_type(destType)==failure){
                                        ch=9;
                                    }
                                    flag=true;
                                    break;
                                }
                                else if(j == num_of_type-1 && flag==false){
                                    printf("Type name doesn't exist.\n");
                                    flag =true;
                                    break;
                                }
                                j++;
                            }//end while loop 2
                        }
                        else if(i == num_of_type-1 && flag ==false){
                            printf("Type name doesn't exist.\n");
                            break;
                        }
                        i++;
                    }//end while loop 1
                    break;
                }

                case '5':{
                    //Remove type from effective against me list
                    i = 0;
                    j =0;
                    k =0;
                    bool flag =false;
                    printf("Please enter type name:\n");
                    scanf("%str",s_name);
                    while(pTypeOf[i]!=NULL){//running over the type list to check if exist
                        if(strcmp(pTypeOf[i]->type,s_name)==0){
                            printf("Please enter type name to remove from %s effective against me list:\n",s_name);
                            scanf("%str",add_name);
                            type_of * destType =pTypeOf[i];
                            while(pTypeOf[j]!= NULL){//checking if the 2th name exist in the type list
                                if(strcmp(pTypeOf[j]->type,add_name)==0&& destType->effective_against_me != NULL){
                                    while(destType->effective_against_me[k]!=NULL){//checkin if 2th name exist in the effective against me list
                                        if(strcmp(destType->effective_against_me[k]->type,add_name)==0){
                                            if(delete_from_against_me(destType,add_name) == failure){
                                                ch =9;
                                                flag=true;
                                                break;
                                            }
                                            if(to_string_type(destType) == failure){
                                                ch =9;
                                            }
                                            flag =true;
                                            break;
                                        }
                                        else if(k == destType->countMe-1){
                                            printf("Type name doesn't exist in the list.\n");
                                            flag=true;
                                            break;
                                        }
                                        k++;
                                    }
                                }
                                else if(j == num_of_type-1 && flag==false){
                                    printf("Type name doesn't exist in the list.\n");
                                    flag =true;
                                    break;
                                }
                                j++;
                            }
                        }
                        else if(i == num_of_type-1 && flag ==false){
                            printf("Type name doesn't exist.\n");
                            break;
                        }
                        i++;
                    }
                    break;
                }
                case '6': {
                    // Remove type from effective against others list
                    i = 0;
                    j =0;
                    k =0;
                    bool flag =false;
                    printf("Please enter type name:\n");
                    scanf("%str", s_name);
                    while(pTypeOf[i]!=NULL){//checking if the name exist in the type list
                        if(strcmp(pTypeOf[i]->type, s_name) == 0){
                            printf("Please enter type name to remove from %s effective against others list:\n",pTypeOf[i]->type);
                            scanf("%str",add_name);
                            type_of * destType =pTypeOf[i];
                            while(pTypeOf[j]!= NULL){//checking if the 2th name exist in the type list
                                if(strcmp(pTypeOf[j]->type,add_name)==0 && destType->effective_against_others!=NULL){
                                    while(destType->effective_against_others[k]!=NULL){//checkin if 2th name exist in the effective against other list
                                        if(strcmp(destType->effective_against_others[k]->type,add_name)==0){
                                            if(delete_from_against_others(destType,add_name) == failure){
                                                ch =9;
                                                flag=true;
                                                break;
                                            }
                                            if(to_string_type(destType) == failure){
                                                ch = 9;
                                            }
                                            flag =true;
                                            break;
                                        }
                                        else if(k == destType->countOthers-1){
                                            printf("Type name doesn't exist in the list.\n");
                                            flag =true;
                                            break;
                                        }
                                        k++;
                                    }
                                }
                                else if(j == num_of_type-1 && flag ==false){
                                    printf("Type name doesn't exist in the list.\n");
                                    flag =true;
                                    break;
                                }
                                j++;
                            }
                        }
                        else if(i == num_of_type-1 && flag ==false){
                            printf("Type name doesn't exist.\n");
                            break;
                        }
                        i++;
                    }

                    break;
                }

                case '7': {
                    //Print Pokemon by name
                    i = 0;
                    printf("Please enter Pokemon name:\n");
                    scanf("%str", name_print7);
                    while(Pokedex[i] != NULL){
                        if(strcmp(Pokedex[i]->name, name_print7) == 0){
                            if(to_string_pokemon(Pokedex[i]) == failure){
                                ch = 9;
                            }
                            break;
                        }
                        else if(i == num_of_pokemon-1){
                            printf("The Pokemon doesn't exist.\n");
                            break;
                        }
                        i++;
                    }
                    break;
                }
                case '8': {
                    //Print Pokemons by type
                    j =0;
                    i=0;
                    bool flag =false;
                    printf("Please enter type name:\n");
                    scanf("%str", type_to_print8);
                    while(pTypeOf[i]!=NULL){//if name exist in type list
                        if(strcmp(pTypeOf[i]->type, type_to_print8) == 0){
                            if(pTypeOf[i]->num_of_type !=0){
                                printf("There are %d Pokemons with this type:\n", pTypeOf[i]->num_of_type);
                                while(Pokedex[j] != NULL){//printing all the pokemons with the same name type
                                    if(strcmp(Pokedex[j]->pokemon_type.type, type_to_print8) == 0){
                                        if(to_string_pokemon(Pokedex[j]) == failure){
                                            ch =9;
                                            flag =true;
                                            break;
                                        }
                                        j++;
                                        flag = true;
                                    } else j++;
                                }

                            }
                            else {
                                printf("There are no Pokemons with this type.\n");
                                break;
                            }
                        }
                        else if(i == num_of_type-1 && !flag){
                            printf("Type name doesn't exist.\n");
                            break;
                        }
                        i++;
                    }
                    break;
                }

            }
        }
    }
    //cleaning the memory when typing '9'
    for (j = 0; j < num_of_pokemon; ++j) {
        delete_pokemon(Pokedex[j]);
    }
    for (j = 0; j < num_of_type; ++j) {
        delete_types(pTypeOf[j]);
    }
    free(Pokedex);
    free(pTypeOf);
    printf("All the memory cleaned and the program is safely closed.\n");
    return 0;
}