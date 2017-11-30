#ifndef IDRAWABLE_H
#define IDRAWABLE_H
#include "object.h"

// This is an example interface with two methods
typedef struct {
	void (*draw) (void* obj, int x, int y);
	void (*redraw) (void* obj, int x, int y);
} IDrawable;

IDrawable* idrawable_get_class();

#define IDRAWABLE_TYPE (void*) idrawable_get_class()
#define IS_IDRAWABLE(obj) object_get_interface(AS_OBJECT(obj), IDRAWABLE_TYPE)
#define AS_IDRAWABLE(obj) IS_IDRAWABLE(obj) ? object_get_interface((Object*) obj, IDRAWABLE_TYPE) : NULL
#define AS_IDRAWABLE_TYPE(type) ((IDrawable*) type)

#endif
