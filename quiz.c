#include <stdio.h>
#include <string.h>
#include "quiz.h"

int quesCount = 0;
struct Question quiz[10];

void displayQuestion(int quesIndex)
{
   printf("%s\n", quiz[quesIndex].question);

   for (int i = 0; i < 4; i++)
      printf("%c. %s\n", 65 + i, quiz[quesIndex].options[i]);
}

void loadQuiz()
{
   struct Question question;

   FILE *file = fopen("questions.dat", "rb");

   if (file != NULL)
   {
      printf("Question List:\n");
      while (fread(&question, sizeof(struct Question), 1, file) == 1)
      {
         quiz[quesCount] = question;
         quesCount++;
      }

      fclose(file);
   }
   else
   {
      printf("Error opening the file for reading.\n");
   }
}

void startQuiz()
{
   int score = 0;

   for (int i = 0; i < quesCount; ++i)
   {
      displayQuestion(i);

      char answer;
      printf("Your answer (A/B/C/D): ");
      scanf(" %c", &answer);

      int selectedOption = answer - 'A';

      if (selectedOption == quiz[i].correctOption)
      {
         printf("Correct!\n");
         score++;
      }
      else
      {
         printf("Incorrect. Correct answer is %c.\n", 'A' + quiz[i].correctOption);
      }
   }

   printf("Quiz completed. Your score: %d/5\n", score);
}

void viewQuestions()
{
   loadQuiz();

   for (int i = 0; i < quesCount; ++i)
   {
      displayQuestion(i);
   }
}

void createQuestion()
{
   struct Question newQuestion;

   printf("Enter question: ");
   scanf(" %[^\n]s", newQuestion.question);

   for (int i = 0; i < 4; i++)
   {
      printf("Enter option (%d-4): ", i + 1);
      scanf(" %[^\n]s", newQuestion.options[i]);
   }

   printf("Correct option (0-3): ");
   scanf("%d", &newQuestion.correctOption);

   FILE *file = fopen("questions.dat", "ab");

   if (file != NULL)
   {
      fwrite(&newQuestion, sizeof(struct Question), 1, file);
      fclose(file);

      printf("Question added successfully.\n");
   }
   else
   {
      printf("Error opening the file for writing.\n");
   }
}