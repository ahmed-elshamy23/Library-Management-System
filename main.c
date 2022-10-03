#include <stdio.h>
#include <stdlib.h>
#include "app.h"

int main()
{
    user u;
    u8 option, op, flag = 0;
    printWelcomeMessage();
    printf("\nPlease login first to access the library:\n");
    printf("Username: ");
    scanf("%[^\n]s", u.name);
    fflush(stdin);
    printf("Password: ");
    scanf("%[^\n]s", u.pass);
    while (userLogin(u) == INVALID_LOGIN)
    {
        printf("\nYou entered a wrong username or password. Try again\n");
        printf("Username: ");
        fflush(stdin);
        scanf("%[^\n]s", u.name);
        fflush(stdin);
        printf("Password: ");
        scanf("%[^\n]s", u.pass);
    }
    printf("\nYou have logged in successfully!\n");
    do
    {
        if (flag)
        {
            system("cls");
            printWelcomeMessage();
        }
        printOptions();
        fflush(stdin);
        do
        {
            scanf("%d", &option);
        } while (option > 7);
        switch (option)
        {
        case 1:
            if (addBook() == OK)
                printBooks();
            break;
        case 2:
            if (removeBook() == OK)
                printBooks();
            break;
        case 3:
            bookSearch();
            break;
        case 4:
            printBooks();
            break;
        case 5:
            if (borrowBook() == OK)
                printBooks();
            break;
        case 6:
            changePassword();
            break;
        }
        if (option == 7)
            break;
        printf("\nAnother operation? (Y/N) ");
        fflush(stdin);
        scanf("%c", &op);
        flag = 1;
    } while (op != 'N');
    printClosingMessage();
    return 0;
}