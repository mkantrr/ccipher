#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "strings.h"
#include "caesar.h"
#include "augustus.h"
#include "aes_cbc.h"
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
    char *newstr;
    if(c == CAESAR){
       newstr = caesar_encrypt(s, key);
    }
    else if(c == AES) {
      struct AES_ctx ctx;

      int key_len = (slen/3) + 1;
      uint8_t key_arr[key_len + 1];

      char hexNum[3];
      hexNum[2] = 0;

      for (int i = 0; i < key_len; i++) {
        key = strchr(key, ' ');
        if (key) {
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
      if (key_len < 16 || key_len == 16) {
        buf_length = 16;
      } else {
        buf_length = (16 * (key_len / 16)) + (key_len % 16);
      }
      AES_CBC_encrypt_buffer(&ctx, key_arr, buf_length);
      newstr = &key_arr;
      } else if (c == AUGUSTUS) {
        newstr = augustus_encrypt(s, key);
      } else {}
    // if statements regarding which cipher is being used
    str->cipher = newstr;
    str->len = slen;
    str->print = print1;
    return str;

}
char *decrypt_string(cipher c, string *str, char *key){
    char *newstr = malloc(sizeof(str->cipher));
    newstr = str->cipher;
    int slen = strlen(newstr);
    if(c == CAESAR){
        newstr = caesar_decrypt(newstr, key);
    } else if(c == AES) {
      struct AES_ctx ctx;

      int key_len = (slen/3) + 1;
      uint8_t key_arr[key_len + 1];

      char hexNum[3];
      hexNum[2] = 0;

      for (int i = 0; i < key_len; i++) {
        key = strchr(key, ' ');
        if (key) {
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
      if (key_len < 16 || key_len == 16) {
        buf_length = 16;
      } else {
        buf_length = (16 * (key_len / 16)) + (key_len % 16);
      }
      AES_CBC_decrypt_buffer(&ctx, key_arr, buf_length);
      newstr = &key_arr;
      } else if (c == AUGUSTUS) {
        newstr = augustus_decrypt(newstr, key);
      } else {}

    //if statements again regarding which cipher
    str->plain = newstr;
    return newstr;
}
