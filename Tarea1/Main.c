
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(){
    int check;
    char dirname[20];
    char security[20];
    char security2[20];
    char* list[3] = {"/1", "/2", "/3"};
    for(int x=0; x<3; x++){
        strcpy(dirname, "Laberinto");
        strcat(dirname, list[x]);
        strcpy(security, dirname);
        for(int x2=0; x2 < 3; x2++){
            strcpy(dirname,security);
            strcat(dirname, list[x2]);
            strcpy(security2, dirname);
            for(int x3=0; x3 < 3; x3++){
                strcpy(dirname,security2);
                strcat(dirname, list[x3]);
                printf("%s\n", dirname);
            }
        }
    }
    return 0;
}
