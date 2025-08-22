#include "models.h"
#include "books.h"

#include "books.h"

void initializeBookList(Book **bookList, int *bookCount) {
    if (bookList == NULL || bookCount == NULL) {
        fprintf(stderr, "Error: Null pointer passed to initializeBookList.\n");
        return;
    }
    *bookList = NULL;
    *bookCount = 0;
}

void addBook(Book **bookList, int *bookCount) {
    if (bookList == NULL || bookCount == NULL) {
        fprintf(stderr, "Error: Null pointer passed to addBook.\n");
        return;
    }

    Book newBook;
    sprintf(newBook.code, "%s%03d", BOOK_PREFIX, *bookCount + 1);

    printf("Enter book title: ");
    fgets(newBook.title, sizeof(newBook.title), stdin);
    newBook.title[strcspn(newBook.title, "\n")] = '\0';

    printf("Enter book author: ");
    fgets(newBook.author, sizeof(newBook.author), stdin);
    newBook.author[strcspn(newBook.author, "\n")] = '\0';

    printf("Enter available copies: ");
    scanf("%d", &newBook.available);
    getchar();

    *bookList = realloc(*bookList, (*bookCount + 1) * sizeof(Book));
    if (*bookList == NULL) {
        fprintf(stderr, "Error: Memory allocation failed in addBook.\n");
        return;
    }

    (*bookList)[*bookCount] = newBook;
    (*bookCount)++;

    printf("Book added successfully! Total books: %d\n", *bookCount);
}

void removeBook(Book **bookList, int *bookCount, char *bookCode) {
    if (bookList == NULL || bookCount == NULL) {
        fprintf(stderr, "Error: Null pointer passed to removeBook.\n");
        return;
    }

    for (int i = 0; i < *bookCount; i++) {
        if (strcmp((*bookList)[i].code, bookCode) == 0) {
            for (int j = i; j < *bookCount - 1; j++) {
                (*bookList)[j] = (*bookList)[j + 1];
            }
            (*bookCount)--;
            if (*bookCount > 0) {
                *bookList = realloc(*bookList, (*bookCount) * sizeof(Book));
                if (*bookList == NULL) {
                    fprintf(stderr, "Error: Memory allocation failed in removeBook.\n");
                    return;
                }
            } else {
                free(*bookList);
                *bookList = NULL;
            }
            printf("Book %s removed successfully. Total books: %d\n", bookCode, *bookCount);
            return;
        }
    }

    printf("Book with ID %s not found.\n", bookCode);
}

Book* searchBook(Book **bookList, char *bookCode, const int *bookCount) {
    if (bookList == NULL || bookCode == NULL || bookCount == NULL) {
        fprintf(stderr, "Error: Null pointer passed to searchBook.\n");
        return NULL;
    }

    for (int i = 0; i < *bookCount; i++) {
        if (strcmp((*bookList)[i].code, bookCode) == 0) {
            printf("Book %s found!\n", bookCode);
            return &(*bookList)[i];
        }
    }

    printf("Book %s not found!\n", bookCode);
    return NULL;
}

void editBook(Book *book) {
    if (book == NULL) {
        fprintf(stderr, "Error: Null pointer passed to editBook.\n");
        return;
    }

    printf("Enter new title: ");
    fgets(book->title, sizeof(book->title), stdin);
    book->title[strcspn(book->title, "\n")] = '\0';

    printf("Enter new author: ");
    fgets(book->author, sizeof(book->author), stdin);
    book->author[strcspn(book->author, "\n")] = '\0';

    printf("Enter new number of available copies: ");
    scanf("%d", &book->available);
    getchar(); // consume newline
}

void saveBooksCSV(const char *filename, Book *bookList, int bookCount) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Error opening file");
        return;
    }

    fprintf(file, "code,title,author,available\n");
    for (int i = 0; i < bookCount; i++) {
        fprintf(file, "%s,%s,%s,%d\n", 
            bookList[i].code, 
            bookList[i].title, 
            bookList[i].author, 
            bookList[i].available);
    }

    fclose(file);
}

void loadBooksCSV(const char *filename, Book **bookList, int *bookCount) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return;
    }

    char line[512];
    fgets(line, sizeof(line), file);

    *bookList = NULL;
    *bookCount = 0;

    while (fgets(line, sizeof(line), file)) {
        *bookList = realloc(*bookList, (*bookCount + 1) * sizeof(Book));
        Book *b = &(*bookList)[*bookCount];

        char *token = strtok(line, ",");
        strcpy(b->code, token);

        token = strtok(NULL, ",");
        strcpy(b->title, token);

        token = strtok(NULL, ",");
        strcpy(b->author, token);

        token = strtok(NULL, ",");
        b->available = atoi(token);

        (*bookCount)++;
    }

    fclose(file);
}
