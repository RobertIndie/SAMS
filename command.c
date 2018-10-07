#include "include/header.h"

void ParseCommand(int argc,char **argv)
{
    char help_formatter[] = \
    "This Student-Achievement-Management-System is open source under GPLv2.0.\n\
Author: AaronRobert \
    ";

    printf("%s",help_formatter);
}

CommandRunner* new_CommandRunner()
{
    CommandRunner* product = (CommandRunner*)malloc(sizeof(CommandRunner));
    return product;
}
