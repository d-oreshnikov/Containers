CC = g++ -std=c++17
CFLAGS = -Wall -Wextra -Werror -lstdc++ -lm
TEST_FLAGS = -lgtest -pthread
TEST_FILES = ./tests/test_my_*.cc
COVERAGE =

all: test

test: clean  
	$(CC) $(CFLAGS) $(TEST_FILES) -o test $(TEST_FLAGS) $(COVERAGE)
	./test

clean:
	rm -rf test
	rm -rf gcovr
	rm -rf ./*.gc*

add_coverage:
$(eval COVERAGE += --coverage)

gcovr_report: add_coverage test
	mkdir gcovr
	gcovr --html-details gcovr/report.details.html
	rm -rf ./*.gc*
	open gcovr/report.details.html

valgrind: test
	valgrind --tool=memcheck --leak-check=full --track-origins=yes --show-reachable=yes --num-callers=20 --track-fds=yes ./test


format :
	clang-format -i -style=Google */*.h

check-format :
	clang-format -n -style=Google */*.h