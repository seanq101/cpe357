#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char * argv[]){
	list_dir(".");
	return 0;
}


void list_dir (const char * dir_name)
{
    DIR * d;
    struct dirent *e;
    struct stat sb;
    struct stat sb2;
    long childIno;
    long parentIno;
    char parent[200];

    stat(dir_name, &sb);
    if (stat(dir_name, &sb) == -1) {
        perror("stat");
        exit(EXIT_FAILURE);
    }

    childIno = (long) sb.st_ino;

    /* get parent dir name */

    snprintf(parent, sizeof(parent), "%s/..", dir_name);
    d = opendir(parent);


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

    /*below code is really messed up*/
    if (childIno == parentIno) {
        while ((e = readdir(d)) != NULL) {
            printf("base case %s\n", e->d_name);
        break;
         }

    }else{
        list_dir(parent);

    }

    /*code above here is really messed up*/

    /* After going through all the entries, close the directory. */
    closedir (d);
}