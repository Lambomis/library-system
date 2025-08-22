#ifndef MODELS_H
#define MODELS_H

#define MAX_BORROWED 10
#define USER_PREFIX "USR"
#define BOOK_PREFIX "BK"

typedef struct {
    char code[20];
    char title[100];
    char author[50];
    int available;
} Book;

typedef struct {
    char code[20];
    char name[50];
    char borrowedBooks[MAX_BORROWED][20];
    int borrowedBooksCount;
} User;

#endif
