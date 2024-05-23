#include <stdio.h>
#include <stdarg.h>
#include <utils.h>
#include <userSyscalls.h>
#include <buffer.h>


void putCh(char c){
    call_sys_write(&c, 1, STDOUT);
}

char getCh(){
    char c;
    call_sys_read(&c, 1, STDIN);
    return c;
}

int null_or_space(char c){
    return (c == '\0' || c == ' ');
}

int null_or_newline(char c){
    return (c == '\0' || c == '\n');
}

int strcmp(char * str1, char * str2){
	int i = 0;
	for (; str1[i] != '\0' && str2[i] != '\0'; i++){
		if (str1[i] > str2[i]){
			return 1;
		} else if (str1[i] < str2[i]){
			return -1;
		}
	}
	if (str1[i] == '\0' && str2[i] == '\0') {
        return 0;
    } else if (str1[i] == '\0') {
        return -1; 
    } else return 1;

}


int strcmpspace(char * str1, char * str2){
    char partition[BUFFERLIMIT];
    int j = 0;
    for (; str2[j] != '\0' && str2[j] != ' '; j++){
        partition[j]=str2[j];
    }
    partition[j+1]=0;
	int i = 0;
	for (; str1[i] != '\0' && !null_or_space(partition[i]); i++){
		if (str1[i] > str2[i]){
			return 1;
		} else if (str1[i] < str2[i]){
			return -1;
		}
	}
	if (str1[i] == '\0' && null_or_space(partition[i])) {
        return 0;
    } else if (null_or_space(partition[i])) {
        return -1; 
    } else return 1;

}