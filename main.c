#include <stdio.h>
#include <stdlib.h>
#include "auth.h"
#include "quiz.h"

/**
 * @brief Start command to build and run this project
 *
 * gcc main.c auth.c quiz.c -o main
 *
 * ./main
 *
 *
 */
int main()
{
   int choice;
   int isAdmin = 0;
   struct User authenticatedUser;

   int authBreak = 1;

   while (authBreak)
   {
      printf("1. Register\n");
      printf("2. Login\n");
      printf("3. Exit\n");
      printf("Enter your choice: ");
      scanf("%d", &choice);

      switch (choice)
      {
      case 1:
         createNewUser();
         break;
      case 2:
         if (authenticateUser(&authenticatedUser, &isAdmin))
         {
            printf("Authentication successful. Welcome, %s!\n", authenticatedUser.username);

            if (isAdmin)
            {
               printf("You are an admin.\n");
               // Add admin functionality here if needed
            }
            else
            {
               printf("You are a user.\n");
               loadQuiz();
            }

            authBreak = 0;
         }
         break;
      case 3:
         printf("Exiting...\n");
         exit(0);
      default:
         printf("Invalid choice. Please try again.\n");
      }
   }

   if (isAdmin == 0)
   {
      while (1)
      {
         printf("1. Start Quiz\n");
         printf("2. Exit\n");
         printf("Enter your choice: ");
         scanf("%d", &choice);

         switch (choice)
         {
         case 1:
            startQuiz();
            break;
         case 2:
            printf("Exiting...\n");
            exit(0);
         default:
            printf("Invalid choice. Please try again.\n");
         }
      }
   }
   else
   {
      while (1)
      {
         printf("1. Create Question\n");
         printf("2. View Questions\n");
         printf("3. Exit\n");
         printf("Enter your choice: ");
         scanf("%d", &choice);

         switch (choice)
         {
         case 1:
            createQuestion();
            break;
         case 2:
            viewQuestions();
            break;
         case 3:
            printf("Exiting...\n");
            exit(0);
         default:
            printf("Invalid choice. Please try again.\n");
         }
      }
   }

   return 0;
}