/*
 * Copyright (C)2016-2017      Amos Brocco (amos.brocco@supsi.ch)
 *                             Scuola Universitaria Professionale della
 *                             Svizzera Italiana (SUPSI)
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the Scuola Universitaria Professionale della Svizzera
 *       Italiana (SUPSI) nor the names of its contributors may be used
 *       to endorse or promote products derived from this software without
 *       specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef OBJECT_H
#define OBJECT_H

typedef struct Object {
	void* type; // Type reference
} Object;

typedef struct {
	void* parent_type;
	void* (* get_interface) (void* iface_type);
	void (* finalize) (Object* obj);
} ObjectClass;

ObjectClass* object_get_class();
void* object_get_interface(Object* b, void * iface_type);
void object_finalize(Object * obj);
int instance_of(void* o, void* type);

void object_init(Object* ref); // Constructor

#define OBJECT_TYPE object_get_class()
#define IS_OBJECT(obj) instance_of(obj, OBJECT_TYPE)
#define AS_OBJECT(obj) (IS_OBJECT(obj) ? (Object*) obj : NULL)
#define AS_OBJECT_TYPE(type) ((ObjectClass*) type)

// Convenience macros
#define SET_INSTANCE_TYPE(obj, thetype) ((Object*) obj)->type = thetype;
#define GET_INSTANCE_TYPE(obj) \
		(IS_OBJECT(obj) ? AS_OBJECT(obj)->type : (ObjectClass*) NULL)
#define PARENT_TYPE(thetype) (AS_OBJECT_TYPE(thetype))->parent_type
#define EXTENDS(class_structure, thetype) \
		class_structure->parent = *thetype; \
		PARENT_TYPE(class_structure) = thetype;	
#define DECLARE_STATIC_MEMBER(type_struct, mtype, name, value) \
		{ static mtype name = value; type_struct->name = &(name); }	
#define DECLARE_INTERFACE_DISPATCHER_OVERRIDE(type_struct, dispatcher) \
		((ObjectClass*) type_struct)->get_interface = dispatcher;
#define DECLARE_METHOD_OVERRIDE(type_struct, method, theoverride) \
		type_struct->method = theoverride;		

#endif
