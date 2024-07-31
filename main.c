#include "hc/common.h"
#include "hc/chunk.h"
#include "hc/debug.h"

int main(int argc, char const *argv[])
{
    Chunk chunk;
    initChunk(&chunk);
    writeChunk(&chunk,OP_RETURN);
    disassembleChunk(&chunk,"test chunk");
    freeChunk(&chunk);
    return 0;
}
