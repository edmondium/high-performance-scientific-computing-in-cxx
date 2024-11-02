for m in Point Circle Polygon Triangle; do
echo "Generating CMI for $m"
clang++ -std=c++20 -stdlib=libc++ -fprebuilt-module-path=. --precompile -xc++-module $m.ixx
done
for m in Point Circle Polygon Triangle; do
echo "Generating object file for $m"
clang++ -std=c++20 -c $m.pcm
done
echo "Compiling main.cc -> a.clg"
clang++ -std=c++20 -stdlib=libc++ -fprebuilt-module-path=. -o a.clg main.cc Point.o Circle.o Polygon.o Triangle.o



