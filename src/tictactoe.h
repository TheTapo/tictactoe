#include <stdio.h>
#include <math.h>
#include <stdbool.h>

typedef struct Grid {
  char G[3][3];
} grid;

void prepareGrid(grid *ptr) {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      ptr->G[i][j] = (char) (3 * i + j + 1) + '0';
    }
  }
}

bool isFilled(grid *ptr, int position) {
  int i =  ceil((float)(position) / 3) - 1;
  int j;
  if (position <= 3) {
    j = position - 1;
  }
  else if (position > 3 && position <= 6) {
    j = position - 4;
  }
  else {
    j = position - 7;
  }
  if (ptr->G[i][j] == 'O' || ptr->G[i][j] == 'X') {
    return true;
  }
  else {
    return false;
  }
}

bool isWon(grid *ptr, char symbol) {
  int countI = 0, countJ = 0, countD = 0, countD2 = 0;
  int local3 = 0, local4 = 0;
  for (int i = 0; i < 3; i++) {
    int local1 = 0, local2 = 0;
    for (int j = 0; j < 3; j++) {
      if (ptr->G[i][j] == symbol) {
        local1++;
        countI = local1;
      }
      if (ptr->G[j][i] == symbol) {
        local2++;
        countJ = local2;
      }
      if (i + j == 2 && ptr->G[i][j] == symbol) {
        local3++;
        countD = local3;
      }
      if (i == j && ptr->G[i][j] ==  symbol) {
        local4++;
        countD2 = local4;
      }
    }
  }
  if (countI == 3 || countJ == 3 || countD == 3 || countD2 == 3) {
    return true;
  }
  else {
    return false;
  }
}

void printGrid(grid *ptr) {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (j < 2) {
        printf("%c ",ptr->G[i][j]);
      }
      else {
        printf("%c\n",ptr->G[i][j]);
      }
    }
  }
}

void fillChoice(grid *ptr, char symbol, int position) {
  int i =  ceil((float)(position) / 3) - 1;
  int j;
  if (position <= 3) {
    j = position - 1;
  }
  else if (position > 3 && position <= 6) {
    j = position - 4;
  }
  else {
    j = position - 7;
  }
  if (!isFilled(ptr, position) && position >= 0 && position <= 9) {
    ptr->G[i][j] = symbol;
  }
}

void game(grid *ptr) {
  prepareGrid(ptr);
  int count = 0;
  char symbol;
  while (count < 9) {
    printGrid(ptr);
    int position;

    if (count % 2 == 0) {
      symbol = 'X';
    }
    else {
      symbol = 'O';
    }

    printf("Player %c's turn\n", symbol);
    printf("Enter Position: ");
    scanf("%d",&position);

    if (!isFilled(ptr, position) && position < 10 && position > 0) {
      fillChoice(ptr,symbol,position);
      count++;
    }
    else {
      printf("Try Again\n");
    }
    if (isWon(ptr, symbol)) {
      printGrid(ptr);
      printf("%c Wins The Game\n",symbol);
      break;
    }
  }
  if (!isWon(ptr, 'O') && !isWon(ptr, 'X') && count == 9) {
    printf("The Game Ends In A Draw\n");
  }
}
