package day2

import (
	"bytes"
	"fmt"
	"io/ioutil"
	"math"
	"strconv"

	//"strconv"
	"sync"
)

func isDigit(b byte) bool {
	return b >= '0' && b <= '9'
}

func processLines(lines [][]byte, sum *int, wg *sync.WaitGroup, mu *sync.Mutex) {
	defer wg.Done()
	localSum := int(0)
    var minMap map[byte]int = make(map[byte]int);

	for _, game := range lines {

        // reset mins
        minMap[byte('r')] =  0
        minMap[byte('g')] =  0
        minMap[byte('b')] =  0

		g := bytes.Split(game, []byte(":"))
		gameData := g[1]

		hands := bytes.Split(gameData, []byte(";"))

		for _, hand := range hands {
			cubeSets := bytes.Split(hand, []byte(","))
			for _, set := range cubeSets {
				//set = bytes.Trim(set, " ") // instead of this we just ignore the 0th index later
				cn := bytes.Split(set, []byte(" "))
				amount, err := strconv.Atoi(string(cn[1]))
                if err != nil {
                    panic(err)
                }
				color := cn[2][0] // r, g, b
                if minMap[color] < amount {
                    minMap[color] = amount
                }
			}
		}
        localSum += (minMap[byte('r')] * minMap[byte('g')] * minMap[byte('b')])
	}

	mu.Lock()
	*sum += localSum
	mu.Unlock()
}

func Solve() {
	inBuffer, err := ioutil.ReadFile("input.txt")
	if err != nil {
		fmt.Println(err)
		return
	}

	lines := bytes.Split(inBuffer, []byte("\n"))
	lines = lines[0 : len(lines)-1]
	var wg sync.WaitGroup
	var mu sync.Mutex
	var sum int

	batchSize := int(math.Max(1, float64(len(lines)/8)))
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
