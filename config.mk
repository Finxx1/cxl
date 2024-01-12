# For both NMAKE and GNUmake
app = cxl
lang = cxx

tool_dir = tools
obj_dir = obj
bin_dir = bin
src_dir = src
inc_dir = inc
lib_dir = lib

# For solely NMAKE
lex = re2c.exe

win_cflags = /EHsc /Zi
win_ldflags = 
win_libs = kernel32.lib
