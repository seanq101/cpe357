#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

#include "mypwd.h"

int main(int argc, char * argv[]){
	list_dir(".");
	return 0;
}


void list_dir (const char * dir_name)
{
    DIR * d;
    struct dirent *e1, *e2;
    char parent[200];

    d = opendir(dir_name);

    e1 = readdir(d);
    e2 = readdir(d);
    parent = strncpy(parent, e2->d_name);
    closedir(dir_name);

    list_dir(parent);
}


/*
    stat(parent, &sb2);
    if (stat(parent, &sb2) == -1) {
        perror("stat2");
        printf("parent name: \n");
        exit(EXIT_FAILURE);
    }
    parentIno = (long) sb2.st_ino;


    if (d == NULL) {
        printf("Cannot open dircetory '%s'\n", parent);
    }

    if (childIno == parentIno) {
        while ((e = readdir(d)) != NULL) {
            printf("base case %s\n", e->d_name);
        break;
         }

    }else{
        list_dir(parent);

    }
*/
    /*code above here is really messed up*/

    /* After going through all the entries, close the directory. */
 