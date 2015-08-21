CURRENT_DIR = `pwd`
CPP_COMPILE_FLAG = -x c++ -std=c++11 -stdlib=libc++
CPP_LINK_FLAG = -framework SDL2_image -framework SDL2

all: build

run: build
	${CURRENT_DIR}/build

build: main.o
	clang -o build main.o ${CPP_LINK_FLAG}

main.o: main.cpp header.o
	clang -c main.cpp ${CPP_COMPILE_FLAG}

header.o: header.hpp header.cpp
	clang -c header.hpp header.cpp ${CPP_COMPILE_FLAG}

clean: build
	rm ${CURRENT_DIR}/build
	rm ${CURRENT_DIR}/*.o
	rm ${CURRENT_DIR}/*.gch

