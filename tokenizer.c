/*
 * Shereif Saleh
 * tokenizer.c
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

struct TokenizerT_ {
  char * token_index;   // Current token index
  char * token_stream;  // Copy of argv[1]
  char * current_token; // My current_token
  char * token_holder;  // Temp <- this could be optimized more.
};

typedef struct TokenizerT_ TokenizerT;

TokenizerT *TKCreate( char * ts )
{

  struct TokenizerT_ * TOKEN = malloc(sizeof (struct TokenizerT_));
  char* CopyofTs =(char *)malloc( sizeof(TOKEN) );
  strcpy(CopyofTs, ts);
  TOKEN->token_stream = CopyofTs;
  if(TOKEN->token_stream == CopyofTs)
  {
    return TOKEN;
  }
  else
  {
    return NULL;
  }
  free(CopyofTs);
  free(TOKEN);

}
/*
char *Slice (TokenizerT * tk)
{
  int i;
  int count = 0;
  int Length = (strlen(tk->token_stream)+ 1);
  //char * allTokens = malloc(Length)+1;
  for(i = count; i<strlen(tk->token_stream); i++)
  {
    if(tk->token_stream[i] == ' ')
    {
      strncpy()
    }
  }
  //printf("counter is %d\n", count);
  //printf("all my tokens : %s\n", allTokens);
  return tk->token_holder;
}
*/
void TKDestroy( TokenizerT * tk ) {
  free(tk->token_index);
  free(tk->token_stream);
  free(tk->current_token);
  free(tk);

}

char *TKGetNextToken( TokenizerT * tk ) 
{
  const char delimit[2] = " ";
  tk->current_token = strtok(tk->token_stream, delimit);
  while (tk->token_stream != NULL)
  {
    tk->token_stream = strtok(NULL, delimit);
  }
  return tk->current_token;
}

int isOCTAL( TokenizerT * tk )        //Checks if octal
{

  int i = 0;
  int stop = 0;
  int Length = (strlen(tk->current_token)); //Length of current_token
  if(Length > 4 )
  {
    stop = 1;
  }
  for(i = 0; i<Length; i++)
  {
    if(tk->current_token[i] == '.')
    {
      stop = 1;
    }
    if(tk->current_token[0] != '0')
    {
      stop = 1;
    }
    else if(tk->current_token[i] == '8' || tk->current_token[i] == '9')
    {
      stop = 1;
    }
    else if(isalpha(tk->current_token[i]))
    {
      stop = 1;
    }
  }
  if (stop == 1)
  {
    return 0;
  }
  else{
    printf("Octal: %s\n",tk->current_token);
    return 1;
  }
}

int isDecimal( TokenizerT * tk)       //Checks if decimal
{
  int i = 0;
  int stop = 0;
  int Length = (strlen(tk->current_token));
  for(i = 0; i<Length; i++)
  {
    if(!isdigit(tk->current_token[i]) )
    {
      stop = 1;
    }
    if(tk->current_token[i] == '0')
    {
      stop = 1;
    }
  }
  if (stop == 1)
  {
    return 0;
  }
  else
  {
    printf("Decimal : %s\n",tk->current_token );
    return 1; // Must be true!
  }

}

int isHex( TokenizerT * tk)           //Checks if hex
{
  int i = 0;
  int stop = 0;
  int Length = (strlen(tk->current_token));
  if(tk->current_token[0] != '0' || tk->current_token[1] != 'x')
  {
    stop = 1;
  }
  for(i = 2; i<Length; i++)
  {
    if(!isxdigit(tk->current_token[i]))
    {
      stop = 1;
    }
  }
  if (stop == 1)
  {
    return 0;
  }
  else
  {
    printf("Hex : %s\n",tk->current_token );
    return 1;
  }
}

int isFloat(TokenizerT * tk)          //Checks if float
{
  int i = 0;
  int stop = 0;
  const char period = '.';
  int Length = (strlen(tk->current_token));
  if(Length < 3)
  {
    stop = 1;
  }
  if (!isdigit(tk->current_token[0]))
  {
    stop = 1;
  }
  for(i = 1; i<Length; i++)
  {
    if(tk->current_token[0] == '.')
    {
      stop = 1;
    }
    else if(tk->current_token[i] == 'x' || tk->current_token[i] == 'X')
    {
      stop =1;
    }
    else if(strchr(tk->current_token,period) == NULL)
    {
      stop = 1;
    }
  }
  if (stop == 1)
  {
    return 0;
  }
  else
  {
    printf("Float : %s\n", tk->current_token );
    return 1;
  }

}

int main(int argc, char **argv) {

  TokenizerT * tk;
  if (argc <= 1){
    printf("No arguments detected \n");
    return 0;
  }
  else
  {
    /*
    *
    * Removed the while loop. To prevent new brunswick students from stealing my code :)
    */
    char *ts = argv[1]; 
    tk = TKCreate(ts);
    TKGetNextToken(tk);
    isOCTAL(tk);
    isDecimal(tk);
    isHex(tk);
    isFloat(tk);
  }
}
