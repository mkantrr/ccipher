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
        char *defaugustus = "12";
        char defaes[] = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c};
        printf("Default Keys:\n");
        printf("Caesar: %s\n", defcaesar);
        printf("Augustus: %s\n", defaugustus);
        printf("AES: 0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6,\n"); 
        printf("     0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c}\n");
        char key[100];
        char stringx[100];
        char cip[3];
        while(1){
            printf("Enter command - qu(it), ca(esar), au(gustus), ae(s): ");
            fgets(cip, 3, stdin);
            getchar();
            printf("\n");
            if(strcmp(cip, "q") == 0){
                break;
            }
            if(strcmp(cip, "ca") == 0){
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
                    str->print(str, PLAIN);
                    printf("\n");
                    printf("Cipher text string:\n");
                    str->print(str, CIPHER);
                    printf("\n");
                    printf("Decrypted input: \n");
                    char *s = decrypt_string(CAESAR, str, defcaesar);
                    printf("len: %d\n", str->len);
                    print_C_string(s);
                    printf(" | %s\n", str->plain);
                    printf("\n");
                    str->print(str, PLAIN);
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
                printf("Enter string: ");
                fgets(stringx, 100, stdin);
                printf("\n");
                printf("Enter key (Enter d for default): ");
                fgets(key, 100, stdin);
                printf("%s\n", key);
                if(key[0] == 'd'){
                    printf("\n");
                    printf("Plain text string: \n");
                    string *str = encrypt_string(AUGUSTUS, stringx, defaugustus);
                    printf("len: %d\n", str->len);
                    printf("%s\n", str->plain);
                    printf("\n");
                    printf("Cipher text string:\n");
                    printf("len: %d\n", str->len);
                    printf("%s\n", str->cipher);
                    printf("\n");
                    
                }else{
                    printf("\n");
                    printf("Plain text string: \n");
                    string *str = encrypt_string(AUGUSTUS, stringx, key);
                    printf("len: %d\n", str->len);
                    printf("%s\n", str->plain);
                    printf("\n");
                    printf("Cipher text string:\n");
                    printf("len: %d\n", str->len);
                    printf("%s\n", str->cipher);
                    printf("\n");

                }
            }
            if(strcmp(cip, "ae") == 0){
              printf("Enter key (Enter d for default): ");
              fgets(key, 100, stdin);
              if (key[0] == 'd') {
                printf("Using default key.");
                printf("\n");
                printf("Plain text string:\n");
                string *str = encrypt_string(AES, stringx, defaes);
                printf("len: %d", str -> len);
                str -> print(str, PLAIN);
                printf("\n");
                printf("Cipher text sring:\n");
                printf("len: %d", str -> len);
                str -> print(str, CIPHER);
              } else {
                uint8_t *use_key = NULL;
                string *str = NULL;
                if (strlen((char*)use_key) % 16 != 0) {
                  printf("AES Key not 16 bytes. Using default key.");
                  str = encrypt_string(AES, stringx, defaes);
                } else {

                  unsigned int i, j, ii, jj;
                  for (j = 0, i = 0; i < strlen(key); i += 2, ++j) {
                    if (key[i] == ' ') {
                      i--;
                      continue;
                    }
                    ii = key[i] > '9' ? key[i] - 'A' + 10 : key[i] - '0';
                    jj = key[i+1] > '9' ? key[i+1] - 'A' + 10 : key[i] - '0';

                    use_key[j] = (ii << 4) | jj;
                  }
                  str = encrypt_string(AES, stringx, (char*)use_key);
                }
                printf("Plain text string:\n");
                printf("len: %d", str -> len);
                str -> print(str, PLAIN);
                printf("\n");
                printf("Cipher text sring:\n");
                printf("len: %d", str -> len);
                str -> print(str, CIPHER);
              }
            }
        }
    }else {
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
