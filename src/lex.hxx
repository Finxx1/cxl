// CXL - A programming language
// This file is licensed under the BSD-2 Clause license.

#include "tokens.hxx"

enum class TokenType {
    END,
	NUMBER,
	STRING,
	KEYWORD,
	OPERATOR,
	DELIM,
	ID,
};

struct Token {
	const char* str;
	int len;
	TokenType type;
};

class Lexer {
	public:
		const char* text;
		unsigned long cursor;
		unsigned long length;
		
		Lexer(const char* source);

		Token get_next_token();
		void lex();
};

Lexer::Lexer(const char* source) {
	this->text = source;
	this->cursor = 0;
	this->length = strlen(source);
}

Token Lexer::get_next_token() {
	Token r;

	for (const char* key : keywords) {
		long keylength = strlen(key);
		if (this->cursor + keylength > this->length) continue;
		
		if (my_strcmp(key, &this->text[this->cursor], keylength)) {
			r.type = TokenType::KEYWORD;
			r.str = key;
			r.len = keylength;

			return r;
		}
	}

	for (const char* op : operators) {
		long oplength = strlen(op);
		if (this->cursor + oplength > this->length) continue;
		
		if (my_strcmp(op, &this->text[this->cursor], oplength)) {
			r.type = TokenType::OPERATOR;
			r.str = op;
			r.len = oplength;

			return r;
		}
	}

	for (const char* delim : delims) {
		long delimlength = strlen(delim);
		if (this->cursor + delimlength > this->length) continue;
		
		if (my_strcmp(delim, &this->text[this->cursor], delimlength)) {
			r.type = TokenType::DELIM;
			r.str = delim;
			r.len = delimlength;

			return r;
		}
	}

    if (my_is_num(this->text[this->cursor])) {
        unsigned long begin = this->cursor;

        while (my_is_num(this->text[this->cursor])) {
            if (this->cursor >= this->length) break;
            this->cursor++;
        }

        r.type = TokenType::NUMBER;
        r.str = &this->text[begin];
        r.len = this->cursor - begin;

        return r;
    }

    if (this->text[this->cursor] == '"') {
        unsigned long begin = this->cursor;

        while (this->text[this->cursor] != '"' || this->text[this->cursor - 1] != '\\') {
            if (this->cursor >= this->length) break;
            this->cursor++;
        }

        r.type = TokenType::STRING;
        r.str = &this->text[begin];
        r.len = this->cursor - begin;

        return r;
    }
    if (my_is_alpha(this->text[this->cursor])) {
        unsigned long begin = this->cursor;

        while (my_is_alpha(this->text[this->cursor])) {
            if (this->cursor >= this->length) break;
            this->cursor++;
        }

        r.type = TokenType::ID;
        r.str = &this->text[begin];
        r.len = this->cursor - begin;

        return r;
    }

	r.type = TokenType::END;
    return r;
}
