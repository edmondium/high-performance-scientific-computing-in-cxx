Compile with clang:

clang++ -std=c++20 -stdlib=libc++ -fmodules -xc++-module --precompile saxpy.ixx
clang++ -std=c++20 -stdlib=libc++ -fmodules -fprebuilt-module-path=. usesaxpy.cc

If you want to compile with GCC, change the imports back to
old style includes, and then do this:

g++ -std=c++20 -fmodules-ts -xc++ -c saxpy.ixx
g++ -std=c++20 -fmodules-ts saxpy.o usesaxpy.cc


