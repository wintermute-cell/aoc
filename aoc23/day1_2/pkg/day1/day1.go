package day1

import (
	"bytes"
	"fmt"
	"io/ioutil"
	"strconv"
	"sync"
)

func isDigit(b byte) bool {
	return b >= '0' && b <= '9'
}

func processLines(lines [][]byte, sum *int64, wg *sync.WaitGroup, mu *sync.Mutex) {
	defer wg.Done()
	localSum := int64(0)

	for _, line := range lines {
		var firstDigit, lastDigit byte

		// Find first digit
		for _, b := range line {
			if isDigit(b) {
				firstDigit = b
				break
			}
		}

		// Find last digit
		for i := len(line) - 1; i >= 0; i-- {
			if isDigit(line[i]) {
				lastDigit = line[i]
				break
			}
		}

		if firstDigit != 0 && lastDigit != 0 {
			combined := string([]byte{firstDigit, lastDigit})
			asNum, err := strconv.ParseInt(combined, 10, 64)
			if err == nil {
				localSum += asNum
			}
		}
	}

	mu.Lock()
	*sum += localSum
	mu.Unlock()
}

func Solve() {
	inBuffer, err := ioutil.ReadFile("day1-input.txt")
	if err != nil {
		fmt.Println(err)
		return
	}

	lines := bytes.Split(inBuffer, []byte("\n"))
	var wg sync.WaitGroup
	var mu sync.Mutex
	var sum int64

	batchSize := len(lines) / 8
	for i := 0; i < len(lines); i += batchSize {
		end := i + batchSize
		if end > len(lines) {
			end = len(lines)
		}

		wg.Add(1)
		go processLines(lines[i:end], &sum, &wg, &mu)
	}

	wg.Wait()
	fmt.Println(sum)
}
