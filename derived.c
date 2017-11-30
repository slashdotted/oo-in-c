#include "derived.h"
#include <stdio.h>
#include <stdlib.h>

// Prototypes
void derived_mymethod_impl(Derived* d, int z);
void derived_finalize_impl(Object * obj);

struct _DerivedPrivate {
    int q;
};

void
derived_init(Derived* ref, int x, double pi, double e, int q)
{
    object_init(&ref->parent); // Initialize the parent object
    SET_INSTANCE_TYPE(ref, DERIVED_TYPE); // Set the type of the object
    // MUST BE called AFTER the parent object
    // constructor, in order to overwrite
    // the parent type

    // Initialize instance members
    ref->priv = (DerivedPrivate*) malloc(sizeof(DerivedPrivate));
    ref->e = e;
    ref->pi = pi;
    ref->x = x;
    ref->priv->q = q;
}

DerivedClass*
derived_get_class()
{
    static DerivedClass* class_structure = NULL;
    if (!class_structure) {
        class_structure = (DerivedClass*) malloc(sizeof(DerivedClass));
        EXTENDS(class_structure, OBJECT_TYPE)
        // Override methods, declare static fields
        DECLARE_METHOD_OVERRIDE(AS_DERIVED_TYPE(class_structure), mymethod, derived_mymethod_impl)
        DECLARE_METHOD_OVERRIDE(AS_OBJECT_TYPE(class_structure), finalize, derived_finalize_impl)
        DECLARE_STATIC_MEMBER(class_structure, int, counter, 0)
    }
    return class_structure;
}

void
derived_display(Derived* d)
{
    printf("e=%3.2f, pi=%3.2f, x=%d, q=%d\n", d->e, d->pi, d->x, d->priv->q);
}

void
derived_mymethod_impl(Derived* b, int z)
{
    printf("derived_mymethod_impl called with z=%d\n", z);
}

void
derived_finalize_impl(Object * obj)
{
    printf("Finalizing Derived object\n");
    free(AS_DERIVED(obj)->priv);
    OBJECT_TYPE->finalize(obj); // Chain
}

void
derived_mymethod(Derived* d, int z)
{
    AS_DERIVED_TYPE(GET_INSTANCE_TYPE(d))->mymethod(d,z);
}
