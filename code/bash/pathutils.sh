#!/bin/bash

# ***********************************************
#  High-performance scientific computing in C++
#  29 May -- 02 June 2023
#  Jülich Supercomputing Centre
# ***********************************************

rmspecial() {
    sed -e 's/[]\/()$*.^|[]/\\&/g' <<< "$1"
}

# Usage:
# prepend_path NAME_OF_PATH_ENV_VAR LOCATION_TO_PREPEND
prepend_path() {
    local pathtochange prevpath
    pathtochange=$1
    prevpath=${!pathtochange}
    if [ -d "$2" ]; then
        [[ ":${prevpath}:" != *":$2:"* ]] && prevpath="$2:${prevpath}"
    fi
    eval "export ${pathtochange}=${prevpath}"
}

# Usage:
# remove_path_element NAME_OF_PATH_ENV_VAR LOCATION_TO_REMOVE_FROM_IT
remove_path_element() {
    local pathtochange prevpath toremove
    pathtochange=$1
    prevpath=${!pathtochange}
    toremove=$(rmspecial $2)
    prevpath=$(eval "echo ${prevpath} | sed -e 's#$toremove:##'")
    prevpath=$(eval "echo ${prevpath} | sed -e 's#:$toremove##'")
    eval "export ${pathtochange}=${prevpath}"
}

# Usage:
# pathadd /a/b/c/bin
pathadd() {
    prepend_path PATH $1
}
# Usage:
# pathrm /a/b/c/bin
pathrm() {
    remove_path_element PATH $1
}
libpathadd() {
    prepend_path LD_LIBRARY_PATH $1
    prepend_path LD_RUN_PATH $1
    prepend_path LIBRARY_PATH $1
}
libpathrm() {
    remove_path_element LD_LIBRARY_PATH $1
    remove_path_element LD_RUN_PATH $1
    remove_path_element LIBRARY_PATH $1
}

incpathadd() {
    prepend_path CPATH $1
}
incpathrm() {
    remove_path_element CPATH $1
}
manpathadd() {
    prepend_path MANPATH $1
}
manpathrm() {
    remove_path_element MANPATH $1
}
cmpathadd() {
    prepend_path CMAKE_PREFIX_PATH $1
}
cmpathrm() {
    remove_path_element CMAKE_PREFIX_PATH $1
}
pypathadd() {
    prepend_path PYTHONPATH $1
}
pypathrm() {
    remove_path_element PYTHONPATH $1
}

