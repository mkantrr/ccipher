#include <stdio.h>
#include <string.h>
#include <stdlib.h>
char *caesar_encrypt(char *plain, char *key){
    int len = strlen(plain);
    int keyint = atoi(key);
    char newplain[len];
    int  newkey = keyint/26;
    newkey = keyint - (26*newkey);
    
    for(int i=0;i<len;i++){
        char el = plain[i];
        printf("%d\n", newkey);
        printf("%d\n", el);
        char newel = el+newkey;
        printf("%d\n", newel);
        if(newel > 122){
            // printf("XX");
            // printf("%d\n", newel);
            newel = newel - 122;
            // printf("%d\n", newel);
            newel = newel + 96;
            // printf("%d\n", newel);
        }
        // printf("%d\n", newel);
        newplain[i] = newel;
        printf("\n");
    } 
    plain = newplain;
    return plain;
}
char *caesar_decrypt(char *cipher, char *key){
    int len = strlen(cipher);
    int keyint = atoi(key);
    char newcipher[len];
    int newkey = keyint/26;
    newkey = keyint - (26*newkey);
    for(int i=0;i<len;i++){
        char el = cipher[i];
        char newel = el-newkey;
        newcipher[i] = newel;
    }
    cipher = newcipher;
    return cipher;
}