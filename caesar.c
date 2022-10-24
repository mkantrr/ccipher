#include <stdio.h>
#include <string.h>
#include <stdlib.h>
char *caesar_encrypt(char *plain, char *key){
    int len = strlen(plain);
    int keyint = atoi(key);
    char newplain[len+1];
    newplain[len+1] = '\0';
    
    for(int i=0;i<len;i++){
        char el = plain[i];
        if(el>96 && el<123){
            int  newkey = keyint/26;
            newkey = keyint - (26*newkey);
            int newelint = el+newkey;
            if(newelint > 122){
                newelint = newelint - 122;
                newelint = newelint + 96;
            }
            char newel = newelint;
            newplain[i] = newel;
        }
        if(el>32 && el<59){
            int newkey = keyint/26;
            newkey = keyint-(26*newkey);
            int newelint = el+newkey;
            if(newelint > 58){
                newelint = newelint - 58;
                newelint = newelint + 32;
            }
            char newel = newelint;
            newplain[i] = newel;
        }
        if(el>64 && el<91){
            int  newkey = keyint/26;
            newkey = keyint - (26*newkey);
            int newelint = el+newkey;
            if(newelint > 90){
                newelint = newelint - 90;
                newelint = newelint + 64;
            }
            char newel = newelint;
            newplain[i] = newel;
        }
        if(plain[i] == ' '){
            newplain[i] = ' ';
        }   
    }
    char *newplain2 = malloc(sizeof(plain));
    for(int i=0;i<strlen(plain);i++){
        newplain2[i] = newplain[i];
    }
    
    return newplain2;
}
char *caesar_decrypt(char *cipher, char *key){
    int len = strlen(cipher);
    int keyint = atoi(key);
    char newcipher[len+1];
    newcipher[len+1]='\0';
    int newkey = keyint/26;
    newkey = keyint - (26*newkey);
    for(int i=0;i<len;i++){
        char el = cipher[i];
        if(el>96 && el<123){
            int  newkey = keyint/26;
            newkey = keyint - (26*newkey);
            int newelint = el-newkey;
            if(newelint < 97){
                newelint = newelint - 96;
                newelint = newelint + 122;
            }
            char newel = newelint;
            newcipher[i] = newel; 
        }
        if(el>32 && el<59){
            int  newkey = keyint/26;
            newkey = keyint - (26*newkey);
            int newelint = el-newkey;
            if(newelint < 33){
                newelint = newelint - 32;
                newelint = newelint + 58;
            }
            char newel = newelint;
            newcipher[i] = newel;
        }
        if(el>64 && el<91){
            int  newkey = keyint/26;
            newkey = keyint - (26*newkey);
            int newelint = el-newkey;
            if(newelint < 65){
                newelint = newelint - 64;
                newelint = newelint + 90;
            }
            char newel = newelint;
            newcipher[i] = newel;
        }
        if(cipher[i] == ' '){
            newcipher[i] = ' ';
        } 
    }
    char *newcipher2 = malloc(sizeof(cipher));
    
    for(int i=0;i<strlen(cipher);i++){
        newcipher2[i] = newcipher[i];
    }
    return newcipher2;
}
