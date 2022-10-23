#ifndef _AUGUSTUS_H
#define _AUGUSTUS_H
char *augustus_encrypt(char *plain, char *key);
char *augustus_decrypt(char *cipher, char *key);
char caesarConvert(char input, int key);
char caesarRevert(char input, int key);
int wrapAround(int start, int key);
#endif // _AUGUSTUS_H