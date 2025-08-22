#include "utils.h"

int getInt(const char* prompt){
    int value;
    printf("%s", prompt);
    while (scanf("%d", &value) != 1)
    {
        printf("Invalid Input. Try again: ");
        clearBuffer();
    }
    clearBuffer();
    return value;
}

void getString(const char* prompt, char* buffer, int size) {
    printf("%s", prompt);
    if(fgets(buffer, size, stdin) != NULL) {
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }
    } else {
        buffer[0] = '\0';
    }
}

void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void generateCode(const char* prefix, char* buffer, int count){
    int random = rand() % 10000;
    sprintf(buffer, "%s%03d-%04d", prefix, count, random);
}

bool checkValidPointers(int count, ...) {
    va_list args;
    va_start(args, count);

    for (int i = 0; i < count; i++) {
        void *ptr = va_arg(args, void*);
        if (ptr == NULL) {
            va_end(args);
            return false;
        }
    }

    va_end(args);
    return true;
}

bool checkCode(char* code, char type){
    if(type == 'b'){
        if(strncmp(code, BOOK_PREFIX, strlen(BOOK_PREFIX)) != 0) {
            return false;
        }
        return true;
    } else if (type == 'u') {
        if(strncmp(code, USER_PREFIX, strlen(USER_PREFIX)) != 0) {
            return false;
        }
        return true;
    }
    return false;
}