.PHONY: build run

all: test run

build:
	meson setup build
	ninja -C build -v

run: build
	./build/mosh

test: build
	meson test -C build --print-errorlogs

debug:
	meson setup build --buildtype=debug
	ninja -C build -v

clean:
	rm -r build/ .cache/
