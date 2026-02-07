# --- Configuration ---
CXX      := clang++
TARGET   := app
INPUT    := in

# --- Compiler Flags ---
FLAGS    := -std=c++17 -O2 -DLOCAL -DDBG_MACRO_NO_WARNING

# --- Rules ---
.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(TARGET).cpp
	@echo "🔨 Building."
	@$(CXX) $(FLAGS) $< -o $@

run: $(TARGET)
	@echo "=== Output ==="
	@./$(TARGET) < $(INPUT)
	@echo "=============="
	@echo "Execution Stats:"
	@time -p ./$(TARGET) < $(INPUT) > /dev/null

clean:
	@rm -f $(TARGET)
	@echo "🗑️ Cleaned."

