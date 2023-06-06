#!/bin/bash

echo "SOURCES := \\" > make/sources.mk;
find src -type f -name '*.c' | awk '{print "\t" $0 " \\"}' >> make/sources.mk ;

echo "HEADERS := \\" > make/headers.mk;
find inc -type f -name '*.h' | awk '{print "\t" $0 " \\"}' >> make/headers.mk ;

echo "INCLUDE := \\" > make/include.mk;
find inc -type d | awk '{print "\t -I " $0 " \\"}' >> make/include.mk ;

