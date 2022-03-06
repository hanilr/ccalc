# CALCULATOR IN C FOR NEWBIES MAKEFILE #

CC = gcc # C COMPLIER
main = src/ccalc.c # MAIN FILE

ifeq ($(OS),Windows_NT) # IF OPERATING SYSTEM WINDOWS
	output = ccalc.exe
	delete = del
else # IF OPERATING SYSTEM LINUX, UNIX OR OTHER OPERATING SYSTEM
	output = ccalc
	delete = rm
endif

.PHONY: run clean # MAKE COMMANDS

run: $(main) # IF MAIN FILE IS EXIST THEN EXECUTE THE COMMAND
	$(CC) $(main) -o $(output)

clean: $(output)
	$(delete) $(output)

# MADE BY @hanilr #