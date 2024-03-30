package main

import (
	d2p1 "aoc23/pkg/day2"
	//d2p2 "aoc23/pkg/day2/part2"
	"fmt"
	"time"
)


func main() {
    start := time.Now()
    d2p1.Solve()
    //d2p2.Solve()
    elapsed := time.Since(start)

    fmt.Println(fmt.Sprintf("Took: %s", elapsed))
    fmt.Println(elapsed.Microseconds())
}
