#ifndef __cplusplus
#define bool char
#define false 0
#define true !false
#endif

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

//loaders
int LoadExe(char *path);
int LoadDll(char *path);
int LoadDrv(char *path);

int main()
{
    bool terminate = false;

    printf("MinWin16\n");
    
    while (!terminate)
    {
        
    }

    printf("System has shut down successfully.\n");
    
    return 0;
}


