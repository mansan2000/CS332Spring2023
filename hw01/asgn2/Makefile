FILE = asgn2

build: $(FILE).c
	# the next line is only needed if compiling outside Vulcan
	#gcc -Wall -g $(FILE).c -o $(FILE) -lm -fno-pie -no-pie
	# use this command to compile on Vulcan (enabled by default)
	gcc -Wall -g $(FILE).c -o $(FILE) -lm

.PHONY: db

db:
	gdb -tui $(FILE)

run:
	./$(FILE)