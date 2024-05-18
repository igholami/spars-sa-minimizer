cmake -S .. .
make

if [[ "$1" == "build" ]]; then
  echo "Building index"
  for ratio in "0.25" "0.5" "0.75" "1.0"; do
#  for ratio in "0.25"; do
    for type in "random_order" "frequency" "lexicographical"; do
#    for type in "random_order"; do
      for i in "1 10" "3 10" "5 10" "1 6" "3 6"; do
#      for i in "1 10"; do
        a=( $i )
        k=${a[0]}
        w=${a[1]}
        echo "Building ${type}_${ratio}_${k}_${w}_index.bin"
        ./buildsa ../data/test_input/salmonella.fa $ratio $k $w $type files/${type}_${ratio}_${k}_${w}_index.bin
      done
    done
    echo "Building none_${ratio}_index.bin"
    ./buildsa ../data/test_input/salmonella.fa $ratio 0 0 none files/none_${ratio}_index.bin
  done
fi

echo "Querying index"
  for ratio in "0.25" "0.5" "0.75" "1.0"; do
#  for ratio in "0.25"; do
    for type in "random_order" "frequency" "lexicographical"; do
#    for type in "random_order"; do
      for i in "1 10" "3 10" "5 10" "1 6" "3 6"; do
#      for i in "1 10"; do
      a=( $i )
      k=${a[0]}
      w=${a[1]}
      echo "Querying ${type}_${ratio}_${k}_${w}_index.bin"
      ./querysa files/${type}_${ratio}_${k}_${w}_index.bin ../data/test_input/reads_sal_sub.fq minimizer files/${type}_${ratio}_${k}_${w}_out.txt
    done
  done
  echo "Querying none_${ratio}_index.bin"
  ./querysa files/none_${ratio}_index.bin ../data/test_input/reads_sal_sub.fq none files/none_${ratio}_out.txt
done
