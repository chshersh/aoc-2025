#!/usr/bin/env bash
set -euox pipefail

if [[ $# -ne 2 ]]; then
    echo "Usage: ./run.sh <day-number> <input-file>"
    echo "Example: ./run.sh 6 input.txt"
    exit 1
fi

DAY=$(printf "day%02d" "$1")   # 1 → day01, 6 → day06
FILE="$2"

# Build first
cmake --build --preset default --target "${DAY}"

# Run executable
"./build/${DAY}/${DAY}" "${DAY}/${FILE}"
