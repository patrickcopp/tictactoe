
#include "tictactoe.h"
int main(int argc, char **argv)
{
  unsigned short us;
  char b3[10];
  char board [60];
  int c;
  int input;
    if(argc!=2)
  {
    fprintf( stderr, "Usage: %s [n]\n", argv[0] );
    exit(-1);
  }
  input=atoi(argv[1]);
  us=input;
  printf("Board Number= %d\n",us);
  b3fromus(b3,us);
  printf("Board b3: %s\n",b3);
  printf("Board pic:\n");
  boardfromb3(board,b3);
  printf("Move: %c\n",get_move(b3));
  printf("Turn: %c\n",get_turn(b3));
  printf("Winner: %c\n",winner(us));
  for(c=0;c<9;c++)
  {
    printf("%d -> %d\n",c,next(us,c));
  }
  return 0;
}
