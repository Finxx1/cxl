// CXL - A programming language
// This file is licensed under the BSD-2 Clause license.

//
// This file contains the lexer.
// It is a simple lexer written
// by hand. It handles EOF by
// constantly checking for the
// position of the cursor, and
// breaking any loops if it ever
// is greater than the length.
//

#include "tokens.hxx" // keywords, operators, and delims

enum class TokenType {
    END,
	NUMBER,
	STRING,
    TYPE,
	KEYWORD,
	OPERATOR,
	DELIM,
	ID,
    UNKNOWN,
};

const char* TokenTypeStr[] = {"END", "NUMBER", "STRING", "KEYWORD", "OPERATOR", "DELIM", "ID", "UNKNOWN"};
const char* get_token_type_str(TokenType type) {
    return TokenTypeStr[(long)type];
}

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
		void lex(std::vector<Token>& tokens);
};

Lexer::Lexer(const char* source) {
	this->text = source;
	this->cursor = 0;
	this->length = strlen(source);
}

Token Lexer::get_next_token() {
	Token r;

    if (this->cursor > this->length) {
        r.type = TokenType::END;
        r.len = 0;
        r.str = NULL;
        return r;
    }

	for (const char* key : keywords) {
		long keylength = strlen(key);
		if (this->cursor + keylength > this->length) continue;
		
		if (my_strcmp(key, &this->text[this->cursor], keylength)) {
			r.type = TokenType::KEYWORD;
			r.str = key;
			r.len = keylength;

            this->cursor += keylength;

			return r;
		}
	}

	for (const char* key : types) {
		long keylength = strlen(key);
		if (this->cursor + keylength > this->length) continue;
		
		if (my_strcmp(key, &this->text[this->cursor], keylength)) {
			r.type = TokenType::TYPE;
			r.str = key;
			r.len = keylength;

            this->cursor += keylength;

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

            this->cursor += oplength;

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
            
            this->cursor += delimlength;

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
        this->cursor++;
        unsigned long begin = this->cursor;

        while (this->text[this->cursor] != '"') {
            if (this->cursor >= this->length) break;
            this->cursor++;
        }

        r.type = TokenType::STRING;
        r.str = &this->text[begin];
        r.len = this->cursor - begin;

        this->cursor++;
        return r;
    }
    if (my_is_alpha(this->text[this->cursor])) {
        unsigned long begin = this->cursor;
        this->cursor++;

        while (my_is_alpha(this->text[this->cursor]) || my_is_num(this->text[this->cursor])) {
            if (this->cursor >= this->length) break;
            this->cursor++;
        }

        r.type = TokenType::ID;
        r.str = &this->text[begin];
        r.len = this->cursor - begin;

        return r;
    }

	r.type = TokenType::UNKNOWN;
    r.len = 0;
    r.str = NULL;
    this->cursor++;
    return r;
}

void Lexer::lex(std::vector<Token>& tokens) {
    Token tok = this->get_next_token();
	while (tok.type != TokenType::END) {
        if (!tok.str) {
            tok = this->get_next_token();
            continue;
        }
        
        tokens.push_back(tok);
        tok = this->get_next_token();
    }
}
