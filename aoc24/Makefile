CXX := g++
CXXFLAGS := -std=c++20 -Wall -Wextra -static -O1 -g3
#-O3 -static -flto -funroll-loops
LDFLAGS := 
#-lGL -ldl -lglfw
MYLIB_DIR := -I./lib

# === OPENGL
#INCLUDE_DIR := -I./include
#GLAD_SRC := ./src/glad.c
BEAR := bear --
# === END OPENGL

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
		$(BEAR) $(CXX) $(CXXFLAGS) $(INCLUDE_DIR) $(MYLIB_DIR) $(GLAD_SRC) main.cpp day$(DAY)/solution.cpp -o $(OUTPUT) $(LDFLAGS); \
		echo "Built: ./$(OUTPUT)"; \
	else \
		echo "Error: solution file for day $(DAY) not found!"; \
		exit 1; \
	fi

.PHONY: clean
clean:
	@rm -f $(OUTPUT)
	@echo "Cleaned output binary."
