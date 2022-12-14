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
        printf("len: %d\n", self->len);
        toHex(self->plain);
        printf(" | %s\n", self->plain);
    }
    else {
        printf("len: %d\n", self->len);
        toHex(self->cipher);
        printf(" | %s\n", self->cipher);
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
        printf("%c " , self -> plain[i]);
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
    int plainsize = strlen(plain);
    if(roundup > 0){
        while(plainsize % 16 != 0){
            plainsize++;
        }
        for(int i=0;i<roundup-1;i++){
            plainsize = plainsize + 16;
        }
    }
    string *str = malloc(sizeof(string));
    str->plain = malloc(plainsize);
    char newstr[plainsize];
    for(int a=0;a<plainsize;a++){
        newstr[a] = '\0';
    }
    for(int a=0;a<strlen(plain);a++){
        newstr[a] = plain[a];
    }
    strcpy(str->plain, newstr);
    str->len = strlen(plain);
    str->print = print1;
    str -> encrypt = encrypt_string;
    str -> decrypt = decrypt_string;
    return str;
}
string *new_cipher(char *ciph, int len, int roundup){
    int ciphsize = strlen(ciph);
    if(roundup > 0){
        while(ciphsize % 16 != 0){
            ciphsize++;
        }
        for(int i=0;i<roundup-1;i++){
            ciphsize = ciphsize + 16;
        }
    }
    string *str = malloc(sizeof(string));
    str -> cipher = malloc(ciphsize);
    char newstr[ciphsize];
    for(int a=0;a<ciphsize;a++){
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
    char *newstr = str -> plain;
    if(c == CAESAR){
       newstr = caesar_encrypt(s, key);
       str -> print = print1;
    }
    else if(c == AES) {
      if (str -> cipher) {
        strcpy(newstr, str -> cipher);
      } else {
      struct AES_ctx ctx;
      AES_init_ctx_iv(&ctx, (uint8_t*)key, iv);
      uint32_t buf_length;
      if (strlen(s) == 16) {
        buf_length = strlen(s);
        char buffer[16];
        memcpy(buffer, s, buf_length);
        AES_CBC_encrypt_buffer(&ctx, (uint8_t*)buffer, buf_length);
        newstr = buffer;
      } else if (strlen(newstr) > 16) {
        uint32_t twice_length = strlen(s) * ((strlen(s) / 16) + 1);
        buf_length = twice_length - (twice_length % 16);
        char buffer[buf_length];
        memcpy(buffer, s, buf_length);
        AES_CBC_encrypt_buffer(&ctx, (uint8_t*)buffer, buf_length);
        newstr = buffer;
      } else {
        buf_length = 16;
        char buffer[16];
        memcpy(buffer, s, buf_length);
        AES_CBC_encrypt_buffer(&ctx, (uint8_t*)buffer, buf_length);
        newstr = buffer;
      }
      str -> len = buf_length;
      }
      str -> print = print2;
    } else if (c == AUGUSTUS) {
      newstr = augustus_encrypt(s, key);
      str -> print = print1;
    }
    // if statements regarding which cipher is being used
    str->cipher = newstr;
    str->len = slen;
    return str;

}
char *decrypt_string(cipher c, string *str, char *key){
  // printf("%ld\n", sizeof(char)*strlen(str->cipher));
  char *newstr = str->cipher;
  if(c == CAESAR){
    newstr = caesar_decrypt(newstr, key);
    str -> print = print1;
  } else if(c == AES) {
    if (str -> plain) {
      strcpy(newstr, str -> plain);
    } else {
      struct AES_ctx ctx;

      AES_init_ctx_iv(&ctx, (uint8_t*)key, iv);
      uint32_t buf_length;
      if (strlen(newstr) == 16) {
        buf_length = strlen(newstr);
        char buffer[16];
        memcpy(buffer, newstr, buf_length);
        AES_CBC_decrypt_buffer(&ctx, (uint8_t*)buffer, buf_length);
        newstr = buffer;
      } else if (strlen(newstr) > 16) {
        uint32_t twice_length = strlen(newstr) * ((strlen(newstr) / 16) + 1);
        buf_length = twice_length - (twice_length % 16);
        char buffer[buf_length];
        memcpy(buffer, newstr, buf_length);
        AES_CBC_decrypt_buffer(&ctx, (uint8_t*)buffer, buf_length);
        newstr = buffer;
      } else {
        buf_length = 16;
        char buffer[16];
        memcpy(buffer, newstr, buf_length);
        AES_CBC_decrypt_buffer(&ctx, (uint8_t*)buffer, buf_length);
        newstr = buffer;
      }
      str -> len = buf_length;
      }
      str -> print = print2;   
    } else if (c == AUGUSTUS) {
        newstr = augustus_decrypt(newstr, key);
        str -> print = print1;
      }

    //if statements again regarding which cipher
    str->plain = newstr;
    return newstr;
}

void toHex(char *s) {
  int ssize = sizeof(s);
  for (int i = 0; i < ssize; i++) {
    printf("%x ", s[i]);
  }
}

void print_C_string(char *s){
    int ssize = sizeof(s);
    for(int i=0;i<ssize;i++){
      printf("%c",s[i]);
    }
}
