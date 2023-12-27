#ifndef AUTH_H
#define AUTH_H

struct User
{
   int role;
   char username[50 + 1];
   char hashed_password[64 + 1];
};

void createNewUser();
int authenticateUser(struct User *authenticatedUser, int *isAdmin);

#endif // AUTH_H
