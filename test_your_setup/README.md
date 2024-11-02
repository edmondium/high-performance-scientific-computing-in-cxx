# Compile

## GCC

    1. `hello.cc`: `g++ hello.cc`
    2. `hello_c++20.cc`: `g++ -std=c++20 hello_c++20.cc`
    3. `psort1.cc`: `g++ -std=c++20 -O3 -march=native psort1.cc -ltbb -ltbbmalloc`

## Clang

    1. `hello.cc`: `clang++ hello.cc`
    2. `hello_c++20.cc`: `clang++ -std=c++20 hello_c++20.cc`
    3. `psort1.cc`: `clang++ -std=c++20 -stdlib=libc++ -O3 -march=native psort1.cc -ltbb -ltbbmalloc`

## GCC through wrapper script G

    1. `hello.cc`: `G hello.cc` (produces output hello.g)
    2. `hello_c++20.cc`: `G hello_c++20.cc` (produces output `hello_c++20.g`)
    3. `psort1.cc`: `G -tbb psort1.cc` (produces output `psort1.g`)

## Clang through wrapper script A

    1. `hello.cc`: `A hello.cc` (produces output hello.l)
    2. `hello_c++20.cc`: `A hello_c++20.cc` (produces output `hello_c++20.l`)
    3. `psort1.cc`: `A -tbb psort1.cc` (produces output `psort1.l`)

## Clang through wrapper script B

    1. `hello.cc`: `B hello.cc` (produces output hello.b)
    2. `hello_c++20.cc`: `B hello_c++20.cc` (produces output `hello_c++20.b`)
    3. `psort1.cc`: `B -tbb psort1.cc` (produces output `psort1.b`)


