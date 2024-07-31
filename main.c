#include "hc/common.h"
#include "hc/chunk.h"
#include "hc/debug.h"

int main(int argc, char const *argv[])
{
    Chunk chunk;
    initChunk(&chunk);
    
    int constant = addConstants(&chunk,1.2);
    
    writeChunk(&chunk,OP_CONSTANT,12);
    
    writeChunk(&chunk,constant,12);

    writeChunk(&chunk,OP_RETURN,12);

    disassembleChunk(&chunk,"test chunk");
    freeChunk(&chunk);
    return 0;
}
