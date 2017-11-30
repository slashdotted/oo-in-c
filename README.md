# OO in C (in 100 lines of code)

Welcome! This library provides simple OO (Object-Orientation) to the C language, all in just 100 lines (which refers to the size of *object.h* and *object.c*, a.k.a the core of this small library, ignoring comments).

## Creating a new class

Create a *myclass.h* file. This will will define the required data structures and provide public function prototypes for your class:
```C
#ifndef MYCLASS_H
#define MYCLASS_H

#include "object.h"
```
The first structure we need for our class is the *instance structure*, which will be used for each instance (object) of our class. The instance structure embeds the structure of the base class (in our case we are deriving from the root class, which is *Object*). The parent instance structure MUST BE the first member of the struct. We can define additional members which will act as instance variables:
```C
// Instance structure
typedef struct {
    Object parent; // Parent instance structure
    // instance members 
} MyClass;
```
The second structure is the *class structure*, which is shared by all instances. The class structure also embeds the parent class structure (in this case *ObjectClass*). Additional members for this structure are function pointers (for polymorphic methods) and pointers to static class members:
```C
// Class structure
typedef struct {
	ObjectClass parent; // Parent class structure
	// Polymorphic methods (function pointers)
	// Static members (MUST BE declared as pointers in order to be shared across all class hierarchies)
} MyClassClass;
```
Finally we need to define prototypes for some basic functions and some convenience macros:
```C
MyClassClass* myclass_get_class();

#define MYCLASS_TYPE myclass_get_class()
#define IS_MYCLASS(obj) instance_of(AS_OBJECT(obj), MYCLASS_TYPE)
#define AS_MYCLASS(obj) (IS_MYCLASS(obj) ? (MyClass*) obj : NULL)
#define AS_MYCLASS_TYPE(type) ((MyClassClass*) type)

void myclass_init(MyClass* ref); // Constructor

#endif
```
The constructor for our class initializes a *MyClass* instance structure and can take any additional parameter.
The implementation for our class goes into *myclass.c*:
```C
#include <stdlib.h>
#include "myclass.h"

void
myclass_init(MyClass* ref)
{
    object_init(&ref->parent); // Initialize the parent object
    SET_INSTANCE_TYPE(ref, MYCLASS_TYPE); // Set the type of the object
    // MUST BE called AFTER the parent object
    // constructor, in order to overwrite
    // the parent type

    // Initialize instance members
}
```
The constructor MUST first call the parent object constructor (in this case *object_init*), subsequently it MUST set the instance type using the *SET_INSTANCE_TYPE* macro: the first parameter is the pointer to the instance structure (*ref*) and the second parameter is the type (obtained using the *MYCLASS_TYPE* macro).
The latter is bound to the *myclass_get_class* function which is defined as follows:
```C
MyClassClass*
myclass_get_class()
{
    static MyClassClass* class_structure = NULL;
    if (!class_structure) {
        class_structure = (MyClassClass*) malloc(sizeof(MyClassClass));
        EXTENDS(class_structure, OBJECT_TYPE)
        // Override methods, declare static fields
    }
    return class_structure;
}
```

This function creates and returns a singleton instance of a *MyClassClass* structure (the *class structure*), which is used both for accessing class related stuff (such as polymorphic methods and static members) and as type identifier. After allocating memory for the class structure we NEED TO declare that our class is derived from the *Object* class using the *EXTENDS* macro: the first parameter is a pointer to the class structure, wherease the second parameter is the parent class type (*OBJECT_TYPE*). After the *EXTENDS* macro we can put additional code to override methods or declare static fields.

## Using our class

To use *MyClass* simply declare a variable of type *MyClass* and call the *constructor*:
```C
MyClass myobject;
myclass_init(&myobject);
```

## Declaring new public members and (non-polymorphic) methods

Public members are declared within the instance structure, for example:

```C
// Instance structure
typedef struct {
    Object parent; // Parent instance structure
    // instance members
    int value;
} MyClass;
```
Initialization takes place in the constructor, which can be modified in order to accept an additional parameter used to set *value*:

```C
void
myclass_init(MyClass* ref, int value)
{
    (...)
    // Initialize instance members
    ref->value = value;
}
```
We can also define two methods for getting and setting the value:
```C
// in myclass.h
int myclass_get_value(MyClass* ref);
void myclass_set_value(MyClass* ref, int value);

// in myclass.c
int
myclass_get_value(MyClass* ref)
{
	return ref->value;
}

void
myclass_set_value(MyClass* ref, int value)
{
	ref->value = value;
}
```
Those methods are not polymorphic, which means that they cannot be overridden in a derived class. Nonetheless, we can test that our code works correctly by changing the value in the example code:
```C
printf("value is %d\n", myclass_get_value(&myobject));
myclass_set_value(&myobject, 33);
printf("value is %d\n", myclass_get_value(&myobject));
```

## Going further

In *derived.h* and *derived.c* you find an example of a class which extends *Object* and shows you how to implement *private* members and how to implement/override *polymorphic* methods. Moreover, *doublederived.h*, *doublederived.c*, *idrawable.h* and *idrawable.c* provide an example on how to extend *Derived* and declare/implement and interface. Finally, in *main.c* you will find an example of usage of all these classes (and of some convenience macro).

## License

The code of the library (found in *object.h* and *object.c*) is released under a BSD 3-clause license (see *LICENSE* for details). Examples (derived.c, derived.h, doublederived.c, doublederived.h, idrawable.c, idrawable.h, main.c) are public domain.

## Comments? Questions? Bugs?

If you have any comment, question or if you found a bug in the code please don't hesitate to contact me at amos _DOT_GOES_HERE_ brocco _AT_GOES_HERE_ supsi _DOT_GOES_HERE_ ch . Thank you!
