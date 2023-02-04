#include <stdio.h>
#include <string.h>
#include "app.h"

static book booksDatabase[BOOKS_DATABASE_SIZE] = {{"C Primer Plus", "Stephen Prata", "2004", IN_STOCK}, {"C Programming", "K. N. King", "2008", IN_STOCK}, {"Python", "Author", "2000", OUT_OF_STOCK}};
static user defaultUser = {"user", "1234"};

static u16 nextBookIndex = 3;

errorCode printWelcomeMessage()
{
    printf("**********************************************\n");
    printf("*                                            *\n");
    printf("*           Welcome to our library           *\n");
    printf("*                                            *\n");
    printf("**********************************************\n");
    return OK;
}

errorCode printClosingMessage()
{
    printf("\n\n******************Thank You******************\n\n\n");
    return OK;
}

errorCode printOptions()
{
    printf("\nThe available options are:\n");
    printf("1) Add a new book             2) Remove a book\n");
    printf("3) Search for a book          4) Print all the books\n");
    printf("5) Borrow a book              6) Change your password\n");
    printf("7) Exit\n");
    printf("\nSelect the option number: ");
}

errorCode bookSearch()
{
    u8 bookName[50];
    printf("\nEnter the book name: ");
    fflush(stdin);
    scanf("%[^\n]s", bookName);
    for (u16 i = 0; i < nextBookIndex; i++)
    {
        if (!strcmp(booksDatabase[i].name, bookName))
        {
            printf("\nBook information: \n");
            printf("\033[1m\033[30m"
                   "        Name                Author              Release Year            Status\n"
                   "\033[0m");
            printf("-----------------------------------------------------------------------------------\n");
            printf("    ");
            printf("%-21s", booksDatabase[i].name);
            printf("%-26s", booksDatabase[i].author);
            printf("%-20s", booksDatabase[i].releaseYear);
            if (booksDatabase[i].status == IN_STOCK)
            {
                printf("In Stock");
            }
            else
            {
                printf("\033[1m\033[31m"
                       "Out Of Stock"
                       "\033[0m");
            }
            printf("\n");
            printf("-----------------------------------------------------------------------------------\n\n");
            return OK;
        }
    }
    printf("\nBook not found!\n");
    return BOOK_NOT_FOUND;
}

errorCode addBook()
{
    if (nextBookIndex == BOOKS_DATABASE_SIZE)
    {
        printf("\033[1m\033[31m"
               "\nThe database is full"
               "\033[0m");
        return FULL_DATABASE;
    }
    book b;
    printf("Enter the book name: ");
    fflush(stdin);
    scanf("%[^\n]s", b.name);
    for (u16 i = 0; i < nextBookIndex; i++)
    {
        if (!strcmp(booksDatabase[i].name, b.name))
        {
            printf("\nThis book is already in the database");
            return BOOK_EXISTS_IN_DATABASE;
        }
    }
    printf("Enter the book author: ");
    fflush(stdin);
    scanf("%[^\n]s", b.author);
    printf("Enter the book release year: ");
    fflush(stdin);
    scanf("%s", b.releaseYear);
    strcpy(booksDatabase[nextBookIndex].author, b.author);
    strcpy(booksDatabase[nextBookIndex].name, b.name);
    strcpy(booksDatabase[nextBookIndex].releaseYear, b.releaseYear);
    booksDatabase[nextBookIndex].status = IN_STOCK;
    nextBookIndex++;
    return OK;
}

errorCode removeBook()
{
    if (nextBookIndex == 0)
    {
        printf("\033[1m\033[31m"
               "\nEmpty Database\n"
               "\033[0m");
        return EMPTY_DATABASE;
    }
    else
    {
        book b;
        printf("Enter the book name: ");
        fflush(stdin);
        scanf("%[^\n]s", b.name);
        for (u16 i = 0; i < nextBookIndex; i++)
        {
            if (!strcmp(booksDatabase[i].name, b.name))
            {
                for (u16 j = i; j < nextBookIndex - 1; j++)
                {
                    strcpy(booksDatabase[j].name, booksDatabase[j + 1].name);
                    strcpy(booksDatabase[j].author, booksDatabase[j + 1].author);
                    strcpy(booksDatabase[j].releaseYear, booksDatabase[j + 1].releaseYear);
                    booksDatabase[j].status = booksDatabase[j + 1].status;
                }
                nextBookIndex--;
                printf("\nBook removed successfully!\n");
                return OK;
            }
        }
        printf("\nBook not found!\n");
    }
    return BOOK_NOT_FOUND;
}

errorCode printBooks()
{
    if (nextBookIndex == 0)
    {
        printf("\033[1m\033[31m"
               "\nEmpty Database\n"
               "\033[0m");
        return EMPTY_DATABASE;
    }
    else
    {
        printf("\nBooks in the library are:\n");
        printf("-------------------------\n\n");
        printf("\033[1m\033[30m"
               "        Name                Author              Release Year            Status\n"
               "\033[0m");
        printf("-----------------------------------------------------------------------------------\n");
        for (u16 i = 0; i < nextBookIndex; i++)
        {
            printf("    ");
            printf("%-21s", booksDatabase[i].name);
            printf("%-26s", booksDatabase[i].author);
            printf("%-21s", booksDatabase[i].releaseYear);
            if (booksDatabase[i].status == IN_STOCK)
            {
                printf("In Stock");
            }
            else
            {
                printf("\033[1m\033[31m"
                       "Out Of Stock"
                       "\033[0m");
            }
            printf("\n");
        }
        printf("-----------------------------------------------------------------------------------\n");
    }
    return OK;
}

errorCode borrowBook()
{
    book b;
    printf("Enter the book name: ");
    fflush(stdin);
    scanf("%[^\n]s", b.name);
    for (u16 i = 0; i < nextBookIndex; i++)
    {
        if (!strcmp(booksDatabase[i].name, b.name))
        {
            if (booksDatabase[i].status == OUT_OF_STOCK)
            {
                printf("\nThis book is out of stock!\n");
                return BOOK_NOT_FOUND;
            }
            else
            {
                printf("\nSuccessful operation!\n");
                booksDatabase[i].status = OUT_OF_STOCK;
                return OK;
            }
        }
    }
    printf("\nBook not found!\n");
    return BOOK_NOT_FOUND;
}

errorCode userLogin(user u)
{
    if (strcmp(u.name, defaultUser.name) == 0 && strcmp(u.pass, defaultUser.pass) == 0)
        return OK;
    return INVALID_LOGIN;
}

errorCode changePassword()
{
    u8 newPass[5];
    printf("\nEnter a new password of 4 characters: ");
    fflush(stdin);
    scanf("%[^\n]s", newPass);
    strcpy(defaultUser.pass, newPass);
    printf("Password changed successfully!\n");
    return OK;
}
