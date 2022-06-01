FLAGS := -Wall -Werror -Wextra

all: build

build: exe

clean:
	@rm -rf *.o exe exe.dSYM/

exe: main.c
	@gcc $(FLAGS) main.c -o exe
