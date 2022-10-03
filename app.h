#ifndef APP_H
#define APP_H

#include "STD_TYPES.h"

#define BOOKS_DATABASE_SIZE 100

typedef struct user
{
    u8 name[10];
    u8 pass[5];
} user;

typedef enum bookStatus
{
    IN_STOCK,
    OUT_OF_STOCK
} bookStatus;

typedef enum errorCode
{
    OK,
    FULL_DATABASE,
    EMPTY_DATABASE,
    BOOK_EXISTS_IN_DATABASE,
    BOOK_NOT_FOUND,
    INVALID_LOGIN
} errorCode;

typedef struct book
{
    u8 name[50];
    u8 author[50];
    u8 releaseYear[5];
    bookStatus status;
} book;

errorCode printWelcomeMessage();

errorCode printClosingMessage();

errorCode printOptions();

errorCode bookSearch();

errorCode addBook();

errorCode removeBook();

errorCode printBooks();

errorCode borrowBook();

errorCode userLogin(user u);

errorCode changePassword();

#endif