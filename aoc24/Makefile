CXX := g++
CXXFLAGS := -std=c++20 -Wall -Wextra -O3 -static -flto -funroll-loops
LDFLAGS := 

OUTPUT := advent

.PHONY: all
all:
	@echo "Usage: make <day> (e.g., make 01)"

# target for each day
%:
	$(MAKE) build DAY=$@

.PHONY: build
build:
	@if [ -f "day$(DAY)/solution.cpp" ]; then \
		echo "Compiling for day $(DAY)..."; \
		$(CXX) $(CXXFLAGS) main.cpp day$(DAY)/solution.cpp -o $(OUTPUT); \
		echo "Built: ./$(OUTPUT)"; \
	else \
		echo "Error: solution file for day $(DAY) not found!"; \
		exit 1; \
	fi

.PHONY: clean
clean:
	@rm -f $(OUTPUT)
	@echo "Cleaned output binary."
