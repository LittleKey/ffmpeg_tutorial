CURRENT_DIR = `pwd`

all: build

run: build
	${CURRENT_DIR}/build 

build: main.c
	clang -o ${CURRENT_DIR}/build ${CURRENT_DIR}/main.c -isystem /usr/local/include/SDL2 -lsdl2

clean:
	rm ${CURRENT_DIR}/build

