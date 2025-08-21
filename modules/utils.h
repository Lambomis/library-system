#ifndef UTILS_H
#define UTILS_H

int getInt(char *prompt);
void getString(char *prompt, char *buffer, int size);
void clearBuffer();
void generateCode(char* prefix, char* buffer, int count);
bool checkValidPointers(int count, ...);

#endif