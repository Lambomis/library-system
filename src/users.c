#include "users.h"

void initializeUserList(User **userList, int *userCount){
    if(userList == NULL || userCount == NULL) {
        fprintf(stderr, "Error: Null pointer passed to initializeUserList.\n");
        return;
    }
    *userList = NULL;
    *userCount = 0;
}

bool checkUserCode(char* userCode){
    if(strncmp(userCode, USER_PREFIX, strlen(USER_PREFIX)) != 0) {
        return false;
    }
    return true;
}

void addUser(User **userList, int *userCount){
    if(userList == NULL || userCount == NULL) {
        fprintf(stderr, "Error: Null pointer passed to addUser.\n");
        return;
    }
    User newUser;
    generateCode(&USER_PREFIX, newUser.code, userCount);
    getString("Enter user name: ", newUser.name, sizeof(newUser.name));
    newUser.borrowedBooksCount = 0; // No book borrowed initially
    *userList = realloc(*userList, (*userCount + 1) * sizeof(User));
    if(*userList == NULL) {
        fprintf(stderr, "Error: Memory allocation failed in addUser.\n");
        return;
    }
    (*userList)[*userCount] = newUser; // Add the new user to the list
    (*userCount)++;
    printf("User added successfully. Total users: %d\n", *userCount);
}

void removeUser(User **userList, int *userCount, char* userCode){
    if (!checkValidPointers(3, userList, userCount)) {
        fprintf(stderr, "Error: Null pointer passed to removeUser.\n");
        return;
    }

    if(!checkUserCode(userCode)) {
        printf("Invalid user ID.\n"); 
        return;
    }

    for(int i = 0; i < *userCount; i++) {
        if(strcmp((*userList)[i].code, userCode) == 0){
            for(int j = i; j < *userCount - 1; j++) {
                (*userList)[j] = (*userList)[j + 1];
            }
            *userList = realloc(*userList, (*userCount - 1) * sizeof(User));
            if(*userList == NULL && *userList > 1) {
                fprintf(stderr, "Error: Memory allocation failed in removeUser.\n");
                return;
            }
            (*userCount)--;
            printf("User with ID %s removed successfully. Total users: %d\n", userCode, *userCount);
            return;
        }
    }
}

User* searchUser(User **userList, char* userCode, const int* userCount){
    if(!checkValidPointers(3, userList, userCode, userCount)) {
        fprintf(stderr, "Error: Null pointer passed to searchUser.\n");
        return NULL;
    }

    for(int i = 0; i < *userCount; i++){
        if(strcmp((*userList)[i].code, userCode) == 0){
            printf("User %s found!", userCode);
            return &(*userList)[i];
        }
    }
    print("User not %s found!", userCode);
    return NULL;
}

void editUser(User *user){
    if(!checkValidPointers(1, user)) {
        fprintf(stderr, "Error: Null pointer passed to editUser.\n");
        return;
    }
    getString("Please enter the new name of the User: ", user->name, sizeof(user->name));
}

void borrowBook(User* user, int* userCount, Book* book, int* bookCount){
    if(!checkValidPointers(3, user, userCount, book)) {
        fprintf(stderr, "Error: Null pointer passed to borrowBook.\n");
        return;
    }

    if(user->borrowedBooksCount == MAX_BORROWED) {
        printf("User with ID %s already has %d books borrowed.\n", user->code, MAX_BORROWED);
        return;
    }

    if(book->available <= 0) {
        printf("Book with ID %s (Name: %s) is not available for borrowing.\n", book->code, book->title);
        return;
    }
    book->available--;
    strcpy(user->borrowedBooks[user->borrowedBooksCount], book->code);
    user->borrowedBooksCount++;
    (*bookCount)++;
    
    printf("Book with ID %s borrowed by user with ID %s.\n", book->code, user->code);

}

