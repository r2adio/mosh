.PHONY: build run

all: test run

build:
	meson setup build
	ninja -C build -v

run: build
	./build/mosh

test: build
	meson test -C build --print-errorlogs

clean:
	rm -r build/ .cache/
