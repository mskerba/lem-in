#!/bin/bash
make > /dev/null 2>&1
# Function to generate a test map
generate_map() {
  local map_file=$1
  ./generator_linux "$generator_flag" > "$map_file"
}

# Function to get the required number of lines
get_required_lines() {
  local map_file=$1
  cat "$map_file" | grep "Here is the number of lines required" | cut -d ':' -f2 | tr -d ' ' | head -n 1
}

# Function to get the actual number of lines
get_actual_lines() {
  local map_file=$1
  ./lem-in "$map_file" | grep 'L' | wc -l
}

# Function to run a single test
run_test() {
  local i=$1
  local map_file=$2

  local required_lines actual_lines
  required_lines=$(get_required_lines "$map_file")
  actual_lines=$(get_actual_lines "$map_file")

  if [ "$actual_lines" -le "$required_lines" ]; then
    echo -e "\e[32mRun $i: OK\e[0m (Required: $required_lines, Actual: $actual_lines)"
    return 0
  else
    echo -e "\e[31mRun $i: KO\e[0m (Required: $required_lines, Actual: $actual_lines)"
    return 1
  fi
}

# Main script logic
main() {
  local success_count=0
  local total_tests=100
  local map_file="./maps/one_map_test"

  for i in $(seq 1 $total_tests); do
    generate_map "$map_file"
    if run_test "$i" "$map_file"; then
      success_count=$((success_count + 1))
    fi
  done

  echo -e "\n\e[34mTests Passed: $success_count/$total_tests\e[0m"
}

# Check if an argument is provided
if [ $# -lt 1 ]; then
  echo "Error: Missing arguments!"
  echo "Usage: $0 <generator flag>"
  echo "Options:"
  echo "  --help"
  echo "  --flow-one"
  echo "  --flow-ten"
  echo "  --flow-thousand"
  echo "  --big"
  echo "  --big-superposition"
  exit 1
fi

# Store the argument
generator_flag=$1

# Check if the argument is one of the valid options
case $generator_flag in
  --help)
    echo "Help selected. Displaying usage information..."
    ;;
  --flow-one)
    echo "Flow One selected."
    ;;
  --flow-ten)
    echo "Flow Ten selected."
    ;;
  --flow-thousand)
    echo "Flow Thousand selected."
    ;;
  --big)
    echo "Big map selected."
    ;;
  --big-superposition)
    echo "Big Superposition map selected."
    ;;
  *)
    echo "Error: Invalid argument '$generator_flag'."
    echo "Usage: $0 <generator flag>"
    echo "Options:"
    echo "  --help"
    echo "  --flow-one"
    echo "  --flow-ten"
    echo "  --flow-thousand"
    echo "  --big"
    echo "  --big-superposition"
    exit 1
    ;;
esac

# Execute the main function
main