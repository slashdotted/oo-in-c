#ifndef DERIVED_H
#define DERIVED_H

#include "object.h"

// This is an example class derived from Object

typedef struct _DerivedPrivate DerivedPrivate;

// Instance structure
typedef struct {
    Object parent; // Parent instance structure
    double e;
    int x;
    double pi; 
    DerivedPrivate* priv; // Private structure   
} Derived;

// Class structure
typedef struct {
	ObjectClass parent; // Parent class structure
	void (*mymethod) (Derived* b, int z); // Polymorphic method
	int* counter; // Static member (MUST BE a pointer in order to be shared across all class hierarchies)
} DerivedClass;

DerivedClass* derived_get_class();

#define DERIVED_TYPE derived_get_class()
#define IS_DERIVED(obj) instance_of(AS_OBJECT(obj), DERIVED_TYPE)
#define AS_DERIVED(obj) (IS_DERIVED(obj) ? (Derived*) obj : NULL)
#define AS_DERIVED_TYPE(type) ((DerivedClass*) type)

void derived_init(Derived* ref, int x, double pi, double e, int q); // Constructor
void derived_mymethod(Derived* d, int z); // Convenience method for calling mymethod
void derived_display(Derived* d); // Non-polymorphic method
#endif

