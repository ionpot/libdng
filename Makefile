.PHONY: build
build:
	cmake --build build

.PHONY: cfiles
cfiles: CFILES := $(shell cd src && echo *.c)
cfiles:
	@sed -i '' "s/\(^set(CFILES\)\(.*\)/\1 $(CFILES))/" src/CMakeLists.txt

.PHONY: clean
clean:
	rm -rf build

.PHONY: conf
conf:
	cmake -S . -B build
