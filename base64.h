#include <openssl/bio.h>
#include <openssl/evp.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#ifndef __BASE64_H
#define __BASE64_H

int Base64Encode(const char* message, char** buffer);
int Base64Decode(char* b64message, char** buffer);

#endif
