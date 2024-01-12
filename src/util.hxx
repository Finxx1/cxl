bool isnum(char c) {
    return c >= '0' && c <= '9';
}

bool iswhitespace(char c) {
    return c == ' ' || c == '\t' || c == '\n' || c == '\r';
}

bool my_isalpha(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '_');
}

bool my_strcmp(const char* a, const char* b, int length) {
    for (int i = 0; i < length; i++) {
        if (a[i] != b[i]) return false;
    }
    return true;
}