/// @file Gui/Reader/Reader.package.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_GUI_READER_PACKAGE_H_INCLUDED)
#define MACHINE_GUI_READER_PACKAGE_H_INCLUDED



#include "Gui/Border.h"
#include "Gui/Group.h"
#include "Gui/TextButton.h"
#include "Gui/TextLabel.h"



/// @brief
/// <code>
/// group :
///   "to be done"
/// </code>
/// @param self A pointer to this GUI context.
/// @param source A pointer to the source map.
/// @return A pointer to the widget.
/// @todo Restruct visibility to "package".
Machine_Gui_Group* Machine_GUI_Reader_readGroup(Machine_Gui_Context* self, Machine_Map const* source);

/// @brief
/// <code>
/// border :
///   kind = 'Border'
///   borderWidth = <non-negative real>, optional, default : 0
///   (top|bottom|left|right)BorderWidth = <non-negative-real>, optional, default: 0
///   borderColor = <rgba color>, optional, default : [0.1, 0.1, 0.1, 1.0]
///   child = <widget>, optional, default : void
/// </code>
/// @param self A pointer to this GUI context.
/// @param source A pointer to the source map.
/// @return A pointer to the widget.
/// @todo Restruct visibility to "package".
Machine_Gui_Border* Machine_GUI_Reader_readBorder(Machine_Gui_Context* self, Machine_Map const* source);

/// @brief
/// <code>
/// textButton :
///   "to be done"
/// </code>
/// @param self A pointer to this GUI context.
/// @param source A pointer to the source map.
/// @return A pointer to the widget.
/// @todo Restrict visibility to "package".
Machine_Gui_TextButton* Machine_GUI_Reader_readTextButton(Machine_Gui_Context* self, Machine_Map const* source);

/// @brief 
/// <code>
/// textLabel :
///   "to be done"
/// </code>
/// @param self A pointer to this GUI context.
/// @param source A pointer to the source map.
/// @return A pointer to the widget.
/// @todo Restruct visibility to "package".
Machine_Gui_TextLabel* Machine_GUI_Reader_readTextLabel(Machine_Gui_Context* self, Machine_Map const* source);

/// @brief
/// <code>
/// layout :
///   "to be done"
/// </code>
/// @param self A pointer to this GUI context.
/// @param source A pointer to the source map.
/// @return A pointer to the layout model.
Machine_GUI_LayoutModel* Machine_GUI_Reader_readLayout(Machine_Gui_Context* self, Machine_Map const* source);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief Get if a key of the specified name exists in the specified map and refers to a value of type <code>String</code>.
/// @param self The GUI context.
/// @param map The map.
/// @param key The key.
/// @return @a true if such a key/value pair exists, @a false otherwise.
static inline bool Machine_GUI_Reader_hasString(Machine_Gui_Context* self, Machine_Map const* map, Machine_String const* key) {
  Machine_Value keyValue;
  Machine_Value_setString(&keyValue, key);
  Machine_Value valueValue = Machine_Map_get(map, keyValue);
  return Machine_Value_isString(&valueValue);
}

// USED
static inline Machine_String* Machine_GUI_Reader_getString(Machine_Map const* map, Machine_String const* key) {
  Machine_Value keyValue;
  Machine_Value_setString(&keyValue, key);
  Machine_Value valueValue = Machine_Map_get(map, keyValue);
  if (!Machine_Value_isString(&valueValue)) {
    Machine_setStatus(Machine_Status_ConversionFailed);
    Machine_jump();
  }
  return Machine_Value_getString(&valueValue);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief Get if a key of the specified name exists in the specified map and refers to a value of type <code>Integer</code> or <code>Real</code>.
/// @param self The GUI context.
/// @param map The map.
/// @param key The key.
/// @return @a true if such a key/value pair exists, @a false otherwise.
static inline bool Machine_GUI_Reader_hasReal(Machine_Gui_Context* self, Machine_Map const* map, Machine_String const* key) {
  Machine_Value keyValue;
  Machine_Value_setString(&keyValue, key);
  Machine_Value valueValue = Machine_Map_get(map, keyValue);
  return Machine_Value_isInteger(&valueValue) || Machine_Value_isReal(&valueValue);
}

// USED
static inline Machine_Real Machine_GUI_Reader_getReal(Machine_Map const* map, Machine_String const* key) {
  Machine_Value keyValue;
  Machine_Value_setString(&keyValue, key);
  Machine_Value valueValue = Machine_Map_get(map, keyValue);
  if (!Machine_Value_isInteger(&valueValue) && !Machine_Value_isReal(&valueValue)) {
    Machine_setStatus(Machine_Status_ConversionFailed);
    Machine_jump();
  }
  if (Machine_Value_isInteger(&valueValue)) {
    return (Machine_Real)Machine_Value_getInteger(&valueValue);
  }
  else {
    return Machine_Value_getReal(&valueValue);
  }
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief Get if a key of the specified name exists in the specified map and refers to a value of type <code>Object</code> or derived type.
/// @param self The GUI context.
/// @param map The map.
/// @param key The key.
/// @return @a true if such a key/value pair exists, @a false otherwise.
static inline bool Machine_GUI_Reader_hasObject(Machine_Gui_Context* self, Machine_Map const* map, Machine_String const* key) {
  Machine_Value keyValue;
  Machine_Value_setString(&keyValue, key);
  Machine_Value valueValue = Machine_Map_get(map, keyValue);
  return Machine_Value_isObject(&valueValue);
}

// USED
static inline Machine_Object* Machine_GUI_Reader_getObject(Machine_Map const* map, Machine_String const* key) {
  Machine_Value keyValue;
  Machine_Value_setString(&keyValue, key);
  Machine_Value valueValue = Machine_Map_get(map, keyValue);
  if (!Machine_Value_isObject(&valueValue)) {
    Machine_setStatus(Machine_Status_ConversionFailed);
    Machine_jump();
  }
  return Machine_Value_getObject(&valueValue);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static inline Machine_Value getMapOrVoid(Machine_Gui_Context* self, Machine_Map const* map, Machine_String const* key) {
  Machine_Value keyValue;
  Machine_Value_setString(&keyValue, key);
  Machine_Value valueValue = Machine_Map_get(map, keyValue);
  if (!Machine_Value_isObject(&valueValue)) {
    return valueValue;
  }
  Machine_Object* object = Machine_Value_getObject(&valueValue);
  if (!Machine_isSubTypeOf(Machine_getClassType(object), Machine_Map_getClassType())) {
    Machine_Value_setVoid(&valueValue, Machine_Void_Void);
  }
  return valueValue;
}

static inline bool Machine_GUI_Reader_hasMap(Machine_Gui_Context* self, Machine_Map const* map, Machine_String const* key) {
  Machine_Value v = getMapOrVoid(self, map, key);
  return !Machine_Value_isVoid(&v);
}

static inline Machine_Map* Machine_GUI_Reader_getMap(Machine_Gui_Context* self, Machine_Map const* map, Machine_String const* key) {
  Machine_Value v = getMapOrVoid(self, map, key);
  if (Machine_Value_isVoid(&v)) {
    Machine_setStatus(Machine_Status_SemanticalError);
    Machine_jump();
  }
  return (Machine_Map*)Machine_Value_getObject(&v);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static inline Machine_Value getListOrVoid(Machine_Gui_Context* self, Machine_Map const* map, Machine_String const* key) {
  Machine_Value keyValue;
  Machine_Value_setString(&keyValue, key);
  Machine_Value valueValue = Machine_Map_get(map, keyValue);
  if (!Machine_Value_isObject(&valueValue)) {
    return valueValue;
  }
  Machine_Object* object = Machine_Value_getObject(&valueValue);
  if (!Machine_isSubTypeOf(Machine_getClassType(object), Machine_List_getClassType())) {
    Machine_Value_setVoid(&valueValue, Machine_Void_Void);
  }
  return valueValue;
}

static inline bool Machine_GUI_Reader_hasList(Machine_Gui_Context* self, Machine_Map const* map, Machine_String const* key) {
  Machine_Value v = getListOrVoid(self, map, key);
  return !Machine_Value_isVoid(&v);
}

static inline Machine_List* Machine_GUI_Reader_getList(Machine_Gui_Context* self, Machine_Map const* map, Machine_String const* key) {
  Machine_Value v = getListOrVoid(self, map, key);
  if (Machine_Value_isVoid(&v)) {
    Machine_setStatus(Machine_Status_SemanticalError);
    Machine_jump();
  }
  return (Machine_List*)Machine_Value_getObject(&v);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#endif // MACHINE_GUI_READER_PACKAGE_H_INCLUDED
