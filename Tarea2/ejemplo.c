#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main(){
    fork();
    fork();
    printf("Hello World!\n");
}
+------+------+------+------+------+------+------+------+\n
| Col2 | Col2 | Col3 | col4 | Col2 | Col2 | Col3 | col4 |\n
+------+------+------+------+------+------+------+------+\n
| Col2 |                                         | col4 |\n
+------+                                         +------+\n
| Col2 |                                         | col4 |\n
+------+                                         +------+\n
| Col2 |                                         | col4 |\n
+------+                                         +------+\n
| Col2 |                                         | col4 |\n
+------+                                         +------+\n
| Col2 |                                         | col4 |\n
+------+                                         +------+\n
| Col2 |                                         | col4 |\n
+------+------+------+------+------+------+------+------+\n
| Col2 | Col2 | Col3 | col4 | Col2 | Col2 | Col3 | col4 |\n
+------+------+------+------+------+------+------+------+\n
