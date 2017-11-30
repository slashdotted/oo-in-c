#include <stdio.h>
#include "doublederived.h"

int
main(void)
{
    Object b;
    object_init(&b);

    Derived d;
    derived_init(&d, 42, 3.14, 2.6, 44);
    derived_display(&d);

    DoubleDerived dd;
    doublederived_init(&dd, 42, 3.14, 2.6, 56, 13);
    doublederived_display(&dd);
    derived_display((Derived*) &d);

    derived_mymethod((Derived*) &d, 6);
    derived_mymethod((Derived*) &dd, 6);

    *DERIVED_TYPE->counter = 42;
    printf("Derived counter %d \n", *DERIVED_TYPE->counter);
    *DERIVED_TYPE->counter = 77;
    printf("Derived counter %d \n", *DERIVED_TYPE->counter);
    *AS_DERIVED_TYPE(PARENT_TYPE(DOUBLEDERIVED_TYPE))->counter = 42;
    printf("Derived counter %d \n", *DERIVED_TYPE->counter);

    derived_display((Derived*) &dd);
    derived_display((Derived*) &d);

    if (IS_OBJECT(&b)) {
        printf("b instance_of Object\n");
    }

    if (IS_DERIVED(&b)) {
        printf("b instance_of Derived\n");
    }

    if (IS_DOUBLEDERIVED(&b)) {
        printf("b instance_of DoubleDerived\n");
    }

    if (IS_OBJECT(&d)) {
        printf("d instance_of Object\n");
    }

    if (IS_DERIVED(&d)) {
        printf("d instance_of Derived\n");
    }

    if (IS_DOUBLEDERIVED(&d)) {
        printf("d instance_of DoubleDerived\n");
    }

    if (IS_OBJECT(&dd)) {
        printf("dd instance_of Object\n");
    }

    if (IS_DERIVED(&dd)) {
        printf("dd instance_of Derived\n");
    }

    if (IS_DOUBLEDERIVED(&dd)) {
        printf("dd instance_of DoubleDerived\n");
    }

    if (IS_IDRAWABLE(&b)) {
        printf("b implements IDrawable\n");
    }

    if (IS_IDRAWABLE(&d)) {
        printf("d implements IDrawable\n");
    }

    if (IS_IDRAWABLE(&dd)) {
        printf("dd implements IDrawable\n");
    }


    IDrawable* i = AS_IDRAWABLE(&dd);
    if (i) {
        i->draw(&dd, 10, 20);
    }

    printf("Finalizing Base object...\n");
    object_finalize(AS_OBJECT(&b));
    printf("Finalizing Derived object...\n");
    object_finalize(AS_OBJECT(&d));
    printf("Finalizing DoubleDerived object...\n");
    object_finalize(AS_OBJECT(&dd));

    return 0;
}
