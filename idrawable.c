#include <stdlib.h>
#include "idrawable.h"

IDrawable*
idrawable_get_class()
{
    static IDrawable* class_structure = NULL;
    if (!class_structure) {
        class_structure = (IDrawable*) malloc(sizeof(IDrawable));
    }
    return class_structure;
}
