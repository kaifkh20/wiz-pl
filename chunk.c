#include <stdlib.h>
#include "hc/chunk.h"
#include "hc/memory.h"

void initChunk(Chunk* chunk){
    chunk->count = 0;
    chunk->capacity = 0;
    chunk->code = NULL;
    chunk->lines = NULL;
    initValueArray(&chunk->constants);
}

void writeChunk(Chunk* chunk,uint8_t byte,int line){
    if(chunk->capacity<chunk->count+1){
        int oldCap = chunk->capacity;
        chunk->capacity = GROW_CAPACITY(oldCap);
        chunk->code = GROW_ARRAY(uint8_t,chunk->code,oldCap,chunk->capacity);
        chunk->lines = GROW_ARRAY(int,chunk->lines,oldCap,chunk->capacity);
    }
    chunk->code[chunk->count] = byte;
    chunk->lines[chunk->count] = line;
    ++chunk->count;
}


int addConstants(Chunk* chunk,Value value){
    writeValueArray(&chunk->constants,value);
    return chunk->constants.count-1;
}

void writeConstant(Chunk* chunk,Value value,int line){
  int idxConstant = addConstants(chunk,value);
  if(idxConstant>255){
    uint8_t byte1 = idxConstant>>24 & 0xFF;
    uint8_t byte2 = idxConstant>>16 & 0xFF;
    uint8_t byte3 = idxConstant>>8 && 0xFF;

    writeChunk(chunk,OP_CONSTANT_LONG,line);
    writeChunk(chunk,byte1,line);
    writeChunk(chunk,byte2,line);
    writeChunk(chunk,byte3,line);

  }else{
    writeChunk(chunk,OP_CONSTANT,line);
    writeChunk(chunk,idxConstant,line);
  }
}

void freeChunk(Chunk* chunk){
    FREE_ARRAY(uint8_t,chunk->code,chunk->capacity);
    FREE_ARRAY(int,chunk->lines,chunk->capacity);
    freeValueArray(&chunk->constants);
    initChunk(chunk);
}
