#include <stdio.h>
#include "include/header.h"

int main(int argc,char *argv[])
{
    options_description* od = new_Options_Description();
    od->add_options();
    for(int i = 0;i<argc;i++)
    {
        printf("%s\n",argv[i]);
    }
}