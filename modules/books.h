#ifndef BOOKS_H
#define BOOKS_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "models.h"
#include "utils.h"

void initializeBookList(Book **bookList, int *bookCount);

void addBook(Book **bookList, int *bookCount);
void removeBook(Book **bookList, int *bookCount, char *bookCode);
Book* searchBook(Book **bookList, char *bookCode, const int *bookCount);
void editBook(Book *book);

void saveBooksCSV(const char *filename, Book *bookList, int bookCount);
void loadBooksCSV(const char *filename, Book **bookList, int *bookCount);


#endif