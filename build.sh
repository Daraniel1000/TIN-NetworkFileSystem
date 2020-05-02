#!/bin/bash

print_usage()
{
    echo
    echo "Poprawne wywołanie to : $0 target"
    echo
    echo "target - projekt do zbudowania"
}

if ! [ "$#" -eq 1 ]
then
    echo "Potrzeba dokładnie jednego argumentu"
    print_usage
    exit 1
fi

target="$1"
build_dir="cmake-build"

mkdir -p "$build_dir"
cd "$build_dir"
cmake ..
make "$target"