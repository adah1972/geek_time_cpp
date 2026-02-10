#!/bin/bash

# Get script directory
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
BUILD_DIR="${SCRIPT_DIR}/build"

# Check if build directory exists
if [ ! -d "$BUILD_DIR" ]; then
    echo "Error: build directory not found. Please compile the project first."
    echo "Example: mkdir -p build && cd build && cmake .. && make -j$(nproc)"
    exit 1
fi

# Get all chapter directories containing executables
chapters=$(find -L "$BUILD_DIR" -maxdepth 1 -type d -regex '.*/[0-9][0-9]' | sort)

if [ -z "$chapters" ]; then
    echo "Error: No chapter directories found in build folder."
    exit 1
fi

while true; do
    echo "========================================"
    echo "    Modern C++ in Action"
    echo "    OS: $OSTYPE"
    echo "========================================"
    echo ""

    # List all chapters
    echo "Available Chapters:"
    chapter_list=()
    all_chapters=($chapters)

    for ch in "${all_chapters[@]}"; do
        ch_name=$(basename "$ch")
        executables=$(find "$ch" -maxdepth 1 -perm -001 -type f ! -name "*.cmake" ! -name "Makefile" ! -name "*.so*" ! -name ".*")
        if [ -n "$executables" ]; then
            printf "  Chapter %2s\n" "$ch_name"
            chapter_list+=("$ch_name")
        fi
    done

    echo ""
    read -p "Enter chapter number (e.g. 19, 'q' to quit): " ch_choice

    if [[ "$ch_choice" == "q" ]]; then
        exit 0
    fi

    found=false
    for ch_name_item in "${chapter_list[@]}"; do
        if [[ "$ch_choice" == "$ch_name_item" || "$ch_choice" == $((10#$ch_name_item)) ]]; then
            found=true
            selected_ch_name="$ch_name_item"
            break
        fi
    done

    if [ "$found" = false ]; then
        echo "Invalid chapter or no executables found."
        sleep 1
        continue
    fi

    selected_ch="${BUILD_DIR}/${selected_ch_name}"
    ch_name=$(basename "$selected_ch")

    while true; do
        echo ""
        echo "--- Chapter $ch_name Executables ---"
        execs=$(find "$selected_ch" -maxdepth 1 -perm -001 -type f ! -name "*.cmake" ! -name "Makefile" ! -name "*.so*" ! -name ".*" | sort)

        exec_list=()
        j=1
        for ex in $execs; do
            ex_name=$(basename "$ex")
            printf "  %2d) %s\n" "$j" "$ex_name"
            exec_list+=("$ex")
            ((j++))
        done

        echo ""
        read -p "Select program index ('q' for back, 'qq' to quit): " ex_choice

        if [[ "$ex_choice" == "qq" ]]; then
            exit 0
        fi

        if [[ "$ex_choice" == "q" ]]; then
            break
        fi

        if ! [[ "$ex_choice" =~ ^[0-9]+$ ]] || [ "$ex_choice" -lt 1 ] || [ "$ex_choice" -ge "$j" ]; then
            echo "Invalid selection."
            continue
        fi

        selected_ex="${exec_list[$((ex_choice-1))]}"
        ex_name=$(basename "$selected_ex")

        echo ""
        echo ">>> Running: $ex_name"
        echo "----------------------------------------"
        "$selected_ex"
        echo "----------------------------------------"
        echo ">>> Finished."
        
        read -p "Press Enter to continue..."
    done
done
