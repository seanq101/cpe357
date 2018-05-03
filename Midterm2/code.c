#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <pwd.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>


unsigned char makebyte(const int bits[]) {
    if(bits == NULL){
        return 0;
    }
    unsigned char res;
    int i, tempi, tempVal;
    res = 0;
    for ( i = 0; i < 8 ; i++ ){
        if(bits[i] == 1){
            tempi = i;
            tempVal = 1;
            while(7 - tempi > 0){
                tempVal = tempVal * 2;
                tempi++;
            }
            res += tempVal;
        }
    }
    return res;
}

char * sprintbits(char *buffer, unsigned int num){
    int offset;
    unsigned long currentPow;
    currentPow = 1;
    while(currentPow < num){
        currentPow = currentPow * 2;
        printf("%lu, %u\n", currentPow, num);
    }

    offset = 0;
    while(currentPow > 0){
        printf("%lu, %u\n", currentPow, num);
        if(num >= currentPow){
            num = num - currentPow;
            buffer[offset] = '1';
        }else{
            buffer[offset] = '0';
        }
        offset++;
        currentPow = currentPow / 2;
    }
    return buffer;
}

int isleafdirectory(const char *path) {
    struct stat sb;
    struct dirent *dent;
    DIR * d;
    if(path == NULL){
        perror(path);
        exit(EXIT_FAILURE);
    }
    if((d = opendir(path)) == NULL){
        perror(path);
        closedir(d);
        exit(EXIT_FAILURE);
    }

    while( (dent = readdir(d)) != NULL){
        stat(dent->d_name, &sb);
        if(S_ISDIR(sb.st_mode) && strcmp(dent->d_name, ".") != 0 && strcmp(dent->d_name, "..") != 0){
            return 0;
        }
    }
    closedir(d);
    return 1;
}

int shareread(char *fname){
    struct stat sb;

    if(stat(fname, &sb) < 0){
        perror(fname);
        
        return 0;
    }
    if( ((sb.st_mode & S_IRUSR) != 0) || ((sb.st_mode & S_IRGRP) != 0) || ((sb.st_mode & S_IROTH) != 0) ){
        chmod(fname, sb.st_mode|0444);
        return 1;
    }
    return 0;
}

int main(){

    struct passwd pwent;
    struct passwd *pwentp;
    char buf[1024];
    uid_t temp;
    temp = getuid();
    if (getpwuid_r(temp, &pwent, buf, sizeof buf, &pwentp))
    {
            perror("getpwuid_r");
    }
    else
    {
            printf("Username: %s\n", pwent.pw_name);
            printf("Real Name: %s\n", pwent.pw_gecos);
            printf("Passwd: %s\n", pwent.pw_passwd);
    }



    int  arr1[8] = {1,1,0,0,0,1,0,1};
    unsigned int num = 0xDEADC0DE;
    char bitstr[33];
    
    printf("%u\n", makebyte(arr1));

    sprintbits(bitstr, num);
    printf("%u is %s.\n", num, bitstr);
    printf("%i\n", isleafdirectory("/Users/SeanQuinn/Desktop/cpe357/Midterm2"));
}

