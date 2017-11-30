#ifndef DOUBLEDERIVED_H
#define DOUBLEDERIVED_H

#include "derived.h"
#include "idrawable.h"

// This is an example class derived from Derived

typedef struct {
    Derived parent; // Parent instance structure
    int k;
} DoubleDerived;

typedef struct {
	DerivedClass parent; // Parent class structure
	IDrawable drawable; // Interface structure
} DoubleDerivedClass;

DoubleDerivedClass* doublederived_get_class();

#define DOUBLEDERIVED_TYPE doublederived_get_class()
#define IS_DOUBLEDERIVED(obj) instance_of(AS_OBJECT(obj), DOUBLEDERIVED_TYPE)
#define AS_DOUBLEDERIVED(obj) (IS_DOUBLEDERIVED(obj) ? (DoubleDerived*) obj : NULL)
#define AS_DOUBLEDERIVED_TYPE(type) ((DoubleDerivedClass*) type)

void doublederived_init(DoubleDerived* ref, int x, double pi, double e, int q, int k); // Constructor
void doublederived_display(DoubleDerived* dd); // Non-polymorphic method
#endif
