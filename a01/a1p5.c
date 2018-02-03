#include "tictactoe.h"

int main()
{
  unsigned short us;
  char b3[10];
  char userName[50];
  char board[60];
  char userInput;
  int user;
  int turnCount;


  FILE * fp;
  struct strategy_struct cpuMove;
  fp = fopen("strategyfile.bin","rb");


  cpuMove.best_move=100;
  cpuMove.winner='x';
  us=0;


  printf("\nSHALL WE PLAY A GAME?\n\n");
  printf("PLEASE ENTER YOUR NAME: ");
  fgets(userName,50,stdin);
  printf("\nGREETINGS %s\n",userName);
  printf("Which side would you like to play (X/O)? ");
  scanf("%c",&userInput);

  if(userInput=='O')
  {
    printf("Ok, you will be O; I will be X.\n");
    b3fromus(b3,us);
    boardfromb3(board,b3);
    turnCount=0; /*cpu goes first*/
    while(winner(us)==' ')
    {
      if(turnCount==0)
      {
        get_record(fp,us,&cpuMove);
        printf("My turn; my move is %d\n",cpuMove.best_move);
        us=next(us,cpuMove.best_move);
        b3fromus(b3,us);
        boardfromb3(board,b3);
        turnCount=1;
      }
      else
      {
        printf("Your turn; choose a move [0-8]: ");
        scanf(" %d",&user);
        us=next(us,user);
        b3fromus(b3,us);
        boardfromb3(board,b3);
        turnCount=0;
      }

    }

  }
  else if(userInput=='X')
    {
      printf("Ok, you will be X; I will be O.\n");
      b3fromus(b3,us);
      boardfromb3(board,b3);
      turnCount=1;/*user goes first*/
      while(winner(us)==' ')
      {
        if(turnCount==0)
        {
          get_record(fp,us,&cpuMove);
          printf("My turn; my move is %d\n",cpuMove.best_move);
          us=next(us,cpuMove.best_move);
          b3fromus(b3,us);
          boardfromb3(board,b3);
          turnCount=1;
        }
        else
        {
          printf("Your turn; choose a move [0-8]: ");
          scanf(" %d",&user);
          us=next(us,user);
          b3fromus(b3,us);
          boardfromb3(board,b3);
          turnCount=0;
        }

      }


  }

  if(winner(us)=='0')
  {
    printf("The game is a tie.\n");
  }
  else
  {
    printf("I win!\n");
  }

  printf("A STRANGE GAME.\nTHE ONLY WINNING MOVE IS\nNOT TO PLAY.\n");

  return 0;
}
