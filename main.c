#include <stdio.h>
#include "global.h"
#include "main.h"

void display(void) // function that displays our gameboard
{
  printf("-------------\n");
  for(int l = 0; l < NBL;l++)
    {
      for(int c = 0; c < NBC;c++)
	{
	  printf("%c ", tab[l][c]);
	}
      printf("\n");
    }
  printf("-------------\n");
}

void init(void)//function that initializes the tab / our gameboard
{
  for(int l = 0; l < NBL;l++)
    {
      for(int c = 0; c < NBC;c++)
	{
	  tab[l][c] = '.';
	}
    }
}

void empty_stdin (void) //empty the buffer
{
  int c = getchar();

  while (c != '\n' && c != EOF)
    {
      c = getchar();
    }
}


int verticalVerif(pToken)//function to verify if 4 tokens are vertically aligned
{
  for(int l = 0;l < NBL-3; l++)
    {
      for(int c = 0;c < NBC; c++)
	{
	  if (tab[l][c] == pToken && tab[l+1][c] == pToken && tab[l+2][c] == pToken && tab[l+3][c] == pToken)
	    {
	      return 1;
	      break;
	    }
	}
    }
  return 0;
}

int horizontalVerif(pToken)//function to verify if 4 tokens are horizontally aligned
{
  for(int l = 0;l < NBL; l++)
    {
      for(int c = 0;c < NBC-3; c++)
	{
	  if (tab[l][c] == pToken && tab[l][c+1] == pToken && tab[l][c+2] == pToken && tab[l][c+3] == pToken)
	    {
	      return 1;
	      break;
	    }
	}
    }
  return 0;
}

int diagVerif(pToken) //function to verify if 4 tokens are diagonally aligned
{

  //verif diag top right
  for(int l = NBL - 1;l > NBL - 4; l--)
    {
      for(int c = 0;c < NBC - 3; c++)
	{
	  if (tab[l][c] == pToken && tab[l-1][c+1] == pToken && tab[l-2][c+2] == pToken && tab[l-3][c+3] == pToken)
	    {
	      return 1;
	      break;
	    }
	}
    }
  //verif diagonal top left
  for(int l = NBL - 1;l > NBL - 4; l--) //going from bottom to the top, it'll stop at line 5-3 because past there, there                              will never be 4 tokens aligned
    {
      for(int c = 0;c < NBC - 3; c++) // same here, past column 4, no tokens will be aligned from right to left
	{
	  if (tab[l][c] == pToken && tab[l-1][c-1] == pToken && tab[l-2][c-2] == pToken && tab[l-3][c-3] == pToken)
	    {
	      return 1;
	      break;
	    }
	}
    }
  return 0;
}

int verification(int returnValue, int value)
{
  for (;;)
    {
      if (returnValue == EOF)
	{   //user generates manual EOF
	  printf("-> EOF Error");
	  return 0;
	}
      else if (returnValue == 0)
	{    // if no Int in input
	  printf("-> Il s'agirait de mettre un int enfait\n");
	  empty_stdin();
	  return 0;
	}
      else if (value < 1 || 7 < value)
	{  // not in the range
	  printf("-> Choose a valid column please [1-7]\n");
	  empty_stdin();
	  return 0;
	}
      else
	{  //good input
	  empty_stdin();
	  break;
	}
    }

  return 1;
}

int main(void){

  int player = 0;
  int end = 0;
  int column = 200;  //200 is to allow the program to enter the while loop (could have used a do/while)
  int columnFilled[7] = {0,0,0,0,0,0,0}; //determine if a column is filled or not
  int over = 1; //bool that determines if there's a game over or if someone won
  int verif = 0;
  int returnValue;
  init();
  while (end < 42) //end will increase by 1 whenever a token is placed

    {
      display();

      while ((column < 1 ||column > 7) || column == 200 || columnFilled[column-1]== 1 || verif == 0)
	{
	  if(column < 7 && column > 1) //to avoid accessing a unavailable spot in my columnTab list
	    {
	      if(columnFilled[column-1] == 1)
		{
		  printf("This column is full, try another one !\n");
		  column = 200;
		}
	    }

	  printf("[Player %d] Choose a column : ",player+1);
	  returnValue = scanf("%d",&column);
	  verif = verification(returnValue,column);
	}

      if (tab[0][column-1] == '.')
	{
	  for(int row = 5;row > -1;row--)
	    {
	      //printf("%d",row);
	      if (tab[row][column-1] == '.')
		{
		  tab[row][column-1] = tokens[player]; //replace the empty spot by the player's token
		  break; //exit the loop
		}
	      if (row == 1) // when i reach the top of a column, it'll add 1 to the columnFilled tab
		{
		  columnFilled[column-1] = 1;
		}
	    }
	  end++;
	}
      //Verifies if 4 tokens are aligned (vertically,horizontally or diagonally)
      if(verticalVerif(tokens[player]) == 1 || horizontalVerif(tokens[player]) == 1 || diagVerif(tokens[player]) == 1)
	{
	  end = 42;
	  printf("\n[Player %d] won the game ! Good Job\n\n", player+1);
	  over = 0; // there's a winner so there will not be any game over
	}

      if(player == 0)
	{
	  player++; //change to player 2
	}
      else
	{
	  player--; // go back to player 1
	}
      column = 200; //so we'll reenter the while loop // only doable since column will never reach 200 with the user's inputs
    }
  display();//displays the board
  if(over == 1)
    {
      printf("Game Over");
    }
  printf("\nThanks for playing to Connect 4");
}


