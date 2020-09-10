.PHONY: build
build:
	cmake --build build

.PHONY: cfiles
cfiles: CFILES := $(shell cd src && echo *.c)
cfiles: TMP := $(shell mktemp)
cfiles: TXT := src/CMakeLists.txt
cfiles:
	sed "s/\(^set(CFILES\)\(.*\)/\1 $(CFILES))/" $(TXT) >$(TMP)
	mv $(TMP) $(TXT)
	chmod 644 $(TXT)

.PHONY: clean
clean:
	rm -rf build

.PHONY: conf
conf:
	cmake -S . -B build
