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


int strcmpspace(char *str1, char *str2) {
    // Compare characters up to the first space in both strings
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0' && !null_or_space(str2[i])) {
        if (str1[i] != str2[i]) {
            return str1[i] > str2[i] ? 1 : -1;
        }
        i++;
    }
    // If str2 contains space, compare up to that space
    if (str1[i] == '\0' && null_or_space(str2[i])) {
        return 0;
    } else if (null_or_space(str2[i])) {
        return -1;
    } else {
        return 1;
    }
}

void print( char * fmt, ...){
    va_list args;
    va_start(args, fmt);

    while(*fmt != '\0'){
        if(*fmt == '%'){
            fmt++;
            switch(*fmt){
                case 'd':{
                    int i = va_arg(args, int);
                    char buff[BUFFERLIMIT];
                    int_to_string(i, buff);
                    call_sys_write(buff, strlen(buff), STDOUT);
                    break;
                }
                case 's':{
                    char * s = va_arg(args, char *);
                    call_sys_write(s, strlen(s), STDOUT);
                    break;
                }
                case 'c':{
                    char c = va_arg(args, int);
                    call_sys_write(&c, 1, STDOUT);
                    break;
                }
            }
        } else {
            call_sys_write(fmt, 1, STDOUT);
        }
        fmt++;
    }
    
    va_end(args);
    return;
}

void int_to_string(int num, char * buff){
    int i = 0;
    if(num == 0){
        buff[i++] = '0';
    } else {
        if(num < 0){
            buff[i++] = '-';
            num = -num;
        }
        int aux = num;
        while(aux > 0){
            aux /= 10;
            i++;
        }
        aux = num;
        buff[i] = '\0';
        while(aux > 0){
            buff[--i] = (aux % 10) + '0';
            aux /= 10;
        }
    }
}

int strlen(char * str){
    int i = 0;
    while(str[i] != '\0'){
        i++;
    }
    return i;
}