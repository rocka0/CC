CPP_EXECUTABLE_NAME = app
CPP_FILE = $(CPP_EXECUTABLE_NAME).cpp
CPP_FLAGS = -std=c++17 -O2 -DLOCAL

all: build

build: $(CPP_FILE)
	@time -f "Build time: %E seconds." g++ $(CPP_FLAGS) $(CPP_FILE) -o $(CPP_EXECUTABLE_NAME)

run: build
	@time -f "Run time: %E seconds." ./$(CPP_EXECUTABLE_NAME) < in

clean:
	@rm -f $(CPP_EXECUTABLE_NAME)