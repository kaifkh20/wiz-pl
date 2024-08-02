#include "hc/common.h"
#include "hc/chunk.h"
#include "hc/debug.h"

int main(int argc, char const *argv[])
{
    Chunk chunk;
    initChunk(&chunk);
    
    // for(int i=0;i<300;++i){
    //   writeConstant(&chunk,i,i);
    writeConstant(&chunk,256,12);
    // }
    writeChunk(&chunk,OP_RETURN,12);

    disassembleChunk(&chunk,"test chunk");
    freeChunk(&chunk);
    return 0;
}
