#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void cambiar(char* temp, char* msg){
    for(int cont=2; cont<strlen(temp); cont++){
        strncat(msg, &temp[cont], 1);
    }
}
int main(){
    char dirname[30], security[30], security2[30];
    char temp[43], Mensaje[90];
    strcpy(Mensaje, "");
    int cont2=0;
    char* list[3] = {"/1", "/2", "/3"};
    FILE* fp;
    for(int x=0; x<3; x++){
        strcpy(dirname, "Laberinto");
        strcat(dirname, list[x]);
        strcpy(security, dirname);
        for(int x2=0; x2 < 3; x2++){
            strcpy(dirname,security);
            strcat(dirname, list[x2]);
            strcpy(security2, dirname);;
            for(int x3=0; x3 < 3; x3++){
                if(cont2>=3){
                    printf("%s\n", Mensaje);
                    return 0;
                }
                strcpy(dirname,security2);
                strcat(dirname, list[x3]);
                strcat(dirname, "/frase.txt");
                if( access (dirname, F_OK) == 0){
                    fp = fopen(dirname, "r");
                    if(fp != NULL){
                        cont2++;
                        fgets(temp, 60, fp);
                        cambiar(temp, Mensaje);
                        fclose(fp);
                        strcpy(temp, "");
                    }
                }
            }
        }
    }
}
