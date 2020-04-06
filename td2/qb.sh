SCHED_RR=2

for loop in 1 2 3 4
do
    for task in 1 2 3 4 5 6
    do
        $(dirname "$0")/qb ${loop}0000000 ${task} $SCHED_RR
    done
done