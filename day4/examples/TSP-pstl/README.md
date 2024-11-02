Notes on building
=================

This project needs at least Clang 16.0, CMake 3.26.3
and Ninja 1.11. Besides, the clang 16 must have been
compiled with support for parallel STL. This is
currently, quite unfortunately, not a straight forward
"cmake - make - make install" process. You saw a working
version in the class, and I will outline here what
I did, so that you can reproduce it. Hopefully, we
will not need to go to so much trouble for such
fundamental HPC tools like parallel algorithms for
much longer:

A. Building LLVM/Clang with parallel STL for LLVM 16.0
1. Configuration step:

cd builddir
CC=clang CXX=clang++ cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=installdir -DLLVM_ENABLE_PROJECTS="clang;clang-tools-extra;lld;openmp" -DLLVM_ENABLE_RUNTIMES="libcxxabi;libcxx;libunwind;pstl" -DLLVM_TARGETS_TO_BUILD="X86" -DLLVM_INSTALL_MODULEMAPS=ON -DLLVM_INSTALL_UTILS=ON -DLIBCXX_ENABLE_PARALLEL_ALGORITHMS=ON -DPSTL_PARALLEL_BACKEND=tbb -DLIBCXX_ENABLE_INCOMPLETE_FEATURES=ON llvm-project-src/llvm

In the above, builddir is any directory you create to
build LLVM. "llvm-project-src" refers to the directory
created when you unpacked the llvm project source archive
llvm-project-16.0.6.src.tar.xz, which you downloaded from,
https://github.com/llvm/llvm-project/releases/download/llvmorg-16.0.6/llvm-project-16.0.6.src.tar.xz

"installdir" is the place you want to put
your final compiled version of LLVM tools and libraries.
You must have write access to that directory. Choose
something non-intrusive for your system, e.g.,
~/local/llvm/16.0.6, i.e.,
-DCMAKE_INSTALL_PREFIX=~/local/llvm/16.0.6


2. Try to build it (necessary, even if it is almost
   certainly going to fail!)

make -j 8 -k

3. Ideally, the above should succeed, and you should
   be able to do a "make install". The problem is,
   LLVM/Clang is currently broken as far as parallel
   STL is concerned, and you need the work arounds
   below.

4. Most likely, your build step will end with a message
   "ParallelSTL not found". This usually happens if you
   put pstl in the -DLLVM_ENABLE_PROJECTS option, along
   with clang, lld etc. That's what one sees in the LLVM
   webpage, at the moment, and that does not work, at the
   moment. To go further, configure as I have shown in
   the step 1 above. It will fail, saying "__pstl_memory
   file not found" or something similar. __pstl_memory,
   __pstl_algorithm etc. are headers generated when we
   finish in the "pstl" folder, which should now be inside
   your build/runtimes/runtimes-bins folder. The problem
   is, the files are only generated when we run "make install"
   in that directory, not when we simply run "make". So,
   I ran "make install". It puts the headers I need in
   the install_prefix/include folder. I then create
   soft-links inside my build directory as follows:

   cd builddir/include
   ln -s installdir/include/__pstl* ./
   ln -s installdir/pstl ./
   mkdir -p c++/v1
   cd c++/v1
   ln -s ../../__pstl* ./
   ln -s ../../pstl ./

   After that the build continues until it fails at the next
   stumbling block: std::not_fn not defined! std::not_fn
   should be defined in the "functional" header, and you will
   see it in two places in builddir/include/c++/v1/functional.
   The first version is expository code, which is inside a
   comment block that starts many pages above it. So, that
   code is not seen by the compiler. Below that expository
   code, we have a series of #include directives, including
   dedicated headers for different functionals. Unfortunately,
   these are sorted in the alphabetical order, so that the
   header for not_fn is below a lot of other headers in the
   list; one of those other headers has a call to std::not_fn.
   The proper fix would be to examine why that dependency
   exists and may be fix the other header. Probably the libcxx
   developers will take care of it soon. In the mean time,
   one could move the not_fn header, __functional/not_fn.h
   high up, to just below __debug.

   Returning to the top level build directory and continuing
   the compilation now ends successfully.

5. Install

   make install
   cd installdir
   cd include/c++/v1
   ln -s ../../__pstl* ./
   ln -s ../../pstl ./


B. Building our TSP example, which uses both C++20 modules and
   parallel STL (using LLVM 16.0 built as above, CMake 3.26, and
   Ninja 1.11.1)

   (i) Make sure clang++ is in PATH and libc++ etc are 
   are in the LD_LIBRARY_PATH etc.
   (ii) Configuration step:
   mkdir build
   cd build
   CXX=clang++ cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_GENERATOR=Ninja ..
   (iii) Build step:
   make


