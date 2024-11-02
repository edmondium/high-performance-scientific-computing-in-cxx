# Compile:

## hello.cc
```
g++ -std=c++23 hello.cc
```
or with clang...
```
clang++ -std=c++23 -stdlib=libc++ hello.cc
```

Using classroom shortcuts `G` and `C` the above can be
written like this:

```
G hello.cc
C hello.cc
```

`G` is an alias for `g++ -std=c++23 -O3 -pedantic -Wall`.
`C` is an alias for `clang++ -std=c++23 -stdlib=libc++ -O3 -pedantic -Wall`

## hello_c++23.cc
G hello_c++23.cc 
C hello_c++23.cc 

## hello_m.cc

With gcc, we build importable header units first (as shown for iostream here)
before proceeding with our source file.

```
g++ -std=c++23 -fmodules-ts -xc++-system-header iostream
g++ -std=c++23 -fmodules-ts hello_m.cc
```
Again, the above can be shortened using our shortcuts:

```
Gh iostream
Gm hello_m.cc
```

With clang, the required header units will be built for you.

```
clang++ -std=c++23 -stdlib=libc++ -fmodules hello_m.cc
```
With shortcuts, that would be:
```
Cm hello_m.cc
```

## hello_c++20_m.cc

With gcc:
Gh concepts
Gh print
Gm hello_c++23_m.cc

With clang:
Cm hello_c++23_m.cc


