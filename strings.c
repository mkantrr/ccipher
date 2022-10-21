#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "strings.h"
#include "caesar.h"
void print1(string *self, string_type st){
    if(st == PLAIN){
        printf("%s\n", self->plain);
    }
    if(st == CIPHER){
        printf("%s\n", self->cipher);
    }
}
string *new_plain(char *plain, int roundup){
    int size = 8;
    int plainsize = strlen(plain);
    if(roundup > 0){
        while(size%16 != 0){
            size++;
        }
        for(int i=0;i<roundup-1;i++){
            size = size + 16;
        }
    }
    string *str = malloc(sizeof(string));
    str->plain = malloc(size);
    char newstr[size];
    for(int a=0;a<size;a++){
        newstr[a] = '\0';
    }
    for(int a=0;a<strlen(plain);a++){
        newstr[a] = plain[a];
    }
    strcpy(str->plain, newstr);
    str->len = plainsize;
    str->print = print1;
    return str;
}
string *new_cipher(char *ciph, int len, int roundup){
    int size = 8;
    int ciphsize = strlen(ciph);
    if(roundup > 0){
        while(size%16 != 0){
            size++;
        }
        for(int i=0;i<roundup-1;i++){
            size = size + 16;
        }
    }
    string *str = malloc(sizeof(string));
    str -> cipher = malloc(size);
    char newstr[size];
    for(int a=0;a<size;a++){
        newstr[a] = '\0';
    }
    for(int a=0;a<strlen(ciph);a++){
        newstr[a] = ciph[a];
    }
    strcpy(str->cipher, newstr);
    str -> len = ciphsize;
    str -> print = print1;
    return str;
}
string *encrypt_string(cipher c, char *s, char *key){
    string *str = malloc(sizeof(string));
    int slen = strlen(s);
    str -> plain = s;
    char *newstr;
    if(c == CAESAR){
        newstr = caesar_encrypt(s, key);
    }
    // if statements regarding which cipher is being used
    str->cipher = newstr;
    str->len = slen;
    str->print = print1;
    return str;

}
char *decrypt_string(cipher c, string *str, char *key){
    char *newchar = malloc(sizeof(str->cipher));
    newchar = str->cipher;
    int slen = strlen(newchar);
    if(c == CAESAR){
        char *newchar2 = malloc(sizeof(str->cipher));
        newchar = caesar_decrypt(newchar, key);
    }
    //if statements again regarding which cipher
    str->plain = newchar;
    return newchar;
}
