#include <stdio.h>
#include <stdlib.h>
#include "hc/common.h"
#include "hc/compiler.h"
#include "hc/scanner.h"

typedef struct{
  Token current;
  Token previous;
  bool hadError;
  bool panicMode;
}Parser;

typedef enum{
  PREC_NONE,
  PREC_ASSIGNMENT,  // =
  PREC_OR,          // or
  PREC_AND,         // and
  PREC_EQUALITY,    // == !=
  PREC_COMPARISON,  // < > <= >=
  PREC_TERM,        // + -
  PREC_FACTOR,      // * /
  PREC_UNARY,       // ! -
  PREC_CALL,        // . ()
  PREC_PRIMARY
}Precedence;

Chunk* compilingChunk;

static Chunk* compilingChunk(){
  return compilingChunk;
}


static void errorAt(Token* token,const char* message){
  if(parser.panicMode) return;
  parser.panicMode = true;
  fprintf(stderr,"[line %d] Error",token->line);
  if(token->type == TOKEN_EOF){
    fprintf(stderr,"at end");
  }else if(token->type == TOKEN_ERROR){
    
  }else{
    fprintf(stderr," at '%.s*'",token->length,token->start);
  }
  fprintf(stderr,": %s\n",message);
  parser.hadError = true;
}

static void error(const char* message){
  errorAt(&parser.previous,message);
}

static void errorAtCurrent(const char* message){
  errorAt(&parser.current,message);
}



static void advance(){
  parser.previous = parser.current;

  while(1){
    parser.current = scanToken();
    if(parser.current.type != TOKEN_ERROR) break;

    errorAtCurrent(parser.current.start);
 //   return !parser.hadError;
  }
}

static void consume(TokenType type,const char* message){
  if(parser.current.type == type){
    advance();
    return ;
  }
  errorAtCurrent(message);
}

static void emitByte(uint8_t byte){
  writeChunk(currentChunk(),byte,parser.previous.line);
}

static void emitBytes(uint8_t byte1,uint8_t byte2){
  emitByte(byte1);
  emitByte(byte2);
}

static inline void emitReturn(){
  emitByte(OP_RETURN);
}

static inline void endCompiler(){
  emitReturn();
}

static void expression(){
  parsePrecedence(PREC_ASSIGNMENT);
}

static void grouping(){
  expression();
  consume(TOKEN_RIGHT_PAREN,"Expect ')' after expression.");
}

static uint8_t makeConstant(Value value){
  int constant = addConstant(currentChunk(),value);
  if(constant>UINT8_MAX){
    error("Too many constants in one chunk");
    return 0;
  }
  return (uint8_t)constant;
  //int constant = writeConstant(currentChunk(),value,parser.previous.line);
  
}

static void emitConstant(Value value){
  emitBytes(OP_CONSTANT,makeConstant(value));
}

static void number(){
  double value = strtod(parser.preivous.start,NULL);
  emitConstant(value)
}

static void unary(){
  TokenType operatorType = parser.previous.type;
  parsePrecedence(PREC_UNARY);
  switch(operatorType){
    case TOKEN_MINUS: emitByte(OP_NEGATE) break;
    default return;

  }
}

static void parserPrecedence(Precedence precedence){
  
}

bool compile(const char* source,Chunk* chunk){
  initScanner(source);
  compilingChunk = chunk;
  parser.hadError = false;
  parser.panicMode = false;
  advance();
  expression();
  consume(TOKEN_EOF,"Expected end of expression.");
  endCompiler();
}
