# --- Configuration ---
CXX      := clang++
TARGET   := app
INPUT    := in

# --- Compiler Flags ---
CXXFLAGS := -std=c++17 -O2 -DLOCAL -DDBG_MACRO_NO_WARNING -fsanitize=address,undefined -fno-omit-frame-pointer

# --- Rules ---
.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(TARGET).cpp
	@echo "🔨 Building..."
	@$(CXX) $(CXXFLAGS) $< -o $@
	@echo "✅ Build complete."

run: $(TARGET)
	@echo "=== Output & Execution Stats ==="
	@time ./$(TARGET) < $(INPUT)
	@echo "================================"

clean:
	@rm -f $(TARGET)
	@echo "🗑️ Cleaned."

