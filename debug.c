#include <stdio.h>
#include "hc/debug.h"
#include "hc/value.h"


int constantInstruction(const char* name,Chunk* chunk,int offset){
    uint8_t constant = chunk->code[offset+1];
    printf("%-16s %4d",name,constant);
    printValue(chunk->constants.values[constant]);
    printf("\n");
    // one for OP_CODE and other for the operand;
    return offset+2;
}

int simpleInstruction(const char* instruction,int offset){
    printf("%s\n",instruction);
    return offset+1;
}
int disassembleInstruction(Chunk* chunk,int offset){
    printf("%04d\t",offset);
    if(offset>0 && chunk->lines[offset]==chunk->lines[offset-1]){
        printf("   | ");
    }else{
        printf("%4d ",chunk->lines[offset]);
    }
    uint8_t instruction = chunk->code[offset];
    switch(instruction){
        case OP_RETURN:
            return  simpleInstruction("OP_RETURN",offset);
        case OP_CONSTANT:
            return constantInstruction("OP_CONSTANT",chunk,offset);
        default:
            printf("Unknown Instruction \n");
            return offset+1;
    }
}

void disassembleChunk(Chunk* chunk,const char* name){
    printf("== %s ==\n",name);

    for(int offset=0;offset<chunk->count;){
        offset = disassembleInstruction(chunk,offset);
    }
}

