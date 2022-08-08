/// @file Gui/Reader/Reader.package.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_GUI_READER_PACKAGE_H_INCLUDED)
#define MACHINE_GUI_READER_PACKAGE_H_INCLUDED

#if !defined(MACHINE_GUI_PRIVATE)
#error("Do not include `Gui/Reader/Reader.package.h` directly, include `_Gui.h` instead.")
#endif
#include "Gui/BorderNode.h"
#include "Gui/GroupNode.h"
#include "Gui/TextNode.h"

/// @brief
/// <code>
/// group :
///   kind = "Group", required
///   ...
/// </code>
/// @param self A pointer to this GUI context.
/// @param source A pointer to the source map.
/// @return A pointer to the widget.
Machine_Gui_GroupNode* Machine_Gui_Reader_readGroupNode(Machine_Gui_Context* self,
                                                        Machine_Map const* source);

/// @brief
/// <code>
/// border :
///   kind = 'Border', required
///   borderWidth = <non-negative real>, optional, default : 0
///   (top|bottom|left|right)BorderWidth = <non-negative-real>, optional, default: 0
///   borderColor = <rgba color>, optional, default : [0.1, 0.1, 0.1, 1.0]
///   child = <widget>, optional, default : void
/// </code>
/// @param self A pointer to this GUI context.
/// @param source A pointer to the source map.
/// @return A pointer to the widget.
Machine_Gui_BorderNode* Machine_Gui_Reader_readBorderNode(Machine_Gui_Context* self,
                                                          Machine_Map const* source);

/// @brief
/// <code>
/// text :
///   kind = "Text", required
///   ...
/// </code>
/// @param self A pointer to this GUI context.
/// @param source A pointer to the source map.
/// @return A pointer to the widget.
Machine_Gui_TextNode* Machine_Gui_Reader_readTextNode(Machine_Gui_Context* self,
                                                      Machine_Map const* source);

/// @brief
/// <code>
/// layout :
///   "to be done"
/// </code>
/// @param self A pointer to this GUI context.
/// @param source A pointer to the source map.
/// @return A pointer to the layout model.
Machine_Gui_LayoutModel* Machine_Gui_Reader_readLayout(Machine_Gui_Context* self,
                                                       Machine_Map const* source);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief Get if a key of the specified name exists in the specified map and refers to a value of
/// type <code>String</code>.
/// @param self The GUI context.
/// @param map The map.
/// @param key The key.
/// @return @a true if such a key/value pair exists, @a false otherwise.
static inline bool Machine_Gui_Reader_hasString(Machine_Gui_Context* self, Machine_Map const* map,
                                                Ring2_String const* key) {
  Machine_Value keyValue;
  Machine_Value_setString(&keyValue, key);
  Machine_Value valueValue = Machine_Map_get(map, keyValue);
  return Machine_Value_isString(&valueValue);
}

// USED
static inline Ring2_String* Machine_Gui_Reader_getString(Machine_Map const* map,
                                                         Ring2_String const* key) {
  Machine_Value keyValue;
  Machine_Value_setString(&keyValue, key);
  Machine_Value valueValue = Machine_Map_get(map, keyValue);
  if (!Machine_Value_isString(&valueValue)) {
    Ring1_Status_set(Ring1_Status_ConversionFailed);
    Ring2_jump();
  }
  return Machine_Value_getString(&valueValue);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief Get if a key of the specified name exists in the specified map and refers to a value of
/// type <code>Integer</code> or <code>Real</code>.
/// @param self The GUI context.
/// @param map The map.
/// @param key The key.
/// @return @a true if such a key/value pair exists, @a false otherwise.
static inline bool Machine_Gui_Reader_hasReal(Machine_Gui_Context* self, Machine_Map const* map,
                                              Ring2_String const* key) {
  Machine_Value keyValue;
  Machine_Value_setString(&keyValue, key);
  Machine_Value valueValue = Machine_Map_get(map, keyValue);
  return Machine_Value_isInteger(&valueValue) || Machine_Value_isReal32(&valueValue);
}

// USED
static inline Ring2_Real32 Machine_Gui_Reader_getReal(Machine_Map const* map,
                                                      Ring2_String const* key) {
  Machine_Value keyValue;
  Machine_Value_setString(&keyValue, key);
  Machine_Value valueValue = Machine_Map_get(map, keyValue);
  if (!Machine_Value_isInteger(&valueValue) && !Machine_Value_isReal32(&valueValue)) {
    Ring1_Status_set(Ring1_Status_ConversionFailed);
    Ring2_jump();
  }
  if (Machine_Value_isInteger(&valueValue)) {
    return (Ring2_Real32)Machine_Value_getInteger(&valueValue);
  } else {
    return Machine_Value_getReal32(&valueValue);
  }
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief Get if a key of the specified name exists in the specified map and refers to a value of
/// type <code>Object</code> or derived type.
/// @param self The GUI context.
/// @param map The map.
/// @param key The key.
/// @return @a true if such a key/value pair exists, @a false otherwise.
static inline bool Machine_Gui_Reader_hasObject(Machine_Gui_Context* self, Machine_Map const* map,
                                                Ring2_String const* key) {
  Machine_Value keyValue;
  Machine_Value_setString(&keyValue, key);
  Machine_Value valueValue = Machine_Map_get(map, keyValue);
  return Machine_Value_isObject(&valueValue);
}

// USED
static inline Machine_Object* Machine_Gui_Reader_getObject(Machine_Map const* map,
                                                           Ring2_String const* key) {
  Machine_Value keyValue;
  Machine_Value_setString(&keyValue, key);
  Machine_Value valueValue = Machine_Map_get(map, keyValue);
  if (!Machine_Value_isObject(&valueValue)) {
    Ring1_Status_set(Ring1_Status_ConversionFailed);
    Ring2_jump();
  }
  return Machine_Value_getObject(&valueValue);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static inline Machine_Value getMapOrVoid(Machine_Gui_Context* self, Machine_Map const* map,
                                         Ring2_String const* key) {
  Machine_Value keyValue;
  Machine_Value_setString(&keyValue, key);
  Machine_Value valueValue = Machine_Map_get(map, keyValue);
  if (!Machine_Value_isObject(&valueValue)) {
    return valueValue;
  }
  Machine_Object* object = Machine_Value_getObject(&valueValue);
  if (!Machine_Type_isSubTypeOf((Machine_Type *)Machine_getClassType(object), (Machine_Type *)Machine_Map_getType())) {
    Machine_Value_setVoid(&valueValue, Ring2_Void_Void);
  }
  return valueValue;
}

static inline bool Machine_Gui_Reader_hasMap(Machine_Gui_Context* self, Machine_Map const* map,
                                             Ring2_String const* key) {
  Machine_Value v = getMapOrVoid(self, map, key);
  return !Machine_Value_isVoid(&v);
}

static inline Machine_Map* Machine_Gui_Reader_getMap(Machine_Gui_Context* self,
                                                     Machine_Map const* map,
                                                     Ring2_String const* key) {
  Machine_Value v = getMapOrVoid(self, map, key);
  if (Machine_Value_isVoid(&v)) {
    Ring1_Status_set(Ring1_Status_InvalidSemantics);
    Ring2_jump();
  }
  return (Machine_Map*)Machine_Value_getObject(&v);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static inline Machine_Value getListOrVoid(Machine_Gui_Context* self, Machine_Map const* map,
                                          Ring2_String const* key) {
  Machine_Value keyValue;
  Machine_Value_setString(&keyValue, key);
  Machine_Value valueValue = Machine_Map_get(map, keyValue);
  if (!Machine_Value_isObject(&valueValue)) {
    return valueValue;
  }
  Machine_Object* object = Machine_Value_getObject(&valueValue);
  if (!Machine_Type_isSubTypeOf((Machine_Type *)Machine_getClassType(object), (Machine_Type *)Machine_List_getType())) {
    Machine_Value_setVoid(&valueValue, Ring2_Void_Void);
  }
  return valueValue;
}

static inline bool Machine_Gui_Reader_hasList(Machine_Gui_Context* self, Machine_Map const* map,
                                              Ring2_String const* key) {
  Machine_Value v = getListOrVoid(self, map, key);
  return !Machine_Value_isVoid(&v);
}

static inline Machine_List* Machine_Gui_Reader_getList(Machine_Gui_Context* self,
                                                       Machine_Map const* map,
                                                       Ring2_String const* key) {
  Machine_Value v = getListOrVoid(self, map, key);
  if (Machine_Value_isVoid(&v)) {
    Ring1_Status_set(Ring1_Status_InvalidSemantics);
    Ring2_jump();
  }
  return (Machine_List*)Machine_Value_getObject(&v);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#endif // MACHINE_GUI_READER_PACKAGE_H_INCLUDED
