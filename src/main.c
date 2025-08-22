#include <stdio.h>
#include <stdlib.h>
#include "users.h"
#include "books.h"

int main() {
    User *userList;
    int userCount;
    Book *bookList;
    int bookCount;

    initializeUserList(&userList, &userCount);
    initializeBookList(&bookList, &bookCount);

    int choice;
    while (1) {
        printf("\n=== Library System ===\n");
        printf("1. Add User\n");
        printf("2. Remove User\n");
        printf("3. Edit User\n");
        printf("4. Add Book\n");
        printf("5. Remove Book\n");
        printf("6. Edit Book\n");
        printf("7. Borrow Book\n");
        printf("8. Return Book\n");
        printf("9. Show Users\n");
        printf("10. Show Books\n");
        printf("11. Save & Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);
        getchar();

        char code[20];

        switch (choice) {
            case 1:
                addUser(&userList, &userCount);
                break;

            case 2:
                printf("Enter User Code to remove: ");
                scanf("%s", code);
                getchar();
                removeUser(&userList, &userCount, code);
                break;

            case 3: {
                printf("Enter User Code to edit: ");
                scanf("%s", code);
                getchar();
                User *u = searchUser(&userList, code, &userCount);
                if (u) editUser(u);
                break;
            }

            case 4:
                addBook(&bookList, &bookCount);
                break;

            case 5:
                printf("Enter Book Code to remove: ");
                scanf("%s", code);
                getchar();
                removeBook(&bookList, &bookCount, code);
                break;

            case 6: {
                printf("Enter Book Code to edit: ");
                scanf("%s", code);
                getchar();
                Book *b = searchBook(&bookList, code, &bookCount);
                if (b) editBook(b);
                break;
            }

            case 7: {
                char userCode[20], bookCode[20];
                printf("Enter User Code: ");
                scanf("%s", userCode);
                getchar();
                printf("Enter Book Code: ");
                scanf("%s", bookCode);
                getchar();

                User *u = searchUser(&userList, userCode, &userCount);
                Book *b = searchBook(&bookList, bookCode, &bookCount);
                if (u && b) borrowBook(u, b);
                break;
            }

            case 8: {
                char userCode[20], bookCode[20];
                printf("Enter User Code: ");
                scanf("%s", userCode);
                getchar();
                printf("Enter Book Code: ");
                scanf("%s", bookCode);
                getchar();

                User *u = searchUser(&userList, userCode, &userCount);
                Book *b = searchBook(&bookList, bookCode, &bookCount);
                if (u && b) returnBook(u, b);
                break;
            }

            case 9:
                printf("\n--- Users ---\n");
                for (int i = 0; i < userCount; i++) {
                    printf("%s - %s | Books borrowed: %d\n",
                           userList[i].code, userList[i].name, userList[i].borrowedBooksCount);
                    for (int j = 0; j < userList[i].borrowedBooksCount; j++)
                        printf("  %s\n", userList[i].borrowedBooks[j]);
                }
                break;

            case 10:
                printf("\n--- Books ---\n");
                for (int i = 0; i < bookCount; i++) {
                    printf("%s - %s by %s | Available: %d\n",
                           bookList[i].code, bookList[i].title, bookList[i].author, bookList[i].available);
                }
                break;

            case 11:
                saveUsersCSV("users.csv", userList, userCount);
                saveBooksCSV("books.csv", bookList, bookCount);
                printf("Data saved. Exiting...\n");
                free(userList);
                free(bookList);
                return 0;

            default:
                printf("Invalid choice!\n");
        }
    }
}


