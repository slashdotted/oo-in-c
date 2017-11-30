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

#include "object.h"
#include <stdlib.h>

void* object_get_interface_impl(void * iface_type); // Prototype
void object_finalize_impl(Object * obj); // Prototype

ObjectClass*
object_get_class()
{
    static ObjectClass* class_structure = NULL;
    if (!class_structure) {
        class_structure = (ObjectClass*) malloc(sizeof(ObjectClass));
        class_structure->parent_type = NULL;
        class_structure->get_interface = object_get_interface_impl;
        class_structure->finalize = object_finalize_impl;
    }
    return class_structure;
}

void
object_init(Object* ref)
{
    SET_INSTANCE_TYPE(ref, OBJECT_TYPE);
}

void*
object_get_interface(Object* b, void * iface_type)
{
    return ((ObjectClass*) b->type)->get_interface(iface_type);
}

void*
object_get_interface_impl(void * iface_type)
{
    return NULL;
}

void
object_finalize(Object * obj)
{
    ((ObjectClass*) obj->type)->finalize(obj);
}

void
object_finalize_impl(Object * obj)
{
}

int
instance_of(void* o, void* type)
{
    if (o == NULL) return 0;
    ObjectClass* obj_type = (ObjectClass*) ((Object*) o)->type;
    do {
        if (obj_type == type) return 1;
        obj_type = (ObjectClass*) obj_type->parent_type;
    } while (obj_type);
    return 0;
}
