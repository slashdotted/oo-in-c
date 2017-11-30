#include "doublederived.h"
#include <stdio.h>
#include <stdlib.h>

// Prototypes
void* doublederived_get_interface_impl(void * iface_type);
void doublederived_mymethod_impl(Derived* b, int z);
void doublederived_draw_impl (void* obj, int x, int y);
void doublederived_draw_impl (void* obj, int x, int y);
void doublederived_finalize_impl(Object * obj);

void doublederived_draw_impl (void* obj, int x, int y)
{
    printf("doublederived draw %d,%d\n", x, y);
}

void doublederived_redraw_impl (void* obj, int x, int y)
{
    printf("doublederived redraw %d,%d\n", x, y);
}

void
doublederived_display(DoubleDerived* dd)
{
    printf("k=%d\n", dd->k);
    //printf("e = %3.2f, pi = %3.2f, x = %d\n", dd->parent.e, dd->parent.pi, dd->parent.x);
    derived_display(&dd->parent);
}

void
doublederived_init(DoubleDerived* ref, int x, double pi, double e, int q, int k)
{
    derived_init(&ref->parent, x, pi, e, q);
    SET_INSTANCE_TYPE(ref, DOUBLEDERIVED_TYPE);
    ref->k= k;
}

DoubleDerivedClass*
doublederived_get_class()
{
    static DoubleDerivedClass* class_structure = NULL;
    if (!class_structure) {
        class_structure = (DoubleDerivedClass*) malloc(sizeof(DoubleDerivedClass));
        EXTENDS(class_structure, DERIVED_TYPE)
        DECLARE_INTERFACE_DISPATCHER_OVERRIDE(class_structure, doublederived_get_interface_impl)

        // Override methods, declare static fields
        DECLARE_METHOD_OVERRIDE(AS_OBJECT_TYPE(class_structure), finalize, doublederived_finalize_impl)
        DECLARE_METHOD_OVERRIDE(AS_DERIVED_TYPE(class_structure), mymethod, doublederived_mymethod_impl)
        DECLARE_METHOD_OVERRIDE(AS_IDRAWABLE_TYPE(&class_structure->drawable), draw, doublederived_draw_impl)
        DECLARE_METHOD_OVERRIDE(AS_IDRAWABLE_TYPE(&class_structure->drawable), redraw, doublederived_redraw_impl)
    }
    return class_structure;
}

void
doublederived_mymethod_impl(Derived* d, int z)
{
    printf("doublederived_mymethod_impl called with z=%d\n", z);
}

void
doublederived_finalize_impl(Object * obj)
{
    printf("Finalizing DoubleDerived object\n");
    AS_OBJECT_TYPE(DERIVED_TYPE)->finalize(obj); // Chain
}

void*
doublederived_get_interface_impl(void * iface_type)
{
    if (iface_type == IDRAWABLE_TYPE) {
        return &doublederived_get_class()->drawable;
    }
    // Chain
    return AS_OBJECT_TYPE(PARENT_TYPE(DOUBLEDERIVED_TYPE))->get_interface(iface_type);
}

