#include "tictactoe.h"

int main()
{
  int c;
  FILE * fp;
  struct strategy_struct r;

  r.best_move=-1;
  r.winner=' ';

  fp = fopen("strategyfile.bin","wb");
  for(c=0;c<19683;c++)
  {
  fwrite(&r,sizeof(r),1,fp);
  }
  fclose(fp);
  return 0;
}
