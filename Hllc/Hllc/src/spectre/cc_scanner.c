/* Copyright (c) 2020 Michael Heilmann. All rights reserved. */
#include "spectre/cc_scanner.h"


#include <memory.h>


cc_cstring* cc_token_kind_to_string(cc_token_kind self)
{
  switch (self)
  {
#define DEFINE(name, string) \
  case CC_TKT_##name: \
  { \
    return cc_cstring_create(string); \
  } break;
#include "spectre/cc_token_kind.i"
#undef DEFINE
  default:
    CC_UNREACHABLE_ERROR();
  };
}

static const char KEY[] = "cc:spectre:scanner";

typedef struct cc_keyword
{
  const char* string;
  size_t string_length;
  int id;
} cc_keyword;

// IMPORTANT: Keep sorted by keyword length.
static const cc_keyword KEYWORDS[] =
{
  { "out",         sizeof("out") - 1,         CC_TKT_OUT         },
  { "class",       sizeof("class") - 1,       CC_TKT_CLASS       },
  { "module",      sizeof("module") - 1,      CC_TKT_MODULE      },
  { "static",      sizeof("static") - 1,      CC_TKT_STATIC      },
  { "sealed",      sizeof("sealed") - 1,      CC_TKT_SEALED      },
  { "public",      sizeof("public") - 1,      CC_TKT_PUBLIC      },
  { "extends",     sizeof("extends") - 1,     CC_TKT_EXTENDS     },
  { "private",     sizeof("private") - 1,     CC_TKT_PRIVATE     },
  { "foreign",     sizeof("foreign") - 1,     CC_TKT_FOREIGN     },
  { "override",    sizeof("override") - 1,    CC_TKT_OVERRIDE    },
  { "abstract",    sizeof("abstract") - 1,    CC_TKT_ABSTRACT    },
  { "protected",   sizeof("protected") - 1,   CC_TKT_PROTECTED   },
  { "namespace",   sizeof("namespace") - 1,   CC_TKT_NAMESPACE   },
  { "structure",   sizeof("structure") - 1,   CC_TKT_STRUCTURE   },
  { "implements",  sizeof("implements") - 1,  CC_TKT_IMPLEMENTS  },
  { "destructor",  sizeof("destructor") - 1,  CC_TKT_DESTRUCTOR  },
  { "constructor", sizeof("constructor") - 1, CC_TKT_CONSTRUCTOR },
  { "enumeration", sizeof("enumeration") - 1, CC_TKT_ENUMERATION },
};

static const size_t KEYWORD_COUNT = sizeof(KEYWORDS) / sizeof(cc_keyword);

static void cc_scanner_visit(cc_scanner* self)
{ 
  CC_VISIT(self->file_path);
  CC_VISIT(self->input);
}

static cc_scanner* factory(cc_ctx* ctx)
{
  cc_type* type = CC_DECORATE(cc_scanner_get_type)();
  cc_scanner* self = (cc_scanner*)cc_object_allocate_2(type);

  self->names = cc_spectre_names_get_instance(ctx);
  self->input = cc_bytebuffer_create();
  self->token.kind = CC_TKT_SOI;
  self->token.text.nelems = 0;
  self->token.text.elems[0] = '\0';

  return self;
}

DEFINE_COMPONENT(cc_scanner, &factory, &cc_scanner_visit, NULL)

void cc_scanner_set_input(cc_scanner* self, cc_cstring* file_path)
{
  // Reset everything to defaults.
  self->file_path = NULL;
  cc_bytebuffer_clear(self->input);
  self->start = NULL;
  self->current = NULL;
  self->end = NULL;
  self->token.kind = CC_TKT_SOI;
  self->token.text.nelems = 0;
  self->token.text.elems[0] = '\0';
  self->token.range.start = 0;
  self->token.range.end = 0;

  cc_get_file_contents_ex(file_path, self->input);
  self->start = self->input->p;
  self->current = self->input->p;
  self->end = self->input->p + self->input->sz;
  self->file_path = file_path;
  self->line_map = cc_line_map_create(file_path, self->input);
}

static void write(cc_scanner* self, char c)
{
  // Encoding error.
  if ('\0' == *self->current)
  {
    cc_print_f(CC_PRINT_FLAG_ERROR | CC_PRINT_FLAG_INTERNAL, "%s:%d: encoding error\n", __FILE__, __LINE__);
    cc_error(CC_EINVAL);
  }
  // Capacity exhausted error.
  if (self->token.text.nelems == 1024)
  {
    cc_print_f(CC_PRINT_FLAG_ERROR | CC_PRINT_FLAG_INTERNAL, "%s:%d: buffer capacity exhausted\n", __FILE__, __LINE__);
    cc_error(CC_ENOMEM);
  }
  self->token.text.elems[self->token.text.nelems++] = *self->current;
  self->token.text.elems[self->token.text.nelems] = '\0';
}

static void save(cc_scanner* self)
{
  // The empty string.
  if (self->current == self->end)
  { return; }
  write(self, *self->current);
}

static void next(cc_scanner* self)
{
  if (self->current != self->end)
  {
    self->current++;
  }
}

static void save_and_next(cc_scanner* self)
{
  save(self);
  next(self);
}

/*Returns number of lines skipped.*/
static int skip_newlines(cc_scanner* scanner)
{
  int n = 0;
  // '\n', '\r', '\r\n'.
  while (scanner->current != scanner->end && (*scanner->current == '\n' || *scanner->current == '\r'))
  {
    int old = *scanner->current;
    scanner->current++;
    if (old == '\r' && scanner->current != scanner->end && *scanner->current == '\n')
    {
      scanner->current++;
    }
    n++;
  }
  return n;
}

/*Returns number of whitespaces skipped.*/
static int skip_whitespaces(cc_scanner* scanner)
{
  int n = 0;
  while (scanner->current != scanner->end && (*scanner->current == ' ' || *scanner->current == '\t'))
  {
    scanner->current++;
    n++;
  }
  return n;
}

static bool is_underscore(cc_scanner* scanner)
{
  if (scanner->current == scanner->end) return false;
  return '_' == *scanner->current;
}

static bool is_digit(cc_scanner* scanner)
{
  if (scanner->current == scanner->end) return false;
  return '0' <= *scanner->current && *scanner->current <= '9';
}

static bool is_char(cc_scanner* scanner)
{
  if (scanner->current == scanner->end) return false;
  return ('a' <= *scanner->current && *scanner->current <= 'z')
      || ('A' <= *scanner->current && *scanner->current <= 'Z');
}

static void on_begin_token(cc_scanner* self)
{
  self->token.kind = CC_TKT_ERR;
  self->token.range.start = self->token.range.end;
  self->token.text.nelems = 0;
  self->token.text.elems[0] = '\0';
}

static void on_end_token(cc_scanner* self, int kind)
{
  self->token.kind = kind;
  self->token.range.end = self->current - self->start;
}

void cc_scanner_step(cc_scanner* scanner)
{
  if (scanner->token.kind == CC_TKT_EOI || scanner->token.kind == CC_TKT_ERR)
  {
    return;
  }
  while (skip_newlines(scanner) > 0 || skip_whitespaces(scanner) > 0)
  { }
  if (scanner->current == scanner->end)
  {
    on_end_token(scanner, CC_TKT_EOI);
    return;
  }
  on_begin_token(scanner);
  switch (*scanner->current)
  {
    case '=':
    {
      save_and_next(scanner);
      on_end_token(scanner, CC_TKT_ASSIGN);
    } break;
    case '+':
    {
      save_and_next(scanner);
      on_end_token(scanner, CC_TKT_PLUS);
    } break;
    case '-':
    {
      save_and_next(scanner);
      on_end_token(scanner, CC_TKT_MINUS);
    } break;
    case '*':
    {
      save_and_next(scanner);
      on_end_token(scanner, CC_TKT_STAR);
    } break;
    case ',':
    {
      save_and_next(scanner);
      on_end_token(scanner, CC_TKT_COMMA);
    } break;
    case ';':
    {
      save_and_next(scanner);
      on_end_token(scanner, CC_TKT_SEMICOLON);
    } break;
    case '{':
    {
      save_and_next(scanner);
      on_end_token(scanner, CC_TKT_LEFT_CURLY_BRACKET);
    } break;
    case '}':
    {
      save_and_next(scanner);
      on_end_token(scanner, CC_TKT_RIGHT_CURLY_BRACKET);
    } break;
    case '(':
    {
      save_and_next(scanner);
      on_end_token(scanner, CC_TKT_LEFT_PARENTHESIS);
    } break;
    case ')':
    {
      save_and_next(scanner);
      on_end_token(scanner, CC_TKT_RIGHT_PARENTHESIS);
    } break;
    case '[':
    {
      save_and_next(scanner);
      on_end_token(scanner, CC_TKT_LEFT_SQUARE_BRACKET);
    } break;
    case ']':
    {
      save_and_next(scanner);
      on_end_token(scanner, CC_TKT_RIGHT_SQUARE_BRACKET);
    } break;
    case '.':
    {
      save_and_next(scanner);
      on_end_token(scanner, CC_TKT_PERIOD);
    } break;
    case '/':
    {
      scanner->current++;
      if (scanner->current != scanner->end && *scanner->current == '/')
      {
        scanner->current++;
        while (scanner->current != scanner->end && !(*scanner->current == '\n' || *scanner->current == '\r'))
        {
          save_and_next(scanner);
        }
        on_end_token(scanner, CC_TKT_COMMENT_LINE);
      }
      else
      {
        on_end_token(scanner, CC_TKT_ERR);
      }
    } break;
    default:
    {
      if (is_digit(scanner))
      {
        do
        {
          save_and_next(scanner);
        } while (is_digit(scanner));
        on_end_token(scanner, CC_TKT_INTEGER);
      }
      else if (is_char(scanner) || is_underscore(scanner))
      {
        do
        {
          save_and_next(scanner);
        } while (is_char(scanner) || is_digit(scanner) || is_underscore(scanner));
        on_end_token(scanner, CC_TKT_NAME);
        for (size_t i = 0, n = KEYWORD_COUNT; i < n; ++i)
        {
          const cc_keyword* kw = &(KEYWORDS[i]);
          // If the keyword length is greater then the length of the lexeme => stop.
          // Reason: All subsequent keywords are longer anyway.
          if (kw->string_length > scanner->token.text.nelems)
          {
            break;
          }
          if (kw->string_length == scanner->token.text.nelems && !memcmp(kw->string, scanner->token.text.elems, kw->string_length))
          {
            on_end_token(scanner, kw->id);
            break;
          }
        }
      }
      else
      {
        on_end_token(scanner, CC_TKT_ERR);
      }
    } break;
  };
}

cc_line_map* cc_scanner_get_line_map(cc_scanner* self)
{
  return self->line_map;
}

cc_file_offset cc_scanner_get_start_offset(cc_scanner* self)
{
  return self->token.range.start;
}

cc_file_offset cc_scanner_get_end_offset(cc_scanner* self)
{
  return self->token.range.end;
}

cc_cstring* cc_scanner_get_file_path(cc_scanner* self)
{
  return self->file_path;
}

int cc_scanner_get_kind(cc_scanner* self)
{
  return self->token.kind;
}

cc_name* cc_scanner_get_text(cc_scanner* self)
{
  return cc_spectre_names_get_or_create(self->names, self->token.text.elems);
}
