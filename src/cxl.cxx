// CXL - A programming language
// This file is licensed under the BSD-2 Clause license.

//
// This file is the main file.
// It is the only one that is
// compiled. Everything else
// is just included. Think of
// it as the "driver".
//

//
// Objectives of CXL:
// C, but:
// - With a better, more capable standard library (like Python)
// - Without translation units (like non-C/C++ languages)
// - Without pointers (like .NET)
// - Without the preprocessor (like non-C/C++ languages)
// - With namespaces (like C++)
// Code optimization and generation is done with LLVM.
//

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <vector>
#include <string>
#include <memory>

#include "./util.hxx"
#include "./platform.hxx"

#include "./pre.hxx"
#include "./lex.hxx"
#include "./parser.hxx"

const char* usage =
"cxl file [options]";
const char* help =
"-h   Shows this help info.\n"
"-o   Specifies the name of the output executable.\n"
"-l   Specifies an additional path when looking for imports.\n"
"-c   Only generate an assembly file, do no linking.\n"
"-e   Output preprocessed code.\n"
"-q   Only output errors.\n";

struct {
	// options
	int src_file_index;
	bool src_file_set;

	int out_file_index;
	bool out_file_set;

	bool output_pre;
	bool quiet;

	std::vector<int> lib_dir_indicies;
} compiler_globals = {0};

int main(int argc, char** argv) {
	if (argc == 1) {
		printf("%s", usage);
		exit(0);
	}

	for (int i = 1; i < argc; i++) {
		if (argv[i][0] == '-') {
			switch (argv[i][1]) {
				case 'h': {
					printf("%s", help);
					exit(0);
				}
				case 'o': {
					i++;

					if (compiler_globals.out_file_set) {
                        CXL_ERROR("only one output executable can be compiled at a time.");
					}

					compiler_globals.out_file_index = i;
					compiler_globals.out_file_set = true;
					break;
				}
				case 'l': {
					i++;

					compiler_globals.lib_dir_indicies.push_back(i);
					break;
				}
				case 'e': {
					compiler_globals.output_pre = true;
					break;
				}
				case 'q': {
					compiler_globals.quiet = true;
					break;
				}
				default: {
					CXL_WARNING("ignoring unknown option '-%c'.", argv[i][1]);
					break;
				}
			}
		} else {
			if (compiler_globals.src_file_set) {
				CXL_ERROR("only one source file can be compiled at a time.");
			}

			compiler_globals.src_file_index = i;
			compiler_globals.src_file_set = true;
		}
	}

	if (!compiler_globals.src_file_set) {
		CXL_ERROR("no source file specified.");
		exit(1);
	}

	if (!compiler_globals.quiet) {
		printf("CXL Compiler, v0.1.0 (c) BSD-2 Clause (%s)\n\n", CXL_STRINGIZE(COMPILER));
	}

	FILE* fp = fopen(argv[compiler_globals.src_file_index], "rb");
	if (!fp) {
		CXL_ERROR("failed to open file '%s'.\n", argv[compiler_globals.src_file_index]);
	}

	fseek(fp, 0, SEEK_END);
	long len = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	char* filedata = (char*)malloc(len + 1);
	if (!filedata) {
		CXL_ERROR("failed to allocation %ld bytes of memory.", len + 1);
	}

	if (int bytes_read = fread(filedata, 1, len, fp) != len) {
        free(filedata);
		CXL_ERROR("failed to read file '%s'. %d bytes read of %d.\n", argv[compiler_globals.src_file_index], bytes_read, len);
	}
	filedata[len] = 0;

	pre(filedata);

	// NOTE: Imports are handled in between lexing and parsing, as import is a keyword.
	if (compiler_globals.output_pre) {
		printf("%s", filedata);
	}

    std::vector<Token> tokens;

    Lexer lex(filedata);
    lex.lex(tokens);

    ASTRoot root;
    

	exit(0);
}