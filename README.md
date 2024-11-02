# High-performance scientific computing in C++ 2024

Course material for the PRACE Advanced Training Course
"High-performance scientific computing in C++",
28 -- 31 October 2024 organized by the Jülich Supercomputing Centre,
Forschungszentrum Jülich, Germany.

# hpcxx2024

You will need to pull from this repository periodically during this course.

If your computer does not have "git", you will need to use the download
button to the left of the "Clone" button in the gitlab page.

## Recommended way of working with this material

The downloaded or cloned material from this repository will be updated
during the course days. You should keep one copy of the examples and
exercises in the pristine form, and work on your own duplicates.
For example, to work on the day1 examples, do as follows:

```bash
    cd day1
    cp -r examples mine
    cd mine
    clang++ -std=c++23 math_functions.cc
    ./a.out
```

Only examples (which includes some exercises) and solutions need to
be duplicated. You don't need two copies of the entire material as that
includes the PDFs of the book, course slides and other utillities.


## Testing your set up

To work with this material, you will need to have a fairly up-to-date
C++ compiler. GCC version 13.3 or Clang version 18.1 or later are
recommended.

Microsoft's Visual C++ compiler has excellent support for C++23, if
you have the latest version installed. During the course, we will focus
on using open source tools, which are available to everyone, rather
than proprietary tools.

To test your setup, proceed as follows:

```bash
    cd wherever_you_downloaded_or_cloned_this_thing
    cd test_your_setup
    g++ hello.cc -o hello.gcc
    ./hello.gcc
    clang++ hello.cc -o hello.clang
    ./hello.clang
    g++ -std=c++23 hello_c++23.cc -o hello_cxx23.gcc
    ./hello_cxx23.gcc
    clang++ -std=c++23 hello_c++20.cc -o hello_cxx20.clang
    ./hello_cxx20.clang
```

And finally to test if your compiler can at least partially
handle C++20 modules, try the two remaining examples:

```bash
    clang++ -std=c++23 -stdlib=libc++ -fmodules hello_m.cc -o hello_m.clang
    ./hello_m.clang
    clang++ -std=c++23 -stdlib=libc++ -fmodules hello_c++23_m.cc -o hello_cxx23_m.clang
    ./hello_cxx23_m.clang

    g++ -std=c++23 -fmodules-ts -xc++-system-header iostream
    g++ -std=c++23 -fmodules-ts -xc++-system-header concepts
    g++ -std=c++23 -fmodules-ts hello_m.cc -o hello_m.gcc
    g++ -std=c++23 -fmodules-ts hello_m.cc -o hello_cxx23_m.gcc
    ./hello_m.gcc
    ./hello_cxx23_m.gcc
```

# Using aliases to save some typing

As the above examples show, we will often need to type a
lot of options to compile our programs during this course,
since we want to use C++23, which is not the default
standard for the compilers yet. A few convenient aliases
have been prepared which you can use to shorten the
above compilation steps. To use them, do as follows:

```bash
source course_material_dir/code/bash/aliases.sh
```

Once you have done that, you can shorten the above 
steps to the following: 

```bash 
C hello.cc 
C hello_c++23.cc 

Cm hello_m.cc
Cm hello_c++23_m.cc 

Gh iostream 
Gh concepts 
Gm hello_m.cc 
Gm hello_c++23_m.cc


