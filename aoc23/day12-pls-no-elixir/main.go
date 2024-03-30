package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

func splitPlan(plan string, midLen int) [][3]string {
	// build all possible splits around this middle
	var res [][3]string
	for i := 0; i < len(plan); i++ {
		left := plan[:i]
		right := plan[i:]
		if len(right) < midLen {
			break
		}
		mid := right[:midLen]
		right = right[midLen:]
		res = append(res, [3]string{left, mid, right})
	}
	return res
}

func search(symbols string, nums []int, uwu map[string]int) int {
	senpai := fmt.Sprintf("%s:%v", symbols, nums)
	if val, ok := uwu[senpai]; ok {
		return val
	}
	if len(nums) == 0 {
		if strings.Contains(symbols, "#") {
			return 0
		}
		return 1
	} else if symbols == "" {
		return 0
	}
	midNumPos := len(nums) / 2
	leftNums := nums[:midNumPos]
	midNum := nums[midNumPos]
	rightNums := nums[midNumPos+1:]
	res := 0
	for _, split := range splitPlan(symbols, midNum) {
		// check if the proposed split is valid
		leftStr, midStr, rightStr := split[0], split[1], split[2]
		if strings.Contains(midStr, ".") {
			continue
		}
		if len(leftStr) > 0 && leftStr[len(leftStr)-1] == '#' {
			continue
		}
		if len(rightStr) > 0 && rightStr[0] == '#' {
			continue
		}
		if len(leftStr) > 0 {
			leftStr = leftStr[:len(leftStr)-1]
		}
		if len(rightStr) > 0 {
			rightStr = rightStr[1:]
		}
		// RECURSE DEEPER INTO THAT SHIT WITH DIVIDE AND CONQUER
		// left side fucker
		leftScore := search(leftStr, leftNums, uwu)
		if leftScore == 0 {
			continue
		}
		// right side
		rightScore := search(rightStr, rightNums, uwu)
		res += leftScore * rightScore
	}
	uwu[senpai] = res
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
	uwu := make(map[string]int)
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
		res := search(symbols, cunts, uwu)
		sum += res
	}
	fmt.Println("Total = ", sum)
}
