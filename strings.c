#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "strings.h"
#include "caesar.h"
#include "augustus.h"
#include "aes_cbc.h"

uint8_t iv[] = {0x10, 0x11, 0x12, 0x13, 0x14, 0x05, 0x06, 0x07,
                    0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};

void print1(string *self, string_type st){
    if(st == PLAIN){
        printf("%s\n", self->plain);
    }
    else {
        printf("%s\n", self->cipher);
    }
}

void print2(string *self, string_type st) {
  if (st == PLAIN) {
    for (int i = 0; i < 16; i++) {
      printf("%.2x " , self -> plain[i]);
    }
    printf(" | ");
    for (int i = 0; i < 16; i++) {
      if (isprint(self -> plain[i])) {
        printf("%c" , self -> plain[i]);
      } else {
        printf(" ");
      }
    }
    printf("\n");
  } else {
    for (int i = 0; i < 16; i++) {
      printf("%.2x " , self -> cipher[i]);
    }
    printf(" | ");
    for (int i = 0; i < 16; i++) {
      if (isprint(self -> cipher[i])) {
        printf("%c" , self -> cipher[i]);
      } else {
        printf(" ");
      }
    }
    printf("\n");
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
    str -> encrypt = encrypt_string;
    str -> decrypt = decrypt_string;
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
    str -> encrypt = encrypt_string;
    str -> decrypt = decrypt_string;
    return str;
}
string *encrypt_string(cipher c, char *s, char *key){
    string *str = malloc(sizeof(string));
    int slen = strlen(s);
    str -> plain = s;
    char *newstr = NULL;
    if(c == CAESAR){
       newstr = caesar_encrypt(s, key);
       str -> print = print1;
    }
    else if(c == AES) {
      struct AES_ctx ctx;

      int key_len = (slen/3) + 1;
      uint8_t key_arr[key_len + 1];
      char hexNum[3];
      hexNum[2] = 0;
      printf("%d\n", key_len);
      for (int i = 0; i < key_len; i++) {
        printf("%d\n", i);
        key = strchr(key, ' ');
        if (key) {
          printf("%d\n", i);
          hexNum[0] = *(key-2);
          hexNum[1] = *(key-1);
          key_arr[i] = (char)strtoul(hexNum, NULL, 16);

          key++;

          if (strlen(key) == 2) {
            i++;

            hexNum[0] = *(key);
            hexNum[1] = *(key+1);
            key_arr[i] = (char)strtoul(hexNum, NULL, 16);
          }
        }
      }
      

      uint8_t iv[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
                    0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};
        
      AES_init_ctx_iv(&ctx, key_arr, iv);
      uint32_t buf_length;
      if (strlen(s) < 16 || strlen(s) == 16) {
        buf_length = strlen(s);
      } else {
        buf_length = (strlen(s) * ((strlen(s) / 16) + 1)) - ((strlen(s) % 10) - 1);
      }
      if (buf_length % 16 == 0) {
      AES_CBC_encrypt_buffer(&ctx, (uint8_t*)s, buf_length);
      } else {
        newstr = NULL;
      }
      newstr = s;
      str -> print = print2;
      str -> len = buf_length;
      } else if (c == AUGUSTUS) {
<<<<<<< HEAD
        newstr = augustus_encrypt(s, key);
        str -> print = print1;
      }
=======

      } else {}
>>>>>>> i;alksdjfa
    // if statements regarding which cipher is being used
    str->cipher = newstr;
    str->len = slen;
    return str;

}
char *decrypt_string(cipher c, string *str, char *key){
    // printf("%ld\n", sizeof(char)*strlen(str->cipher));
    char *newstr = str->cipher;
    newstr = str->cipher;
    if(c == CAESAR){
        newstr = caesar_decrypt(newstr, key);
        str -> print = print1;
    } else if(c == AES) {
      struct AES_ctx ctx;

      AES_init_ctx_iv(&ctx, (uint8_t*)key, iv);
      uint32_t buf_length;
      if (strlen(newstr) < 16 || strlen(newstr) == 16) {
        buf_length = strlen(newstr);
      } else {
        buf_length = (strlen(newstr) * ((strlen(newstr) / 16) + 1)) - ((strlen(newstr) % 10) - 1);
      }
      if (buf_length % 16 == 0) {
      AES_CBC_decrypt_buffer(&ctx, (uint8_t*)newstr, buf_length);
      } else {
        newstr = NULL;
      }
      str -> len = buf_length;
      str -> print = print2;
      } else if (c == AUGUSTUS) {
        newstr = augustus_decrypt(newstr, key);
        str -> print = print1;
      }

    //if statements again regarding which cipher
    str->plain = newstr;
    return newstr;
}
void print_C_string(char *s){
    printf("%d\n", s[0]);
}