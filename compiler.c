#include <stdio.h>
#include "hc/common.h"
#include "hc/compiler.h"
#include "hc/scanner.h"


void compile(const char* source){
  initScanner(source);
  int line = -1;
  while (1) {
    Token token = scanToken(source);
    if(token.line!=line){
      printf("%4d",line);
      line = token.line;
    }else{
      printf("   | ");
    }
    printf("%2d '%.*s'\n",token.type,token.length,token.start);
    if(token.type == TOKEN_EOF) break;
  }
}
