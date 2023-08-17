// #include "syscall.h"
#include "types.h"
#include "stat.h"
#include "user.h"



int main(int argc, char const *argv[])
{
    if(argc < 2)
    {
        printf(1, "usage: cmd command *args ...\n");
        exit();
    }

    int pid = fork();
    if(pid==0)
    {
        exec((char*)argv[1],(char**)&argv[1]);
        printf(1, "Error: No such command exists\n");
        exit();
    }
    else
    {
        // int status;
        wait();
    }
    return 0;
}
