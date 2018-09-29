#include "include/header.h"
#include <stdio.h>

options_description* add_options(options_description *this, char **options,int len)
{
    this->options = options;
}

options_description* new_Options_Description()
{
    options_description* obj = (options_description*)malloc(sizeof(options_description));
    obj->options = NULL;
    obj->add_options = add_options;
}