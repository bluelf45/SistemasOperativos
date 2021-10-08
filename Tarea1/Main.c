
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


int main(){
    // Los directorios deben ser creados en cada estado, debido a que no deja crear directorios donde no hay carpetas padre
    // o sea, si no existe Laberinto, no se puede crear la carpeta 1 -> Laberinto/1/
    int check, cont, cont2=0;
    char dirname[20], security[20], security2[20];
    char* list[3] = {"/1", "/2", "/3"};
    FILE* fp;
    int randoms[3];
    char* Contenido[3] = {"1, Los hurones del", "2, profesor de sistemas operativos son", "3, tiernos"};
    srand(time(0));
    for(int i = 0; i<3; i++){
        randoms[i] = rand()%10;
        printf("%d\n", randoms[i]);
    }

    // Crea La primera Carpeta del Laberinto
    check = mkdir("Laberinto", 0.700);
    if(check){
        printf("El laberinto ya estaba creado\n");
        return 0;
    }
    for(int x=0; x<3; x++){
        //  crea la primera generacion de carpetas, Laberinto/x/
        // Se usa security y security2 para guardar bien el string Laberinto/x/ y Laberinto/x/y/ en cada caso correspondiente
        strcpy(dirname, "Laberinto");
        strcat(dirname, list[x]);
        strcpy(security, dirname);
        mkdir(dirname, 0.700);
        cont=0;
        for(int x2=0; x2 < 3; x2++){
            strcpy(dirname,security);
            strcat(dirname, list[x2]);
            strcpy(security2, dirname);
            mkdir(dirname, 0.700);
            for(int x3=0; x3 < 3; x3++){
                strcpy(dirname,security2);
                strcat(dirname, list[x3]);
                mkdir(dirname, 0.700);
                cont++;
                if(cont==randoms[cont2] && cont2<3){
                    cont=10;
                    strcat(dirname, "/frase.txt");
                    fp=fopen(dirname, "w");
                    if(fp != NULL){
                        fprintf(fp,"%s", Contenido[cont2]);
                        cont2++;
                        fclose(fp);
                    }
                }
            }
        }
    }
    printf("Laberinto Creado\n");
    return 0;
}
/*
fp=fopen(dirname, "w");
if(fp!= NULL){
    fclose(fp);
}
}*/
