#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#define CHUNK 80
extern char *readline(FILE *infile) {
/* Read a string from given stream. Returns the string, or NULL if
* EOF is encoutered. Approach: allocate a buffer of size CHUNK, 10
* and as the string grows expand the buffer as necessary
*/
int i;
char *buff;
char *ret;
int size=0;
char c;
size=CHUNK;
if(NULL==(buff=(char*)malloc(size * sizeof(char)))) { 
	perror(__FUNCTION__);
	exit(-1);
}
for(i=0,c=getc(infile); c!=EOF ;c=getc(infile)) {
	if(i>=size-1){ 
		size+=CHUNK;
		if(NULL==(buff=(char*)realloc(buff,size * sizeof(char)))) {
			perror(__FUNCTION__);
			exit(-1);
		} 
	}
	buff[i++]=c;
	if( c =='\n')
		break;
}
if ( i ) { /* if there was a string read, copy it
* into a new buffer. Otherwise, return
* NULL to signal EOF
*/ 
buff[i] = '\0'; /* final nul */
if(NULL==(ret=(char*)malloc(i+1))) {
	perror(__FUNCTION__);
	exit(-1);
}
strcpy(ret,buff);
} else {
ret = NULL;
}

free(buff);
return ret;
}