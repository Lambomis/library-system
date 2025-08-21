#ifndef USERS_H
#define USERS_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "books.h"

#define MAX_BORROWED 10
#define USER_PREFIX "USR"

typedef struct {
    char code[20];
    char name[50];
    char borrowedBooks[MAX_BORROWED][20];
    int borrowedBooksCount;
} User;

void initializeUsersList(User **usersList, int *usersCount);
bool checkUserCode(char* userCode);

void addUser(User **usersList, int *usersCount);
void removeUser(User **usersList, int *usersCount, char* userCode);
User* searchUser(User **usersList, char* userCode);
void editUser(User *user);

void borrowBook(User *user, int usersCount, Book *books, int bookUserCount);
void returnBook(User *user, int usersCount, Book *books, int bookUserCount);

void saveUsers(User *usersList, int usersCount, char *filename);
int loadUsers(User **usersList, char *filename);

#endif