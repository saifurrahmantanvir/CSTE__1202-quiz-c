#ifndef QUIZ_H
#define QUIZ_H

struct Question
{
   char question[256];
   char options[4][50];
   int correctOption;
};

void displayQuestion(int quesIndex);

void loadQuiz();
void startQuiz();

void viewQuestions();
void createQuestion();

#endif // QUIZ_H
