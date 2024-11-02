Building thse examples
==============================

mkdir build
cd build
cmake -DCMAKE\_BUILD\_TYPE=Release -DCMAKE\_CXX\_FLAGS=-march=core-avx2 ..
make


If you want to use a different compiler, use
for example,

CXX=clang++ cmake -DCMAKE\_BUILD\_TYPE=Release  -DCMAKE\_CXX\_FLAGS=-march=core-avx2 ..
and so on.


