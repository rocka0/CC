CPP_EXECUTABLE_NAME = app
CPP_FILE = $(CPP_EXECUTABLE_NAME).cpp
CPP_FLAGS = -std=c++17 -DLOCAL -Wall -Wextra -O2 -Wshadow -Wfloat-equal -Wconversion

all: build

build: $(CPP_FILE)
	@g++ $(CPP_FLAGS) $(CPP_FILE) -o $(CPP_EXECUTABLE_NAME)

run: build
	@time -p ./$(CPP_EXECUTABLE_NAME) < in
	@rm -f $(CPP_EXECUTABLE_NAME)
