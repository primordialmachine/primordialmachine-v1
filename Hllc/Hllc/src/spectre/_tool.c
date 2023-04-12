#include "spectre/_tool.h"

#include "spectre/cc_parser.h"
#include "spectre/cc_enter.h"
#include "spectre/cc_resolve.h"
#include "spectre/cc_emit.h"
#include "spectre/cc_options.h"
#include "cc_os_lib.h"
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

static void cc_ctx_add_source_file(cc_ctx* ctx, cc_program_tree* program, cc_cstring* file_path)
{
  cc_parser* parser = cc_parser_get_instance(ctx);
  cc_parser_set_input(parser, file_path);
  if (!cc_parser_run(parser, program))
  { cc_error(CC_EINVAL); }
}

#include "Ring1/All/_Include.h"
static void
find_hll_files
  (
    cc_ctx* ctx,
    cc_cstring *path,
    cc_arraylist *files
  )
{
  WIN32_FIND_DATAA find_data;
  if (cc_cstring_ends_with(path, cc_cstring_create("/")) || cc_cstring_ends_with(path, cc_cstring_create("\\"))) {
    cc_error(CC_EINVAL);
  }

  SetLastError(0);

  cc_cstring *search_exp = cc_cstring_concatenate(path, cc_cstring_create("/*"));
  HANDLE find = FindFirstFileA(search_exp->p, &find_data);
  if (find == INVALID_HANDLE_VALUE) {
    DWORD last_error = GetLastError();
    if (last_error != 0) {
      if (GetLastError() == ERROR_NO_MORE_FILES) {
        return;
      } else {
        cc_error(CC_EINVAL);
      }
    } else {
      // Invalid environment.
      cc_error(CC_EINVAL);
    }
  }

  cc_jt jt;
  cc_push_jt(&jt);
  if (!setjmp(jt.env)) {
    while (1) {
      if (!FindNextFileA(find, &find_data)) {
        DWORD last_error = GetLastError();
        if (last_error != 0) {
          if (GetLastError() == ERROR_NO_MORE_FILES) {
            break;
          } else {
            cc_error(CC_EINVAL);
          }
        }
      }
    }
    cc_pop_jt();
    FindClose(find);
    find = 0;
  } else {
    cc_pop_jt();
    FindClose(find);
    find = 0;
    cc_j();
  }
}

static void run(cc_tool *self, cc_arraylist* args)
{
  cc_ctx* ctx = cc_ctx_create();
  cc_options* options = cc_options_get_instance(ctx);
  cc_cstring* BUILD = cc_cstring_create("--build");
  cc_cstring* CLEAN = cc_cstring_create("--clean");
  cc_options_set_mode(options, CC_OPTIONS_MODE_BUILD);
  for (size_t i = 0, n = cc_arraylist_get_size(args); i < n; ++i)
  {
    cc_cstring* argument = (cc_cstring*)cc_arraylist_get_at(args, i);
    if (cc_cstring_equal(argument, BUILD))
    {
      cc_options_set_mode(options, CC_OPTIONS_MODE_BUILD);
    }
    else if (cc_cstring_equal(argument, CLEAN))
    {
      cc_options_set_mode(options, CC_OPTIONS_MODE_CLEAN);
    }
  }
#define FILE(PATH) cc_options_add_source_file(options, cc_cstring_create(PATH))
  FILE("./Ring3.Visuals/sources/Ring3/BlendFunction.hll");
  FILE("./Ring3.Visuals/sources/Ring3/DepthTestFunction.hll");
  FILE("./Ring3.Visuals/sources/Ring3/PixelFormat.hll");
  FILE("./Ring3.Visuals/sources/Ring3/VertexElementSemantics.hll");
  FILE("./Ring3.Visuals/sources/Ring3/Material.hll");
  FILE("./Ring3.Visuals/sources/Ring3/WindingMode.hll");
  FILE("./Ring3.Visuals/sources/Ring3/PrimitiveType.hll");
#if 0
  FILE("./LastMenStanding.Framework/src/g/message_kind.s");
  FILE("./LastMenStanding.Framework/src/g/msg.s");
  FILE("./LastMenStandingEngine/src/gv/font.s");

  FILE("./LastMenStandingAssets/src/gag/vertex_buffer.s");
  FILE("./LastMenStandingAssets/src/gag/vertex_descriptor.s");
  FILE("./LastMenStandingAssets/src/gag/vertex_element_descriptor.s");
  FILE("./LastMenStandingAssets/src/gag/uv_source.s");
  FILE("./LastMenStandingAssets/src/gag/uv_source_constant.s");
  FILE("./LastMenStandingAssets/src/gag/rgba_source_flags.s");
  FILE("./LastMenStandingAssets/src/gag/rgba_source.s");
  FILE("./LastMenStanding.Framework/src/g/image.s");
  FILE("./LastMenStanding.Framework/src/g/rect_int64.s");
  FILE("./LastMenStandingEngine/src/g/window.s");
  FILE("./LastMenStandingEngine/src/g/context.s");
  FILE("./LastMenStandingEngine.Gui/src/g/gui/desktop.s");
  FILE("./LastMenStandingEngine.Gui/src/g/gui/widgets.s");
  FILE("./LastMenStandingEngine.Gui/src/g/gui/text.s");
  FILE("./LastMenStandingEngine.Gui/src/g/gui/image.s");
  FILE("./LastMenStandingEngine/src/gv/gl1/context.s");
  FILE("./LastMenStandingEngine/src/gv/gl4/context.s");
  FILE("./LastMenStandingEngine.Game/src/g/game/entity_flags.s");
  FILE("./LastMenStandingEngine.Game/src/g/game/entity.s");
  FILE("./LastMenStandingEngine.Game/src/g/game/world.s");
  FILE("./LastMenStandingEngine.Game/src/g/game/bullet.s");
  FILE("./LastMenStandingEngine.Game/src/g/game/player.s");

  FILE("./LastMenStanding.Ddl/src/g/ddl/ast/node.s");
  FILE("./LastMenStanding.Ddl/src/g/ddl/ast/value_node.s");
  FILE("./LastMenStanding.Ddl/src/g/ddl/ast/primitive_value_node.s");
  FILE("./LastMenStanding.Ddl/src/g/ddl/ast/list_value_node.s");
  FILE("./LastMenStanding.Ddl/src/g/ddl/ast/map_value_node.s");
  FILE("./LastMenStanding.Ddl/src/g/ddl/ast/error_node.s");
  FILE("./LastMenStanding.Ddl/src/g/ddl/ast/program_node.s");

  FILE("./LastMenStanding.Ddl/src/g/ddl/parser.s");
  FILE("./LastMenStanding.Ddl/src/g/ddl/scanner.s");
  FILE("./LastMenStanding.Ddl/src/g/ddl/token.s");
  FILE("./LastMenStanding.Ddl/src/g/ddl/token_kind.s");
  FILE("./LastMenStanding.Ddl/src/g/ddl/names.s");
  FILE("./LastMenStanding.Ddl/src/g/ddl/diagnostics/diagnosis_kind.s");
  FILE("./LastMenStanding.Ddl/src/g/ddl/diagnostics/diagnosis_flags.s");
  FILE("./LastMenStanding.Ddl/src/g/ddl/diagnostics/diagnosis.s");

  FILE("./LastMenStandingEngine.Graphics/src/gv/culling_mode.s");
  FILE("./LastMenStandingEngine.Graphics/src/gv/depth_test_function.s");
  FILE("./LastMenStandingEngine.Graphics/src/gv/winding_mode.s");
  FILE("./LastMenStandingEngine.Graphics/src/gv/colour_blending_factor.s");
  FILE("./LastMenStandingEngine.Graphics/src/gv/primitive_type.s");
  FILE("./LastMenStandingEngine.Graphics/src/gv/glyph.s");
  FILE("./LastMenStandingEngine.Graphics/src/gv/resource.s");
  FILE("./LastMenStandingEngine.Graphics/src/gv/buffer.s");
  FILE("./LastMenStandingEngine.Graphics/src/gv/program.s");
  FILE("./LastMenStandingEngine.Graphics/src/gv/texture.s");
  FILE("./LastMenStandingEngine.Graphics/src/gv/buffer_binding.s");
  FILE("./LastMenStandingEngine.Graphics/src/gv/functions.s");
#endif
#undef FILE

  cc_program_tree* program = cc_tree_factory_create_program(cc_tree_factory_get_instance(ctx));
  for (size_t i = 0, n = cc_arraylist_get_size(cc_options_get_source_files(options)); i < n; ++i)
  {
    cc_cstring* source_file = (cc_cstring*)cc_arraylist_get_at(cc_options_get_source_files(options), i);
    cc_ctx_add_source_file(ctx, program, source_file);
  }

  // enter builtin phase & enter tree phase
  cc_enter* enter = cc_enter_get_instance(ctx);
  cc_enter_run(enter, program);
  
  // resolve phase
  cc_resolve* resolve = cc_resolve_get_instance(ctx);
  cc_resolve_run(resolve);
  
  // emit phase
  cc_emit* emit = cc_emit_get_instance(ctx);
  cc_emit_run(emit);
}

cc_tool*
cc_create_spectre_tool
  (
  )
{ return cc_tool_create(cc_cstring_create("spectre"), &run); }
