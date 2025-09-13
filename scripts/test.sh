#!/bin/bash

# Test script for Tchanz Ant Simulation
# Runs all test files and reports results

set -e

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Counters
TOTAL=0
PASSED=0
FAILED=0

# Test executable
EXECUTABLE="./projet"

# Check if executable exists
if [ ! -f "$EXECUTABLE" ]; then
    echo -e "${RED}Error: Executable '$EXECUTABLE' not found!${NC}"
    echo "Please build the project first: make"
    exit 1
fi

echo -e "${BLUE}========================================${NC}"
echo -e "${BLUE}   Tchanz Ant Simulation Test Suite    ${NC}"
echo -e "${BLUE}========================================${NC}"
echo

# Function to run a single test
run_test() {
    local test_file=$1
    local test_name=$(basename "$test_file" .txt)
    
    TOTAL=$((TOTAL + 1))
    
    echo -n "Testing $test_name... "
    
    # Run test with timeout
    if timeout 5s $EXECUTABLE "$test_file" > /dev/null 2>&1; then
        echo -e "${GREEN}PASSED${NC}"
        PASSED=$((PASSED + 1))
        return 0
    else
        echo -e "${RED}FAILED${NC}"
        FAILED=$((FAILED + 1))
        return 1
    fi
}

# Test categories
echo -e "${YELLOW}Running Configuration Tests...${NC}"
for test_file in tests/data/c*.txt; do
    if [ -f "$test_file" ]; then
        run_test "$test_file"
    fi
done

echo
echo -e "${YELLOW}Running Anthill Tests...${NC}"
for test_file in tests/data/f*.txt; do
    if [ -f "$test_file" ]; then
        run_test "$test_file"
    fi
done

echo
echo -e "${YELLOW}Running Integration Tests...${NC}"
for test_file in tests/data/t*.txt; do
    if [ -f "$test_file" ]; then
        run_test "$test_file"
    fi
done

echo
echo -e "${YELLOW}Running Special Tests...${NC}"
special_tests=(
    "tests/data/no_error_collector_move.txt"
    "tests/data/no_error_neighbours_anthill.txt"
    "tests/data/free_anthill.txt"
    "tests/data/wittwer.txt"
)

for test_file in "${special_tests[@]}"; do
    if [ -f "$test_file" ]; then
        run_test "$test_file"
    fi
done

# Memory leak test with valgrind (if available)
if command -v valgrind &> /dev/null; then
    echo
    echo -e "${YELLOW}Running Memory Leak Test...${NC}"
    echo -n "Memory check with valgrind... "
    
    if valgrind --leak-check=quick --quiet --error-exitcode=1 \
               $EXECUTABLE tests/data/f01.txt > /dev/null 2>&1; then
        echo -e "${GREEN}NO LEAKS${NC}"
    else
        echo -e "${RED}MEMORY LEAKS DETECTED${NC}"
    fi
fi

# Summary
echo
echo -e "${BLUE}========================================${NC}"
echo -e "${BLUE}              Test Summary              ${NC}"
echo -e "${BLUE}========================================${NC}"
echo -e "Total Tests: $TOTAL"
echo -e "Passed: ${GREEN}$PASSED${NC}"
echo -e "Failed: ${RED}$FAILED${NC}"

if [ $FAILED -eq 0 ]; then
    echo -e "${GREEN}All tests passed!${NC}"
    exit 0
else
    echo -e "${RED}Some tests failed!${NC}"
    exit 1
fi