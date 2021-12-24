#!/bin/sh

echo "method,n_index,size,search_scale,level,pos_percent,insert_time,search_time" > result.csv

for method in "Treap" "SkipList" "LinearSearch" "BinarySearch" "Hash"
do
    for idx in $(seq 10 20)
    do
        for time in $(seq 1 5)
        do
            if [ "$method" = "SkipList" ]
            then
                for pct in 0.1 0.5 0.9
                do
                ./main.exe -n_index $idx -search_scale 100000 -method $method -save result.csv -pos_percent $pct -max_level 10
                done
            else
                ./main.exe -n_index $idx -search_scale 100000 -method $method -save result.csv
            fi
        done

        rm source.txt
    done
done


