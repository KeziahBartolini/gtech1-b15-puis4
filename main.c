#include <stdio.h>
#define NBL 6
#define NBC 7

char tab[NBL][NBC];
char tokens[] = "ox";


void affiche(void){
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

void init(void){
  for(int l = 0; l < NBL;l++)
    {
      for(int c = 0; c < NBC;c++)
	{
	  tab[l][c] = '.';
	}
    }
}


int main(void){

  int player = 0;
  int end = 0;
  int column = 200;
  int row = 5;
  int columnFilled[7] = {0,0,0,0,0,0,0};
  init();
  while (end < 42)

    {
      affiche();
      while ((column < 1 || column > 7 ) || column == 200 || columnFilled[column-1]== 1)
	{
	  if(columnFilled[column-1] == 1)
	    {
	      printf("The column is full, try another one !\n");
	    }
	  printf("[Player %d] Choose a column : ",player+1);
	  scanf("%d",&column);
	}

      if (tab[0][column-1] == '.')
	{
	  for(int row = 5;row > -1;row--)
	    {
	      //printf("%d",row);
	      if (tab[row][column-1] == '.')
		{
		  tab[row][column-1] = tokens[player];
		  break;
		}
	      if (row == 1)
		{
		  columnFilled[column-1] = 1;
		}
	    }
	  end++;
	}

      if(player == 0)
	{
	  player++;
	}
      else
	{
	  player--;
	}
      column = 200;

    }
  affiche();
  printf("Game Over !");
    }


