#include <stdio.h>


int main(int argc, const char* argv[])
{
    printf("Starting\n");
    fseeko(stdin,0,SEEK_END);
    printf("Done\n");
};
        
