#ifndef USERS_H
#define USERS_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "models.h"
#include "utils.h"

void initializeUserList(User **userList, int *usersCount);

void addUser(User **userList, int *usersCount);
void removeUser(User **userList, int *usersCount, char* userCode);
User* searchUser(User **userList, char* userCode, const int* usersCount);
void editUser(User *user);

void borrowBook(User* user, Book* book);
void returnBook(User *user, Book *book);

void saveUsersCSV(const char *filename, User *userList, int usersCount);
void loadUsersCSV(const char *filename, User **userList, int *usersCount);

#endif