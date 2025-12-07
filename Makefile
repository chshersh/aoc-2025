.PHONY: run-day01
run-day01:
	cmake --build --preset default
	./build/day01/day01 $(FILE)

.PHONY: run-day02
run-day02:
	cmake --build --preset default
	./build/day02/day02 $(FILE)

.PHONY: run-day03
run-day03:
	cmake --build --preset default
	./build/day03/day03 $(FILE)

.PHONY: run-day04
run-day04:
	cmake --build --preset default
	./build/day04/day04 $(FILE)

.PHONY: run-day05
run-day05:
	cmake --build --preset default
	./build/day05/day05 $(FILE)

.PHONY: run-day06
run-day06:
	cmake --build --preset default
	./build/day06/day06 $(FILE)
