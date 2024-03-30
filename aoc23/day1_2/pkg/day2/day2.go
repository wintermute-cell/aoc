package day2

import (
	"bytes"
	"fmt"
	"math"
	"os"
	"strconv"

	//"strconv"
	"sync"
)

func isDigit(b byte) bool {
	return b >= '0' && b <= '9'
}

var maxMap map[byte]int = map[byte]int{
	byte('r'): 12,
	byte('g'): 13,
	byte('b'): 14,
}

func processLines(lines [][]byte, sum *int, wg *sync.WaitGroup, mu *sync.Mutex) {
	defer wg.Done()
	localSum := int(0)

	for _, game := range lines {
        gameIsBad := false
		g := bytes.Split(game, []byte(":"))
		gameId := g[0][5:]
		gameData := g[1]

		hands := bytes.Split(gameData, []byte(";"))

        handloop:
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
                if maxMap[color] < amount {
                    gameIsBad = true
                    break handloop
                }
			}
		}
        if !gameIsBad {
            asNum, err := strconv.Atoi(string(gameId))
            if err != nil {
                panic(err)
            }
            localSum += asNum
        }
	}

	mu.Lock()
	*sum += localSum
	mu.Unlock()
}

func Solve() {
	inBuffer, err := os.ReadFile("input.txt")
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
