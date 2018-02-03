#include "tictactoe.h"

int main(int argc, char **argv)
{
  int c, input;
  char b3[10];
  FILE * fp;
  struct strategy_struct r;
  fp = fopen("strategyfile.bin","rb+");

  if(argc!=2)
  {
  fprintf( stderr, "Usage: %s [n]\n", argv[0] );
  exit(-1);
  }

  input=atoi(argv[1]);


  for(c=0;c<19683;c++)
  {
    b3fromus(b3,c);
    /* check if game is over*/
    if((winner(c)=='1' || winner(c)=='2' ||winner(c)=='0') && get_move(b3)-'0'==input)
    {

      r.best_move=-1;
      r.winner=winner(c);
      set_record(fp,c,r);

    }
    else if(get_move(b3)-'0'==input)
    {
      evaluate_move(fp,c,&r);
      set_record(fp,c,r);
    }
  }
  fclose(fp);

  return 0;
}
