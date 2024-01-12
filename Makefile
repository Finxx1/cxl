# For use with NMAKE and MSVC

include config.mk

all:
	$(CC) $(win_cflags) $(src_dir)/$(app).$(lang) /I $(inc_dir) /Fo: $(obj_dir)/ /Fe: $(bin_dir)/$(app).exe /link $(win_ldflags) /LIBPATH:$(lib_dir)