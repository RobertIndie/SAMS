#include <malloc.h>

typedef struct Options_Description
{
    char **options;
    struct Options_Description* (*add_options)(char **, int);
}options_description;

struct Options_Description* new_Options_Description();