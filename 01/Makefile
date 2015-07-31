CURRENT_DIR = `pwd`

all: build

run: build
	./build ${CURRENT_DIR}/../test/static/bili.mp4

build: main.c
	clang -o build main.c -lavformat -lavcodec -lavutil -lswscale

clean:
	rm ${CURRENT_DIR}/*.ppm
	rm ${CURRENT_DIR}/build
