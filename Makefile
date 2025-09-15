.PHONY: build run

build:
	meson setup build
	ninja -C build

run: build build
	./build/mosh
