#!/bin/bash

if [ $# -eq 0 ]; then
  echo "Usage: $0 <search_pattern>"
  exit 1
fi

search_files() {
  local dir="$1"
  local pattern="$2"

  for file in "$dir"/*; do
    if [ -f "$file" ]; then
      if [[ "$pattern" =~ ^/.* ]]; then
        # Передано регулярное выражение
        if [[ "$(basename "$file")" =~ $pattern ]]; then
          sed -E 's/(^|\.|\?|\!)([[:space:]])*([a-z])/\1 \U\3/g' "$file"
        fi
      else
        # Передано имя файла
        if [[ "$(basename "$file")" == $pattern ]]; then
          sed -E 's/(^|\.|\?|\!)([[:space:]])*([a-z])/\1 \U\3/g' "$file"
        fi
      fi
    elif [ -d "$file" ]; then
      search_files "$file" "$pattern"
    fi
    echo ""
  done
}

current_dir=$(pwd)  

for arg in "$@"; do
  search_files "$current_dir" "$arg"
done