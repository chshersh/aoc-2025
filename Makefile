.PHONY: run-day01
run-day01:
	cmake --build --preset default
	./build/day01/day01 $(FILE)

.PHONY: run-day02
run-day02:
	cmake --build --preset default
	./build/day02/day02 $(FILE)
