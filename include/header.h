#include <stdio.h>
struct add_options_ptr{
    struct add_options_ptr (*fp)(char *option,char *message);
};
struct Options_Description
{
    struct add_options_ptr add_options;
};

struct add_options_ptr test(char *option,char *message)
{
    struct add_options_ptr aop;
    printf("Hello");
    return aop;
}

struct Options_Description* new_Options_Description();