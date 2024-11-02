#!/bin/bash

PREFIX=""

check_prefix_dir() {
    if [ -d "$PREFIX" ]; then
       echo "Install prefix : $PREFIX" 
    else
      echo "PREFIX directory set to '$PREFIX' which is not a valid PATH"
      echo "Run with prefix option, e.g, --prefix /a/b/c"
      kill -INT $$
    fi
}
install_range_v3() {
    check_prefix_dir
    if [ ! -f 0.12.0.tar.gz ]; then
      echo "Downloading range-v3";
      wget https://github.com/ericniebler/range-v3/archive/refs/tags/0.12.0.tar.gz
    else
      echo "Previously downloaded file for range-v3 exists."
    fi
    tar -xzf 0.12.0.tar.gz
    pushd range-v3-0.12.0
    mkdir -p build
    pushd build
    rm -f CMakeCache.txt
    CXX=g++ cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=$PREFIX -DRANGE_V3_TESTS=OFF -DRANGE_V3_EXAMPLES=OFF -DRANGE_V3_DOCS=OFF ..
    make install
    popd
    popd
}

install_libfmt() {
    check_prefix_dir
    if [ ! -f 10.0.0.tar.gz ]; then
      echo "Downloading libfmt";
      wget https://github.com/fmtlib/fmt/archive/refs/tags/10.0.0.tar.gz
    else
      echo "Previously downloaded file for libfmt exists."
    fi
    tar -xzf 10.0.0.tar.gz
    pushd fmt-10.0.0
    mkdir -p build
    pushd build
    rm -f CMakeCache.txt
    CXX=g++ cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=$PREFIX -DFMT_TEST=OFF ..
    make install
    popd
    popd
}

install_xsimd() {
    check_prefix_dir
    if [ ! -f 9.0.1.tar.gz ]; then
      echo "Downloading xsimd";
      wget https://github.com/xtensor-stack/xsimd/archive/9.0.1.tar.gz
    else
      echo "Previously downloaded file for xsimd exists."
    fi
    echo "Downloading xsimd";
    tar -xzf 9.0.1.tar.gz
    pushd xsimd-9.0.1
    mkdir -p build
    pushd build
    CXX=g++ cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=$PREFIX -DXSIMD_TEST=OFF ..
    make install
    popd
    popd
}

install_ctre() {
    check_prefix_dir
    if [ ! -f v3.5.tar.gz ]; then
      echo "Downloading CTRE";
      wget https://github.com/hanickadot/compile-time-regular-expressions/archive/refs/tags/v3.5.tar.gz
    else
      echo "Previously downloaded file for CTRE exists."
    fi
    tar xzf v3.5.tar.gz --one-top-level=ctre-v3.5 --strip-components 1
    pushd ctre-v3.5
    mkdir -p build
    pushd build
    CXX=g++ cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=$PREFIX -DCTRE_BUILD_TESTS=OFF ..
    make install
    popd
    popd
}

while [[ $# > 0 ]]; do
    key=$1
    case $key in
      --prefix|-prefix)
      PREFIX=$2
      shift;
      ;;
      ranges|range|range-v3)
          install_range_v3
      ;;
      fmt|format|libfmt)
          install_libfmt
      ;;
      xsimd)
          install_xsimd
      ;;
      ctre|CTRE)
          install_ctre
      ;;
      all)
          install_range_v3
          install_libfmt
          install_xsimd
          install_ctre
      ;;
    esac;
    shift
done

