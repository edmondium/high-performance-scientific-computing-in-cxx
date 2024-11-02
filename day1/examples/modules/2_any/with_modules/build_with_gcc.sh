for h in string cmath iostream charconv numbers array chrono random vector any; do
echo "Generating library header unit for $h"
g++ -std=c++20 -fmodules-ts -xc++-system-header $h
done

for m in Point Circle Polygon Triangle; do
echo "Generating CMI and object files for $m"
g++ -std=c++20 -fmodules-ts -xc++ -c $m.ixx
done
echo "Compiling main.cc -> a.gcc"
g++ -std=c++20 -fmodules-ts -static -o a.gcc main.cc Point.o Circle.o Polygon.o Triangle.o

echo "GCC module implementation is not in a usable state as of May 2022."
echo "Check if the example builds and runs."



