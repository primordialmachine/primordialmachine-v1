#if !defined(CC_OPTIONS_H_INCLUDED)
#define CC_OPTIONS_H_INCLUDED

#include "cc_context.h"

typedef enum cc_options_target
{

  CC_OPTIONS_TARGET_WINDOWS,

} cc_options_target;

typedef enum cc_options_mode
{

  CC_OPTIONS_MODE_BUILD,

  CC_OPTIONS_MODE_CLEAN,

} cc_options_mode;

BEGIN_DECLARE_COMPONENT(cc_options)

  cc_options_target target;

  cc_options_mode mode;

  cc_arraylist* source_files;

END_DECLARE_COMPONENT(cc_options)


/// @brief Get the target.
/// @param self Pointer to this options object.
/// @return Get the target.
cc_options_target cc_options_get_target(cc_options* self);

/// @brief Set the target.
/// @param self Pointer to this options object.
/// @param target The target.
void cc_options_set_target(cc_options* self, cc_options_target target);

/// @brief Get the mode.
/// @param self Pointer to this options object.
/// @return The mode.
cc_options_mode cc_options_get_mode(cc_options* self);

/// @brief Set the mode.
/// @param self Pointer to this options object.
/// @param mode The mode.
void cc_options_set_mode(cc_options *self, cc_options_mode mode);

cc_arraylist* cc_options_get_source_files(cc_options* self);

void cc_options_add_source_file(cc_options* self, cc_cstring* source_file);

#endif // CC_OPTIONS_H_INCLUDED
