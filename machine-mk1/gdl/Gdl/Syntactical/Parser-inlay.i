
static Machine_Gdl_TokenKind currentKind(Machine_Gdl_Parser *self) {
    return Machine_Gdl_Scanner_getTokenKind(self->scanner);
}
