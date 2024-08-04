#include "hc/common.h"
#include "hc/chunk.h"
#include "hc/debug.h"
#include "hc/vm.h"

int main(int argc, char const *argv[])
{
    initVM();
    Chunk chunk;
    initChunk(&chunk);
    
    // for(int i=0;i<300;++i){
    //   writeConstant(&chunk,i,i);
    writeConstant(&chunk,256,12);
    // }
    writeConstant(&chunk,259,13);

    writeChunk(&chunk,OP_ADD,13);
    // writeChunk(&chunk,OP_NEGATE,13);
    writeChunk(&chunk,OP_RETURN,13);


    disassembleChunk(&chunk,"test chunk");
    interpret(&chunk);
    freeChunk(&chunk);

    freeVM();
    return 0;
}
