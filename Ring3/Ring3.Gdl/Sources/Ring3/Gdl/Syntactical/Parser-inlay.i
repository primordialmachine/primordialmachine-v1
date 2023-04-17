/// @file Ring3/Gdl/Syntactical/Parser-inlay.i
/// @copyright Copyright (c) 2021-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

static Ring3_Gdl_TokenKind
currentKind
  (
    Machine_Gdl_Parser *self
  )
{ return Ring3_Gdl_Token_getKind(Ring3_Gdl_Scanner_getToken(self->scanner)); }
