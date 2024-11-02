#!/bin/bash

sources="Machinery.ccm algo.ccm MyGreatProduct.ccm"
blddir="MODULE_BUILD"
mkdir -p $blddir
for source in $sources; do
clang++ -std=c++20 -stdlib=libc++ -fmodules --precompile -fprebuilt-module-path=$blddir -o $blddir/$(basename $source .ccm).pcm $source
done
cp $blddir/MyGreatProduct.pcm .


