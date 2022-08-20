#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void printScore(int player1Score, int player2Score);
void initializeElements(int height, int width, int* player1RacketPosition, int* player2RacketPosition, int* ballX, int* ballY, int* ballDx, int* ballDy);
void displayField(int height, int width, int player1RacketPosition, int player2RacketPosition, int ballX, int ballY);
int isOut(int ballX, int width);
int isCollisionWithWall(int ballY, int ballDy, int height);
int isCollisionWithRacket(int ballX, int ballY, int ballDx, int player1RacketPosition, int player2RacketPosition, int width);
void moveBall(int* ballX, int* ballY, int ballDx, int ballDy);
int makeTurn(char input, int* player1RacketPosition, int* player2RacketPosition, int* ballX, int* ballY, int* ballDx, int* ballDy, int width, int height);

int main() {
  int height = 25, width = 80;
  int player1Score = 0, player2Score = 0;
  int player1RacketPosition, player2RacketPosition, ballX, ballY, ballDx, ballDy;
  char input;

  //initializeField(field, height, width);
  initializeElements(height, width, &player1RacketPosition, &player2RacketPosition, &ballX, &ballY, &ballDx, &ballDy);
  printScore(player1Score, player2Score);
  displayField(height, width, player1RacketPosition, player2RacketPosition, ballX, ballY);

  
  while (player1Score < 21 && player2Score < 21) {
    input = getchar();

    if (input != ' ' && input != 'a' && input != 'z' && input != 'k' && input != 'm') {
      continue;
    }
    int roundOver = makeTurn(input, &player1RacketPosition, &player2RacketPosition, &ballX, &ballY, &ballDx, &ballDy, width, height);
    if (roundOver == 1) {
      if (ballX < 40) {
        player2Score++;
      }
      else {
        player1Score++;
      }
      initializeElements(height, width, &player1RacketPosition, &player2RacketPosition, &ballX, &ballY, &ballDx, &ballDy);
    }
    system("cls");
    printScore(player1Score, player2Score);
    displayField(height, width, player1RacketPosition, player2RacketPosition, ballX, ballY);
  }

  printf("Game over!");
  
  return 0;
}

void printScore(int player1Score, int player2Score) {
  printf("%38d%7d\n", player1Score, player2Score);
}

void initializeElements(int height, int width, int* player1RacketPosition, int* player2RacketPosition, int* ballX, int* ballY, int* ballDx, int* ballDy) {
  *player1RacketPosition = height / 2 - 1;
  *player2RacketPosition = height / 2 - 1;
  *ballX = width / 2;
  *ballY = 0;
  *ballDx = -1;
  *ballDy = 1;
}


void displayField(int height, int width, int player1RacketPosition, int player2RacketPosition, int ballX, int ballY) {
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      
      if ((i == player1RacketPosition || i == (player1RacketPosition + 1) || i == (player1RacketPosition + 2)) && j == 1) {
        printf("|");
      } else if ((i == player2RacketPosition || i == (player2RacketPosition + 1) || i == (player2RacketPosition + 2)) && j == width - 2) {
        printf("|");
      }
      else if (i == ballY && j == ballX) {
        printf("O");
      }
      else {
        if (j == 0 || j == width - 1 || i == 0 || i == height - 1) {
          printf("*");
        }

        // Print center net
        else if (j == width / 2) {
          printf("#");
        }

        // Fill all free space with spaces
        else {
          printf(" ");
        }
      }
      
    }
    printf("\n");
  }
  
}

int isOut(int ballX, int width) {
  if (ballX == 1 || ballX == width - 2) {
    return 1;
  }
  else {
    return 0;
  }
}

int isCollisionWithWall(int ballY, int ballDy, int height) {
  if ((ballY == 1) && (ballDy == -1) || (ballY == (height - 2)) && (ballDy = 1)) {
    return 1;
  }
  else {
    return 0;
  }
}

int isCollisionWithRacket(int ballX, int ballY, int ballDx, int player1RacketPosition, int player2RacketPosition, int width) {
  if ((ballX == 2 && (ballDx == -1) && ballY >= player1RacketPosition && ballY <= (player1RacketPosition + 2)) ||
    (ballX == (width - 3) && (ballDx == 1) && ballY >= player2RacketPosition && ballY <= (player2RacketPosition + 2))) {
    return 1;
  }
  else {
    return 0;
  }
}

void moveBall(int* ballX, int* ballY, int ballDx, int ballDy) {
  *ballX += ballDx;
  *ballY += ballDy;
}

int makeTurn(char input, int* player1RacketPosition, int* player2RacketPosition, int* ballX, int* ballY, int* ballDx, int* ballDy, int width, int height) {
  switch (input) {
  case ' ':
    moveBall(ballX, ballY, *ballDx, *ballDy);
    break;
  case 'a':
    if (*player1RacketPosition > 1) {
      *player1RacketPosition -= 1;
    }
    moveBall(ballX, ballY, *ballDx, *ballDy);
    break;
  case 'z':
    if (*player1RacketPosition < (height - 1)) {
      *player1RacketPosition += 1;
    }
    moveBall(ballX, ballY, *ballDx, *ballDy);
    break;
  case 'k':
    if (*player2RacketPosition > 1) {
      *player2RacketPosition -= 1;
    }
    moveBall(ballX, ballY, *ballDx, *ballDy);
    break;
  case 'm':
    if (*player2RacketPosition < (height - 1)) {
      *player2RacketPosition += 1;
    }
    moveBall(ballX, ballY, *ballDx, *ballDy);
    break;
  default:
    break;
  }

  if (isOut(*ballX, width) == 1) {
    return 1;
  }

  if (isCollisionWithWall(*ballY, *ballDy, height) == 1) {
    *ballDy = -(*ballDy);
  }

  if (isCollisionWithRacket(*ballX, *ballY, *ballDx, *player1RacketPosition, *player2RacketPosition, width)) {
    *ballDx = -(*ballDx);
  }

  return 0;
}

