#include <tree_sitter/parser.h>
#include <wctype.h>

enum TokenType {
  KEYWORD,
};

void *tree_sitter_pharo_external_scanner_create() { return NULL; }
void tree_sitter_pharo_external_scanner_destroy(void *p) {}
unsigned tree_sitter_pharo_external_scanner_serialize(void *p, char *buffer) { return 0; }
void tree_sitter_pharo_external_scanner_deserialize(void *p, const char *b, unsigned n) {}

bool tree_sitter_pharo_external_scanner_scan(void *p, TSLexer *lexer, const bool *valid_symbols) {
  if (!valid_symbols[KEYWORD]) return false;

  while (iswspace(lexer->lookahead)) {
    lexer->advance(lexer, true);
  }

  if (iswalpha(lexer->lookahead) || lexer->lookahead == '_') { // Pharo can have _ as identifier prefix
    do {
      lexer->advance(lexer, false);
    } while (iswalnum(lexer->lookahead) || lexer->lookahead == '_');

    if (lexer->lookahead == ':') {
      lexer->advance(lexer, false);
      if (lexer->lookahead != '=') {
        lexer->result_symbol = KEYWORD;
        return true;
      }
    }
  }

  return false;
}
