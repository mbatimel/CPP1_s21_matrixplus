CC=g++
FLAGS=-std=c++17 -Wall -Wextra -Werror
MODULES=matrix_chenge.cpp matrix_operators.cpp matrix_opiration.cpp other_fancs.cpp
MODULES_O=$(MODULES:.cpp=.o)
SRC_DIR=working_files
TEST=tests/tests_matix.cpp
LIB_NAME=s21_matrix_oop.a

all: clean $(LIB_NAME) test

$(LIB_NAME): $(MODULES_O)
	ar rc $(LIB_NAME) $(MODULES_O)
	ranlib $(LIB_NAME)

%.o: $(SRC_DIR)/%.cpp
	$(CC) $(FLAGS) -c $< -o $@

test: clean $(LIB_NAME)
	$(CC) $(FLAGS) -fprofile-arcs -ftest-coverage $(TEST) $(LIB_NAME) -lgtest -lgtest_main -o test
	./test
gcov_flag:
	$(eval FLAGS += -fprofile-arcs -ftest-coverage)

gcov_report: gcov_flag test
	gcov --no-output $(TEST)
	lcov --no-external --capture --directory . --output-file coverage.info
	genhtml coverage.info -o report


clean:
	rm -f *.o *.a test *.gcda *.gcno *.info
	rm -rf report

clang-format:
	cp ../materials/linters/.clang-format .
	clang-format -n working_files/*.cpp lib/*.h 2>fail.txt
	rm .clang-format
