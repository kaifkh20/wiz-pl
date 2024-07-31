#include <stdio.h>
#include "hc/debug.h"

int simpleInstruction(const char* instruction,int offset){
    printf("%s\n",instruction);
    return offset+1;
}
int disassembleInstruction(Chunk* chunk,int offset){
    printf("%04d\t",offset);
    uint8_t instruction = chunk->code[offset];
    switch(instruction){
        case OP_RETURN:
            return  simpleInstruction("OP_RETURN",offset);
        default:
            printf("Unknown Instruction \n");
            return offset+1;
    }
}

void disassembleChunk(Chunk* chunk,const char* name){
    printf("== %s ==\n",name);

    for(int offset=0;offset<chunk->count;offset++){
        offset = disassembleInstruction(chunk,offset);
    }
}

