const char* keywords[] = {
    "import",
    "void",
    "const",
    "class",
    "break",
    "continue",
    "if",
    "u8",
    "u16",
    "u32",
    "u64",
    "i8",
    "i16",
    "i32",
    "i64",
    "string",
};

const char* operators[] = {
    "+",
    "-",
    "*",
    "/",
    "%",
    "++",
    "--",
    "==",
    "!=",
    ">",
    "<",
    ">=",
    "<=",
    "!",
    "&&",
    "||",
    "~",
    "&",
    "|",
    "^",
    "=",
    "+=",
    "-=",
    "*=",
    "/=",
    "%=",
    "&=",
    "|=",
    "<<",
    "<<=",
    ">>",
    ">>=",
    "[",
    "]",
    ".",
};

const char* delims[] = {
    ";",
    "{",
    "}",
    "(",
    ")",
    ",",
    "::",
};

struct Token {
    enum {
        STRLITERAL,
        NUMLITERAL,
        KEYWORD,
        ID,
        OPERATOR,
        DELIM
    } type;
    char* str;
    int len;
};

bool lex(char* str, std::vector<Token>& tokens) {
    char* cursor = str;
    char* end = str;
    while (end[0] != '\0') end++;

    while (cursor[0] != '\0') {
        Token tok;
        char* begin = cursor;

        if (cursor[0] == '"') {
            cursor++;
            while (cursor[0] != '"') {
                if (cursor[0] == '\0') break;
                if (cursor[0] == '\\') cursor++;
                cursor++;
            }

            tok.type = tok.STRLITERAL;
            tok.len = cursor - begin - 1;
            tok.str = begin + 1;

            cursor++;
        } else if (isnum(cursor[0])) {
            while (isnum(cursor[0])) {
                if (cursor[0] == '\0') break;
                cursor++;
            }

            tok.type = tok.NUMLITERAL;
            tok.len = cursor - begin;
            tok.str = begin;
        } else if (my_isalpha(cursor[0])) {
            for (const char* keyword : keywords) {
                int len = strlen(keyword);
                bool r = false;

                if (len < end-cursor) {
                    r = my_strcmp(keyword, (const char*)cursor, len);
                }

                if (r) {
                    tok.type = tok.KEYWORD;
                    tok.len = len;
                    tok.str = (char*)keyword;
                    break;
                }
            }

            while (my_isalpha(cursor[0] || isnum(cursor[0]))) {
                if (cursor[0] == '\0') break;
                cursor++;
            }

            tok.type = tok.ID;
            tok.len = cursor - begin;
            tok.str = begin;
        } else {
            for (const char* op : operators) {
                int len = strlen(op);
                bool r = false;

                if (len < end-cursor) {
                    r = my_strcmp(op, (const char*)cursor, len);
                }

                if (r) {
                    tok.type = tok.OPERATOR;
                    tok.len = len;
                    tok.str = (char*)op;
                    break;
                }
            }

            for (const char* delim : delims) {
                int len = strlen(delim);
                bool r = false;

                if (len < end-cursor) {
                    r = my_strcmp(delim, (const char*)cursor, len);
                }

                if (r) {
                    tok.type = tok.DELIM;
                    tok.len = len;
                    tok.str = (char*)delim;
                    cursor++;
                    break;
                }
            }
        }
        
        while (iswhitespace(cursor[0])) cursor++;

        std::string str(tok.str, tok.len);
        printf("Type: %d, Value: %s\n", tok.type, str.c_str());

        tokens.push_back(tok);
    }

    return true;
}