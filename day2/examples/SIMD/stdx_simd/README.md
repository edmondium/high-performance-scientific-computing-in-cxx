examples/SIMD/stdx\_simd
===========================

This directory contains a few simple examples demostrating
SIMD features of parallelism TS-2 implemented in
std::experimental namespace in the header
"<experimental/simd>". To use this SIMD library, which may
become part of a future C++ standard, we have to include
"<experimental/simd>" and use the classes and functions
defined there. In GCC, no special option is required. In
a Clang+libc++ toolchain, additionally, the option
"-fexperimental-library" is required.

stdx0.cc : A very tiny example to demonstrate a few key
elements from experimental/simd.

sprod.cc : scalar product example

daxpy.cc : double precision a * x + y calculation with
arrays x and y

exvol.cc : Calculation of an energy term from a bio-physics
simulation program, vectorized using openmp, standard library
std::execution::unseq, and std::experimental.
 
It is instructive and recommended to compile and run stdx0.cc
without the help of the acompanying CMake file. It prints
a SIMD vector containing the sum of numbers 0...(n-1) in one
such vector and (n ... 1) in another. For a SIMD unit of size
2, the printed vector will be "2, 2". If the SIMD unit can
process 4 doubles at a time, the answer will be "4, 4, 4, 4".
Play around with different options and observe in particular
the effect of various optimisation levels -O1 -O2 -O3 etc,
and the architecture option -march=native.
 
