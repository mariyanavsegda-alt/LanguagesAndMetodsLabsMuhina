!/bin/bash

bubble_sort() {
    local -n arr_ref=$1 
    local n=${#arr_ref[@]}
    
    for ((i = 0; i < n - 1; i++)); do
        for ((j = 0; j < n - i - 1; j++)); do
            if [ ${arr_ref[j]} -gt ${arr_ref[j+1]} ]; then
                local temp=${arr_ref[j]}
                arr_ref[j]=${arr_ref[j+1]}
                arr_ref[j+1]=$temp
            fi
        done
    done
}

if [ $# -eq 0 ]; then
    echo "Использование: $0 <число1> <число2> ..."
    exit 1
fi
numbers=()

for arg in "$@"; do
    if ! [[ "$arg" =~ ^-?[0-9]+$ ]]; then
        echo "Ошибка: '$arg' не является целым числом"
        exit 1
    fi
    numbers+=("$arg")
done

bubble_sort numbers

echo -n "Отсортированный массив: "
printf "%d " "${numbers[@]}"
echo

exit 0