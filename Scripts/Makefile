CXX      := clang++
TARGET   := app
SRC      := $(TARGET).cpp
INPUT    := in

BASE_FLAGS := -std=c++17 -DLOCAL -DDBG_MACRO_NO_WARNING -Wall -Wextra -Wshadow -Wconversion

DEBUG_FLAGS := -O2 -g -fsanitize=address -fsanitize=undefined \
               -fno-omit-frame-pointer -fno-sanitize-recover=all \
               -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC

FAST_FLAGS  := -O3 -march=native -mtune=native -funroll-loops -ffast-math

.PHONY: all build fast run clean

all: build

build: $(SRC)
	@echo "🔨 Compiling $(TARGET) [DEBUG MODE]..."
	@$(CXX) $(BASE_FLAGS) $(DEBUG_FLAGS) $(SRC) -o $(TARGET)

fast: $(SRC)
	@echo "🚀 Compiling $(TARGET) [FAST MODE]..."
	@$(CXX) $(BASE_FLAGS) $(FAST_FLAGS) $(SRC) -o $(TARGET)

run: 
	@if [ ! -f $(TARGET) ]; then $(MAKE) build; fi
	@echo "--- Execution ---"
	@./$(TARGET) < $(INPUT)
	@echo "-----------------"
	@echo "Time statistics:"
	@time -p ./$(TARGET) < $(INPUT) > /dev/null

clean:
	@rm -f $(TARGET)
	@echo "🗑️  Cleaned up binaries."

