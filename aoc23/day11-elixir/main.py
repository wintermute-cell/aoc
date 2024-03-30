import sys

def main():
	symbol_positions = [
        (x, y) for y,
        line in enumerate(sys.stdin) for x,
        symbol in enumerate(line) if symbol == "#"
    ];

	width  = max(symbol_positions, key = lambda s: s[0])[0] + 1;
	height = max(symbol_positions, key = lambda s: s[1])[1] + 1;

	cols = [1000000 - 1] * width;
	rows = [1000000 - 1] * height

	for symbol in symbol_positions:
		cols[symbol[0]] = 0
		rows[symbol[1]] = 0
	column_map = [sum(cols[:i + 1]) for i in range(len(cols))]
	row_map = [sum(rows[:i + 1]) for i in range(len(rows))]

	symbols = [(x + column_map[x], y + row_map[y]) for x, y in symbol_positions]

	result = sum(
        abs(symbols[i][0] - symbols[j][0]) +
            abs(symbols[i][1] - symbols[j][1])
        for i in range(len(symbols))
        for j in range(i + 1, len(symbols)))

	print(result)

if __name__ == "__main__":
	main()
