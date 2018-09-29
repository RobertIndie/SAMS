#include <malloc.h>

typedef struct Options_Description
{
    char **options;
}options_description;

struct Options_Description* new_Options_Description();