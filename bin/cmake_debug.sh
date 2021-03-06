#!/bin/bash

SNAME="`readlink -f $0`"
DIRNAME="`dirname "$SNAME"`"

# FIXME: remove REUSEADDR_HACK

cmake \
-DCMAKE_BUILD_TYPE=Debug \
-DREDFISH_CLIENT_LIB=fishc_stub \
-DREDFISH_SO_REUSEADDR_HACK:BOOL=ON \
-DREDFISH_BUILD_JNI:BOOL=ON \
-DCTEST_MEMORYCHECK_COMMAND:FILEPATH=/usr/bin/valgrind \
-DCTEST_MEMORYCHECK_COMMAND_OPTIONS:STRING="--trace-children=yes \
--quiet --tool=memcheck --leak-check=yes --show-reachable=yes \
--num-callers=100 --verbose --demangle" \
${@} \
"${DIRNAME}/.."
