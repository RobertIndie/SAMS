#include <stdio.h>
#include "include/header.h"

int main(int argc,char *argv[])
{
    struct Options_Description d;
    d.add_options.fp = test;
    d.add_options.fp("h","h").fp("h","h");
    for(int i = 0;i<argc;i++)
    {
        printf("%s\n",argv[i]);
    }
}