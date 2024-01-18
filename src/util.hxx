// CXL - A programming language
// This file is licensed under the BSD-2 Clause license.

bool my_is_num(char c) {
	return (c >= '0' && c <= '9') || c == 'E';
}

bool my_is_whitespace(char c) {
	return c == ' ' || c == '\t' || c == '\n' || c == '\r';
}

bool my_is_alpha(char c) {
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '_');
}

bool my_strcmp(const char* a, const char* b, int length) {
	for (int i = 0; i < length; i++) {
		if (a[i] != b[i]) return false;
	}
	return true;
}