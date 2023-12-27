#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "auth.h"

void createNewUser()
{
   struct User newUser;

   printf("Enter username(max 50): ");
   scanf("%s", newUser.username);

   printf("Enter password(max 64): ");
   scanf("%s", newUser.hashed_password);

   if (strcmp(newUser.username, "tanvir") == 0)
   {
      newUser.role = 1;
   }
   else
   {
      newUser.role = 0;
   }

   /* char password[50];
   printf("Enter password(max 64): ");
   scanf("%s", password);

   hashPassword(password, newUser.hashed_password); */

   // Open the file for appending user data
   FILE *file = fopen("user_data.dat", "ab");

   if (file != NULL)
   {
      /**
       * @brief Write the new user to the file.
       *
       * Reading one instance of `struct User` from the file pointed to by `file`, and store it in the memory location pointed to by `&user`
       *
       * @param [&newUser] This is the pointer to the memory location containing the data you want to write to the file
       *
       * @param [sizeof(struct User)] This argument specifies the size, in bytes, of each element to be written
       *
       * @param [1] This argument specifies the number of elements to write
       *
       * @param [file] This is a pointer to a FILE object, which represents the file stream you are writing to
       *
       *
       *
       */
      fwrite(&newUser, sizeof(struct User), 1, file);
      fclose(file);

      printf("User successfully registered.\n");
   }
   else
   {
      printf("Error opening the file for writing.\n");
   }
}

int authenticateUser(struct User *authenticatedUser, int *isAdmin)
{
   struct User user;

   char enteredUsername[50 + 1];
   char enteredPassword[64 + 1];

   printf("Enter username(max 50): ");
   scanf("%s", enteredUsername);

   printf("Enter password(max 64): ");
   scanf("%s", enteredPassword);

   // Open the file for reading user data
   FILE *file = fopen("user_data.dat", "rb");

   if (file != NULL)
   {
      /**
       * @brief Search for the entered username in the file.
       *
       * Reading one instance of `struct User` from the file pointed to by `file`, and store it in the memory location pointed to by `&user`
       *
       * @param [&user] This is the pointer to the memory location where the data read from the file will be stored
       *
       * @param [sizeof(struct User)] This argument specifies the size, in bytes, of each element to be read
       *
       * @param [1] This argument specifies the number of elements to read
       *
       * @param [file] --> This is a pointer to a FILE object, which represents the file stream you are reading from
       *
       *
       *
       */
      while (fread(&user, sizeof(struct User), 1, file) == 1)
      {
         if (strcmp(user.username, enteredUsername) == 0)
         {
            /* // Hash the entered password and compare it with the stored hash
            char enteredPasswordHash[65];
            hashPassword(enteredPassword, enteredPasswordHash); */

            if (strcmp(user.hashed_password, enteredPassword) == 0)
            {
               fclose(file);
               *authenticatedUser = user;
               *isAdmin = user.role;

               return 1;
            }
            else
            {
               printf("Authentication failed. Invalid password.\n");
               fclose(file);
               return 0;
            }
         }
      }

      // Username or password is incorrect
      printf("Authentication failed. Invalid username or password.\n");

      fclose(file);
   }
   else
   {
      printf("Error opening the file for reading.\n");
   }

   return 0;
}
