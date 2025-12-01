.PHONY: run-day01
run-day01:
	cmake --build --preset default
	./build/day01/day01 $(FILE)
