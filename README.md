# CXL - Classic syntax, modern style
CXL aims to be a language that gets rid of old bygones (pointers, translation units, the preprocessor) while keeping the core syntax.
### Building
CXL depends on LLVM. You can get Windows binaries at https://github.com/vovkos/llvm-package-windows/releases. Place the bin, include, lib, and share folder in ./llvm/.
On Windows, building is done with MSVC. Open a developer console, navigate to the source, and run NMAKE.