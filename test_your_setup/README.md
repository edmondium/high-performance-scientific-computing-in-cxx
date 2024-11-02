# Compile:

## hello.cc
g++ hello.cc
clang++ hello.cc

## hello_c++20.cc
g++ -std=c++20 hello_c++20.cc 
clang++ -std=c++20 -stdlib=libc++ hello_c++20.cc 

## hello_m.cc

With gcc:
g++ -std=c++20 -fmodules-ts -xc++-system-header iostream
g++ -std=c++20 -fmodules-ts hello_m.cc

with clang:
clang++ -std=c++20 -stdlib=libc++ -fmodules hello_m.cc

## hello_c++20_m.cc

With gcc:
g++ -std=c++20 -fmodules-ts -xc++-system-header concepts
g++ -std=c++20 -fmodules-ts -xc++-system-header iostream
g++ -std=c++20 -fmodules-ts hello_c++20_m.cc

With clang:
clang++ -std=c++20 -stdlib=libc++ -fmodules hello_c++20_m.cc


