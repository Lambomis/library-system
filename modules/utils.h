#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdbool.h>
#include "models.h"

int getInt(char *prompt);
void getString(char *prompt, char *buffer, int size);
void clearBuffer();
void generateCode(char* prefix, char* buffer, int count);
bool checkValidPointers(int count, ...);
bool checkCode(char* code, char type);

#endif