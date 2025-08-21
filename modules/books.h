#ifndef BOOKS_H
#define BOOKS_H

#define BOOK_PREFIX "BK"
#include "models.h"

void initializeBooksList(Book **booksList, int *booksCount);
void loadBooks(Book *booksList, int *numBooks, const char *filename);
void saveBooks(const Book *booksList, int numBooks, const char *filename);
void freeBooks(Book *booksList);

void addBook(Book *booksList, int *numBooks, int id, const char *title, const char *author);
void removeBook(Book *booksList, int *numBooks, int id);
Book* searchBook(Book **booksList, char *bookCode);
void editBook(Book *booksList, int numBooks, int id, const char *title, const char *author, int available);

// void displayBooks(const Book *books, int numBooks);
// void searchBook(const Book *books, int numBooks, const char *title);

// void sortBooksByTitle(Book *books, int numBooks);
// void sortBooksByAuthor(Book *books, int numBooks);
// void sortBooksByAvailability(Book *books, int numBooks);
// void filterBooksByAuthor(const Book *books, int numBooks, const char *author, Book *results, int *numResults);
// void filterBooksByAvailability(const Book *books, int numBooks, int available, Book *results, int *numResults);

// void saveBooksAsText(const Book *books, int numBooks, const char *filename);
// void loadBooksFromText(Book *books, int *numBooks, const char *filename);
// void saveBooksAsCSV(const Book *books, int numBooks, const char *filename);
// void loadBooksFromCSV(Book *books, int *numBooks, const char *filename);
// void saveBooksAsJSON(const Book *books, int numBooks, const char *filename);
// void loadBooksFromJSON(Book *books, int *numBooks, const char *filename);


#endif