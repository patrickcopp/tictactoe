#include "tictactoe.h"
void boardfromb3 (char board[60],char b3[10])
{
  int c;
  int spots[9]={1,5,9,25,29,33,49,53,57}; /*spots on board that xs or os */
  strcpy(board,"   |   |   \n---+---+---\n   |   |   \n---+---+---\n   |   |  \n");
  for(c=0;c<9;c++)
  {
    switch(b3[c])
    {
      case '1':
        board[spots[c]]='O';
        break;
      case '2':
        board[spots[c]]='X';
        break;
      case '0':
        break;
      default:
       printf("Error: Bad input at b3[%d]\n",c);

    }
  }
  printf("%s\n",board);
}

void b3fromboard(char b3[10], char board[60])
{
  int c;
  int charSpots[9]={1,5,9,25,29,33,49,53,57};
  for(c=0;c<9;c++)
  {
    switch(charSpots[c]) /* if it's an x put a 2 on b3, if o then a 1 and if nothing then 0*/
    {
      case 'X':
        b3[c]=2;
        break;
      case 'O':
        b3[c]=1;
        break;
      case ' ':
        b3[c]=0;
        break;
    }
  }
}

unsigned short b3tous(char b3[10])
{
  int i,value;
  unsigned short us;
  us=0,value=1;
  for(i=8;i>-1;i--)
  {
    us+=(value*(b3[i]-'0'));
    value*=3;
  }
  return us;
}

void b3fromus(char b3[10],unsigned short us)
{
  int i;

  b3[9]='\0';

  for(i=8;i>-1;i--)
  {
    b3[i]=us%3+'0';
    us/=3;
  }
}

char get_move (char b3[10])
{
  int c;
  int counter;
  counter=0;
  for(c=0;c<9;c++)
  {
    if(b3[c]=='2' || b3[c]=='1') /* if it's not a 0, someone has moved so add a move */
    {
      counter++;
    }
  }
  return counter+'0';
}

char get_turn(char b3[10])
{
  if(get_move(b3)%2==0) /*x goes on even moves, o on odd*/
  {
    return '2';
  }
  else
  {
    return '1';
  }
}

char winner(unsigned short us)
{
  char b3[10];
  b3fromus(b3,us);
  /*rows*/
  if(b3[0]==b3[1] && b3[1]==b3[2] && b3[0]!='0') return b3[0];
  else if(b3[3]==b3[4] && b3[4]==b3[5] && b3[3]!='0') return b3[3];
  else if(b3[6]==b3[7] && b3[7]==b3[8] && b3[6]!='0') return b3[6];

  /*columns*/
  else if(b3[0]==b3[3] && b3[3]==b3[6] && b3[0]!='0') return b3[0];
  else if(b3[1]==b3[4] && b3[4]==b3[7] && b3[1]!='0') return b3[1];
  else if(b3[2]==b3[5] && b3[5]==b3[8] && b3[2]!='0') return b3[2];

  /*diagonals*/
  else if(b3[0]==b3[4] && b3[4]==b3[8] && b3[0]!='0') return b3[0];
  else if(b3[2]==b3[4] && b3[4]==b3[6] && b3[2]!='0') return b3[2];
  /*no win, board full means a tie*/
  else if(b3[0]!='0' && b3[1]!='0' && b3[2]!='0' && b3[3]!='0' && b3[4]!='0' && b3[5]!='0' && b3[6]!='0' && b3[7]!='0' && b3[8]!='0') return '0';
  /*no win or tie*/
  else
  {
    return ' ';
  }
}

unsigned short next(unsigned short us,char pos)
{
  char b3[10];
  b3fromus(b3,us);
  if((b3[pos+'0'-'0']=='1') || b3[pos+'0'-'0']=='2') /* add 0 and subtract to make it an integer without warnings*/
  {
    return 0; /*returns 0 if it's already taken by an x or o*/
  }
  else
  {
    b3[pos+'0'-'0']=get_turn(b3);
    return b3tous(b3); /*returns unsigned short with the b3 value changed*/
  }
}

void get_record( FILE *fp, unsigned short us, struct strategy_struct *record )
{
  long hello;
  hello=sizeof(struct strategy_struct)*us;
  fseek(fp, hello, SEEK_SET);
  fread(record,sizeof(struct strategy_struct),1,fp);
}

void set_record(FILE *fp, unsigned short us, struct strategy_struct record)
{
  fseek(fp, sizeof(struct strategy_struct)*us, SEEK_SET);
  fwrite(&record,sizeof(struct strategy_struct),1,fp);
}
void evaluate_move(FILE *fp,unsigned short us,struct strategy_struct *record)
{
  char b3[10];
  int c,found_tie,legal_move,tie_value;
  struct strategy_struct r;

  tie_value=0;
  found_tie=0,legal_move=0;

  for(c=0;c<9;c++)
  {
    if(next(us,c)!=0) /* if the spot isn't taken*/
    {

      get_record(fp,next(us,c),&r);
      b3fromus(b3,us);

      if(r.winner==get_turn(b3))
      {
        record->best_move=c;
        record->winner=r.winner;
        return; /* returns if there is a winner because that is best move*/
      }

      else if(r.winner=='0' || r.winner==' ')
      {
        found_tie=1;
        tie_value=c; /*set tie in case no winning value is found*/
      }
      else
      {
        legal_move=c;
      }
    }

  }
  if(found_tie==1)
  {
    record->winner='0';
    record->best_move=tie_value;
  }
  else
  {
    record->best_move=legal_move;
    if(get_turn(b3)=='1')
    {
      record->winner='2'; /*swap move*/
    }
    else
    {
      record->winner='1';
    }
  }

}
