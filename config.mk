# For both NMAKE and GNUmake
app = cxl
lang = cxx

tool_dir = tools
obj_dir = obj
bin_dir = bin
src_dir = src
inc_dir = llvm/include
lib_dir = llvm/lib

# For solely NMAKE
win_cflags = /EHsc /Zi
win_ldflags = 
win_libs = kernel32.lib LLVMCore.lib LLVMRemarks.lib LLVMBitstreamReader.lib LLVMBinaryFormat.lib LLVMTargetParser.lib LLVMSupport.lib LLVMDemangle.lib