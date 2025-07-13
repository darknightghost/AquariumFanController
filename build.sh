#! /bin/bash

PROJECT_DIR="$(dirname "$(realpath $0)")"
cd "${PROJECT_DIR}"
mkdir -p .build
cd .build
cmake ../firmware/ && cmake --build .
exit $?
