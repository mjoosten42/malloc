#!/bin/bash

if [ $(uname) = "Linux" ]
then
	export LD_LIBRARY_PATH=.
	export LD_PRELOAD=./libmalloc.so
else
	export DYLD_LIBRARY_PATH=.
	export DYLD_INSERT_LIBRARIES=libmalloc.so
	export DYLD_FORCE_FLAT_NAMESPACE=1
fi

$@
