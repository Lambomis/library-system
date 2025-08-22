#include "users.h"

void initializeUserList(User **userList, int *usersCount){
    if(!checkValidPointers(2, userList, usersCount)) {
        fprintf(stderr, "Error: Null pointer passed to initializeUserList.\n");
        return;
    }
    *userList = NULL;
    *usersCount = 0;
}

void addUser(User **userList, int *usersCount){
    if(!checkValidPointers(2, userList, usersCount)) {
        fprintf(stderr, "Error: Null pointer passed to addUser.\n");
        return;
    }
    User newUser;
    generateCode(&USER_PREFIX, newUser.code, *usersCount);
    getString("Enter user name: ", newUser.name, sizeof(newUser.name));
    newUser.borrowedBooksCount = 0;
    *userList = realloc(*userList, (*usersCount + 1) * sizeof(User));
    if(*userList == NULL) {
        fprintf(stderr, "Error: Memory allocation failed in addUser.\n");
        return;
    }
    (*userList)[*usersCount] = newUser;
    (*usersCount)++;
    printf("User added successfully. Total users: %d\n", *usersCount);
}

void removeUser(User **userList, int *usersCount, char* userCode){
    if (!checkValidPointers(2, userList, usersCount)) {
        fprintf(stderr, "Error: Null pointer passed to removeUser.\n");
        return;
    }

    if(!checkCode(userCode, 'u')) {
        printf("Invalid user ID.\n"); 
        return;
    }

    for(int i = 0; i < *usersCount; i++) {
        if(strcmp((*userList)[i].code, userCode) == 0){
            for(int j = i; j < *usersCount - 1; j++) {
                (*userList)[j] = (*userList)[j + 1];
            }
            *userList = realloc(*userList, (*usersCount - 1) * sizeof(User));
            if(*userList == NULL && *usersCount > 1) {
                fprintf(stderr, "Error: Memory allocation failed in removeUser.\n");
                return;
            }
            (*usersCount)--;
            printf("User with ID %s removed successfully. Total users: %d\n", userCode, *usersCount);
            return;
        }
    }
}

User* searchUser(User **userList, char* userCode, const int* usersCount){
    if(!checkValidPointers(3, userList, userCode, usersCount)) {
        fprintf(stderr, "Error: Null pointer passed to searchUser.\n");
        return NULL;
    }

    for(int i = 0; i < *usersCount; i++){
        if(strcmp((*userList)[i].code, userCode) == 0){
            printf("User %s found!", userCode);
            return &(*userList)[i];
        }
    }
    printf("User not %s found!", userCode);
    return NULL;
}

void editUser(User *user){
    if(!checkValidPointers(1, user)) {
        fprintf(stderr, "Error: Null pointer passed to editUser.\n");
        return;
    }
    getString("Please enter the new name of the User: ", user->name, sizeof(user->name));
}

void borrowBook(User* user, Book* book){
    if(!checkValidPointers(3, user, book)) {
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
    
    printf("Book with ID %s borrowed by user with ID %s.\n", book->code, user->code);

}

void returnBook(User *user, Book *book){
    if(!checkValidPointers(2, user, book)) {
        fprintf(stderr, "Error: Null pointer passed to borrowBook.\n");
        return;
    }

    if(user->borrowedBooksCount <= 0){
        fprintf(stderr, "Error, no book borrowed by this user!");
        return;
    }

    for(int i = 0; i < user->borrowedBooksCount; i++){
        if(strcmp(user->borrowedBooks[i], book->code) == 0){
            for(int j = i; j < user->borrowedBooksCount; j++){
                strcpy(user->borrowedBooks[j], user->borrowedBooks[j + 1]);
            }
            user->borrowedBooksCount--;
            book->available++;
            printf("Book with ID %s correctly returned!", book->code);
            return;
        }
    }
}

void saveUsersCSV(const char *filename, User *userList, int usersCount) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Error opening file");
        return;
    }

    fprintf(file, "code,name,borrowedBooksCount,borrowedBooks\n");

    for (int i = 0; i < usersCount; i++) {
        fprintf(file, "%s,%s,%d,\"", 
            userList[i].code, 
            userList[i].name, 
            userList[i].borrowedBooksCount);

        for (int j = 0; j < userList[i].borrowedBooksCount; j++) {
            fprintf(file, "%s", userList[i].borrowedBooks[j]);
            if (j < userList[i].borrowedBooksCount - 1) fprintf(file, ",");
        }
        fprintf(file, "\"\n");
    }

    fclose(file);
}

void loadUsersCSV(const char *filename, User **userList, int *usersCount) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return;
    }

    char line[512];
    fgets(line, sizeof(line), file);

    *userList = NULL;
    *usersCount = 0;

    while (fgets(line, sizeof(line), file)) {
        *userList = realloc(*userList, (*usersCount + 1) * sizeof(User));
        User *u = &(*userList)[*usersCount];

        char *token = strtok(line, ",");
        strcpy(u->code, token);

        token = strtok(NULL, ",");
        strcpy(u->name, token);

        token = strtok(NULL, ",");
        u->borrowedBooksCount = atoi(token);

        token = strtok(NULL, "\"");
        token = strtok(NULL, "\"");
        if (token != NULL && strlen(token) > 0) {
            char *book = strtok(token, ",");
            int idx = 0;
            while (book != NULL && idx < MAX_BORROWED) {
                strcpy(u->borrowedBooks[idx++], book);
                book = strtok(NULL, ",");
            }
        }
        (*usersCount)++;
    }

    fclose(file);
}

