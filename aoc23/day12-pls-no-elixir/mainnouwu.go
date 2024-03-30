package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

func search(symbols string, nums []int) int {
	if len(nums) == 0 {
		if strings.Contains(symbols, "#") {
			return 0
		}
		return 1
	} else if symbols == "" {
		return 0
	}
	result := 0
	pivotPoint := len(nums) / 2
	leftSideNumbers := nums[:pivotPoint]
	middleNumber := nums[pivotPoint]
	rightSideNumbsers := nums[pivotPoint+1:]
	for _, split := range splitSymbolLine(symbols, middleNumber) {
		// check if the proposed split is valid
		leftString, midStr, rightString := split[0], split[1], split[2]
		if strings.Contains(midStr, ".") {
			continue
		}
		if len(leftString) > 0 && leftString[len(leftString)-1] == '#' {
			continue
		}
		if len(rightString) > 0 && rightString[0] == '#' {
			continue
		}
		if len(leftString) > 0 {
			leftString = leftString[:len(leftString)-1]
		}
		if len(rightString) > 0 {
			rightString = rightString[1:]
		}
		// RECURSE DEEPER INTO THAT SHIT WITH DIVIDE AND CONQUER
		// left side fucker
		leftSideCombinations := search(leftString, leftSideNumbers)
		if leftSideCombinations == 0 {
			continue
		}
		// right side
		rightSideCombinations := search(rightString, rightSideNumbsers)
		result += leftSideCombinations * rightSideCombinations
	}
	return result
}

func splitSymbolLine(currentSymbols string, midLen int) [][3]string {
	// build all possible splits around this middle
	var res [][3]string
	for i := 0; i < len(currentSymbols); i++ {
		// cut off left side
		left := currentSymbols[:i]

		// rest is for right and mid
		rightAndMid := currentSymbols[i:]

		// we've gone too far, no more space for middle part
		if len(rightAndMid) < midLen {
			break
		}

		// take out the middle part
		mid := rightAndMid[:midLen]
		right := rightAndMid[midLen:]

		// use this as split
		res = append(res, [3]string{left, mid, right})
	}
	return res
}

func unfold(numsAsStrings []string, symbols string, multiplier int) ([]string, string) {
	newNums := []string{}
	for i := 0; i < multiplier; i++ {
		newNums = append(newNums, numsAsStrings...)
	}
	newSymbols := ""
	for i := 0; i < multiplier; i++ {
		if i == 0 {
			newSymbols += symbols
		} else {
			newSymbols += "?" + symbols
		}
	}
	return newNums, newSymbols
}

func main() {
	scanner := bufio.NewScanner(os.Stdin)

	sum := 0
	for scanner.Scan() {
		line := scanner.Text()
		parts := strings.Fields(line)
		symbols := parts[0]
		cuntsAsStrings := strings.Split(parts[1], ",")
		cuntsAsStrings, symbols = unfold(cuntsAsStrings, symbols, 5)
		var cunts []int
		// why does go do this to me, why no higher order map()
		for _, c := range cuntsAsStrings {
			num, _ := strconv.Atoi(c)
			cunts = append(cunts, num)
		}
		res := search(symbols, cunts)
		sum += res
	}
	fmt.Println("Total = ", sum)
}
