for m in Point Circle Polygon Triangle; do
echo "Generating CMI and object files for $m"
g++ -std=c++20 -fmodules-ts -xc++ -c $m.ixx
done
echo "Compiling main.cc -> a.gcc"
g++ -std=c++20 -fmodules-ts -o a.gcc main.cc Point.o Circle.o Polygon.o Triangle.o

echo "GCC module implementation is not in a usable state as of May 2023."
echo "Check if the example builds and runs."



