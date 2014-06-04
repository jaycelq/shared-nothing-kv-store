START=$(date +%s)
./dbclient -n 4 -k 25000 -c 1 -l 10  &
./dbclient -n 4 -k 25000 -c 1 -l 10  &
./dbclient -n 4 -k 25000 -c 1 -l 10  &
./dbclient -n 4 -k 25000 -c 1 -l 10  &
wait
END=$(date +%s)
DIFF=$(( $END - $START ))
echo "It took $DIFF seconds"
