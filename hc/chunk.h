#ifndef CHUNK_H

#define CHUNK_H

#include "common.h"
#include "value.h"

typedef enum{
    OP_RETURN,
    OP_CONSTANT,
    OP_CONSTANT_LONG,
}Opcode;

typedef struct{
    int count;
    int capacity;
    uint8_t* code;
    int* lines;
    ValueArray constants;
}Chunk;

void initChunk(Chunk* chunk);
void writeChunk(Chunk* chunk,uint8_t byte,int line);
int addConstants(Chunk* chunk,Value Value);
void freeChunk(Chunk* chunk);
void writeConstant(Chunk* chunk,Value value,int line);

#endif
