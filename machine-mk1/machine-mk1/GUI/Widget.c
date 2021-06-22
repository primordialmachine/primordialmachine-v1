/// @file GUI/Widget.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#include "./../GUI/Widget.h"


static void Machine_GUI_Widget_visit(Machine_GUI_Widget* self);

MACHINE_DEFINE_CLASSTYPE_EX(Machine_GUI_Widget, Machine_Object, &Machine_GUI_Widget_visit, &Machine_GUI_Widget_construct, NULL)

static void Machine_GUI_Widget_visit(Machine_GUI_Widget *self) {
  if (self->connections) {
    Machine_visit(self->connections);
  }
}

void Machine_GUI_Widget_construct(Machine_GUI_Widget* self, size_t numberOfArguments, const Machine_Value* arguments) {
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);
  Machine_setClassType((Machine_Object*)self, Machine_GUI_Widget_getClassType());
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Machine_GUI_Widget_render(Machine_GUI_Widget* self, float width, float height) {
  MACHINE_ASSERT_NOTNULL(self);
  MACHINE_ASSERT_NOTNULL(self->render);
  self->render(self, width, height);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Machine_GUI_Widget_setPosition(Machine_GUI_Widget* self, const Machine_Math_Vector2* position) {
  MACHINE_ASSERT_NOTNULL(self);
  MACHINE_ASSERT_NOTNULL(self->setPosition);
  MACHINE_ASSERT_NOTNULL(position);
  self->setPosition(self, position);
}

const Machine_Math_Vector2* Machine_GUI_Widget_getPosition(const Machine_GUI_Widget* self) {
  MACHINE_ASSERT_NOTNULL(self);
  MACHINE_ASSERT_NOTNULL(self->getPosition);
  return self->getPosition(self);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Machine_GUI_Widget_setSize(Machine_GUI_Widget* self, const Machine_Math_Vector2* size) {
  MACHINE_ASSERT_NOTNULL(self);
  MACHINE_ASSERT_NOTNULL(self->setSize);
  MACHINE_ASSERT_NOTNULL(size);
  self->setSize(self, size);
}

const Machine_Math_Vector2* Machine_GUI_Widget_getSize(const Machine_GUI_Widget* self) {
  MACHINE_ASSERT_NOTNULL(self);
  return self->getSize(self);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Machine_GUI_Widget_setRectangle(Machine_GUI_Widget* self, const Machine_Math_Rectangle2* rectangle) {
  MACHINE_ASSERT_NOTNULL(self);
  MACHINE_ASSERT_NOTNULL(self->setRectangle);
  MACHINE_ASSERT_NOTNULL(rectangle);
  self->setRectangle(self, rectangle);
}

const Machine_Math_Rectangle2* Machine_GUI_Widget_getRectangle(const Machine_GUI_Widget* self) {
  MACHINE_ASSERT_NOTNULL(self);
  MACHINE_ASSERT_NOTNULL(self->getRectangle);
  return self->getRectangle(self);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

const Machine_Math_Vector2* Machine_GUI_Widget_getPreferredSize(const Machine_GUI_Widget* self) {
  MACHINE_ASSERT_NOTNULL(self);
  MACHINE_ASSERT_NOTNULL(self->getPreferredSize);
  return self->getPreferredSize(self);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Machine_GUI_Widget_subscribe(Machine_GUI_Widget* self, Machine_String* name, Machine_Object* context, Machine_ForeignProcedure* callback) {
  Machine_Signals_Connection *connection = Machine_Signals_Connection_create(name, context, callback);
  if (self->connections == NULL) {
    self->connections = Machine_List_create();
  }
  Machine_Value value;
  Machine_Value_setObject(&value, (Machine_Object*)connection);
  Machine_List_append(self->connections, value);
}

void Machine_GUI_Widget_unsubscribe(Machine_GUI_Widget* self, Machine_String* name, Machine_Object* context, Machine_ForeignProcedure* callback) {
  if (self->connections) {
    for (size_t i = 0, n = Machine_Collection_getSize((Machine_Collection*)self->connections); i < n; ++i) {
      Machine_Value temporary = Machine_List_getAt(self->connections, i);
      Machine_Signals_Connection* c = (Machine_Signals_Connection*)Machine_Value_getObject(&temporary);
      if (Machine_String_isEqualTo(c->name, name) &&
          Machine_Object_isEqualTo(c->context, context) &&
          Machine_ForeignProcedure_isEqualTo(c->callback, callback)) {
        Machine_List_removeAtFast(self->connections, i);
        break;
      }
    }
  }
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Machine_GUI_Widget_emitSignal(Machine_GUI_Widget* self, Machine_String* name, size_t numberOfArguments, const Machine_Value *arguments) {
  if (self->connections) {
    for (size_t i = 0, n = Machine_Collection_getSize((Machine_Collection*)self->connections); i < n; ++i) {
      Machine_Value temporary = Machine_List_getAt(self->connections, i);
      Machine_Signals_Connection* c = (Machine_Signals_Connection*)Machine_Value_getObject(&temporary);
      if (Machine_String_isEqualTo(c->name, name)) {
        MACHINE_ASSERT_NOTNULL(c->callback);
        c->callback(numberOfArguments, arguments);
      }
    }
  }
}

