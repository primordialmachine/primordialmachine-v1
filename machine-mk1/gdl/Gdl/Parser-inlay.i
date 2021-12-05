
static Machine_GDL_TokenKind currentKind(Machine_GDL_Parser *self) {
    return Machine_GDL_Scanner_getTokenKind(self->scanner);
}
