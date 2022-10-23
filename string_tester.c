#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "default_tests.h"
#include "caesar.h"
#include "strings.h"
#include "aes_cbc.h"
int main(int argc, char **argv){
    if(argc == 1){
        char *defcaesar = "1";
        int defaugustus = 12;
        u_int8_t defaes[] = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c};
        printf("Default Keys:\n");
        printf("Caesar: %s\n", defcaesar);
        printf("Augustus: %d\n", defaugustus);
        printf("AES: 0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6,\n"); 
        printf("     0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c}\n");
        int loopvar = 0;
        char key[100];
        char stringx[100];
        char cip[2];
        while(loopvar == 0){
            printf("Enter command - q(uit), c(aesar), au(gustus), ae(s): ");
            fgets(cip, 2, stdin);
            getchar();
            printf("\n");
            if(strcmp(cip, "q") == 0){
                break;
            }
            if(strcmp(cip, "c") == 0){
                printf("Enter string: ");
                fgets(stringx, 100, stdin);
                printf("\n");
                printf("Enter key (Enter d for default): ");
                fgets(key, 100, stdin);
                if(key[0] == 'd'){
                    printf("Using default key.");
                    printf("\n");
                    printf("Plain text string:\n");
                    string *str = encrypt_string(CAESAR, stringx, defcaesar);
                    printf("len: %d\n", str->len);
                    printf("%s\n", str->plain);
                    printf("\n");
                    printf("Cipher text string:\n");
                    printf("len: %d\n", str->len);
                    printf("%s\n", str->cipher);
                    printf("\n");
                }else{
                    printf("\n");
                    printf("Plain text string:\n");
                    string *str = encrypt_string(CAESAR, stringx, key);
                    printf("len: %d\n", str->len);
                    printf("%s\n", str->plain);
                    printf("\n");
                    printf("Cipher text string:\n");
                    printf("len: %d\n", str->len);
                    printf("%s\n", str->cipher);
                    printf("\n");
                }
            }
            if(strcmp(cip, "au") == 0){ //Add Augustus cipher user interface here
                printf("Enter key (Enter d for default): ");
                fgets(key, 100, stdin);
                printf("%s\n", key);
                if(key == "D"){
                    
                }else{
                    
                }
            }
            if(strcmp(cip, "ae") == 0){
              printf("Enter key (Enter d for default): ");
              printf("AES Key must be 16 bytes.");
              fgets(key, 100, stdin);
              if (key[0] == 'd') {
                printf("Using default key.");
                printf("\n");
                printf("Plain text string:\n");
                string *str = encrypt_string(AES, stringx, defaes);
                printf("len: %d", str -> len);
                for (int i = 0; i < str -> len; i++) {
                // Add printer function
                }
              }
              else {
                struct AES_ctx ctx;

                strcpy(key, 

                int key_len = (strlen(key)/3) + 1;
                char *key_arr[key_len + 1];

                string *str = encrypt_string(AES, stringx, key);
                if (str -> len % 16 != 0) {
                  printf("AES Key not 16 bytes. Using default key.");
                } else {
                  // add printer function
                }
        }
        }else{
            if(strcmp(argv[1], "default") == 0){
                default_tests();
            }
            if (strstr(argv[1], ".txt") != NULL){
                printf("BBB\n");
                // add txt reader code HERE
            }
        }
    return 0;
}
