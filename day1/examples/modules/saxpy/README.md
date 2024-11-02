Compile with clang:

clang++ -std=c++20 -stdlib=libc++ -xc++-module --precompile saxpy.ixx
clang++ -std=c++20 -c saxpy.pcm -o saxpy.o
clang++ -std=c++20 -stdlib=libc++ -fprebuilt-module-path=. usesaxpy.cc saxpy.o -o usesaxpy.clg

If you want to compile with GCC, change imports involving standard
library header units to includes, and then do this:

g++ -std=c++20 -fmodules-ts -xc++ -c saxpy.ixx
g++ -std=c++20 -fmodules-ts saxpy.o usesaxpy.cc -o usesaxpy.gcc

It is also possible to build this program by treating it as
a CMake project, using the experimental support for modules.
As of May 2023, this only works using clang 16.0, cmake 3.26
and ninja 1.11. Observe the unusual lines in the CMakeLists.txt
file. Hopefully, they will not be required for long. The following
steps will produce an executable called use_saxpy inside
the build directory:

mkdir build
cd build
CC=clang CXX=clang++ cmake -DCMAKE_GENERATOR=Ninja ..
ninja

