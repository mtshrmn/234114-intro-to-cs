RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m' # No color
for file in $(ls src/*.c); do
  hw_idx=$(echo $file | grep -Po '\d+' | head -1)
  question_id=$(echo $file | grep -Po '\d+' | tail -1)
  test_inputs="tests/HW${hw_idx}/hw${hw_idx}q${question_id}in*.txt"
  file=bin/hw${hw_idx}q${question_id} 
  if [ ! -f "$file" ]; then
    echo "binary file \`hw${hw_idx}q${question_id}\` not found, skipping."
      continue
  fi
  for test in $(seq 1 $(ls $test_inputs 2> /dev/null | wc -w)); do
    input="tests/HW${hw_idx}/hw${hw_idx}q${question_id}in${test}.txt"
    output="tests/HW${hw_idx}/hw${hw_idx}q${question_id}out${test}.txt"
    printf "$input - "
     ./$file < $input | diff --suppress-common-lines --strip-trailing-cr --ignore-trailing-space --color=always $output - > /dev/null
    if [ $? -eq 0 ]; then
      printf "${GREEN}PASS${NC}\n"
    else
      printf "${RED}FAIL${NC}\n"
     ./$file < $input | diff --suppress-common-lines --strip-trailing-cr --ignore-trailing-space --color=always $output -
     echo "--------------------------------------------------------"
    fi
  done
done
