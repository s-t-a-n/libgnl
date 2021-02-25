#!/bin/sh

name=gnl
srcs=src
includes=inc

cmake_version=3.11
cm_f=./CMakeLists.txt

# clear file
cat /dev/null > $cm_f

# project details
cat>>$cm_f<<EOF
cmake_minimum_required(VERSION $cmake_version)
project($name)
EOF

# add src files to static target
echo "add_library($name" STATIC >> $cm_f
find ./src -iregex '.*\.\(c\|cpp\)$' | cut -d/ -f2- >> $cm_f
#find ./inc -iregex '.*\.\(c\|h\)$' | cut -d/ -f2- >> $cm_f
echo ")" >> $cm_f

# add includes folder to target
cat>>$cm_f<<EOF
target_include_directories($name
    PUBLIC
		$includes
)
EOF
