#include "include/header.h"
#include <stdio.h>

char optionsList[][30] = {
    "help", "Print this help message"
};
options_description* new_Options_Description()
{
    options_description* obj = (options_description*)malloc(sizeof(options_description));
    obj->options = (char**)optionsList;
}