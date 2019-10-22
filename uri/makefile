# Run all tests
problem := $(wildcard */.)

all: compile 

compile: $(problem)
$(problem):
	mkdir -p $@/.bin/
	g++ -std=c++11 $@/main.cpp -o $@/.bin/exe

test:
	@for f in $(problem); do ./test.sh $$f/; done

clean:
	@for f in $(problem); do rm -rf $$f/.bin/; done

.PHONY: all $(problem) 
