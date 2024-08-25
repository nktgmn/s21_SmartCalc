CFLAGS = -Wall -Wextra -Werror
GCOVFLAGS = -fprofile-arcs -ftest-coverage --coverage
TEST_FILES = ./Test/test.c ./Calculation/polish.c ./Calculation/credit.c

.PHONY: test gcov_report dist clang_check

all: install

install:
	mkdir build
	cd build && qmake ../View/Nik_Calc.pro && make

uninstall:
	rm -rf build

test:
	gcc $(CFLAGS) $(TEST_FILES) -lcheck -o ./Test/test
	./Test/test

gcov_report:
	mkdir -p gcov
	gcc $(CFLAGS) $(GCOVFLAGS) $(TEST_FILES) -lcheck -o ./gcov/gcov_test
	./gcov/gcov_test
	mv *.gcno *.gcda ./gcov
	lcov --capture --directory ./gcov --output-file ./gcov/coverage.info
	genhtml -o ./gcov/report ./gcov/coverage.info
	open ./gcov/report/index.html

dist:
	mkdir -p s21_Calc
	cp -ap Test ./s21_Calc
	cp -ap Calculation ./s21_Calc
	cp -ap View ./s21_Calc
	cp -ap Makefile ./s21_Calc
	cp -ap Documentation.html ./s21_Calc
	tar -czf s21_Calc.tar.gz ./s21_Calc
	rm -rf s21_Calc

dvi:
	open Documentation.html

leaks: test
	leaks -atExit -- ./Test/test

clang_check:
	cp ../materials/linters/.clang-format ../src/.clang-format
	clang-format -n -style=google Calculation/*.c Calculation/*.h Test/*.c Test/*.h View/*.cpp View/*.h
	rm .clang-format

clang_format:
	cp ../materials/linters/.clang-format ../src/.clang-format
	clang-format -i -style=google Calculation/*.c Calculation/*.h Test/*.c Test/*.h View/*.cpp View/*.h
	rm .clang-format

clean:
	rm -f ./Test/test
	rm -rf gcov