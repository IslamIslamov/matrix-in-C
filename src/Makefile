CC :=gcc
CFLAGS =-Wall -Werror -Wextra -std=c11 -o2
GCOV_FLAGS :=--coverage
GCOV_FLAGS_TEMP :=

SOURCE_DIR = functions
SOURCE =$(foreach current_dir, $(SOURCE_DIR), $(wildcard $(current_dir)/*.c)) 
OBJECTS =$(patsubst %.c,%.o, ${SOURCE})
EXECUTABLE_NAME =s21_matrix.a

ifeq ($(shell uname -s), Linux)
	ADD_LIB =-lrt -pthread -lsubunit
else
	ADD_LIB =
endif

TEST_SOURCE_DIR = tests
TEST_SOURCE =$(foreach current_dir, $(TEST_SOURCE_DIR), $(wildcard $(current_dir)/*.c)) 
TEST_OBJECTS =$(patsubst %.c,%.o, ${TEST_SOURCE})
TEST_EXECUTABLE_NAME =s21_matrix_test
ADD_TEST_LIB =-lcheck -lm

GCOV_REPORT_NAME =$(TEST_EXECUTABLE_NAME)_gcov_report
REPORT_LIB =gcov_report

all: clean $(EXECUTABLE_NAME) test

$(EXECUTABLE_NAME): clean_exe clean_obj ${OBJECTS}

ifeq ($(EXECUTABLE_NAME), $(patsubst %.% ,%.a, $(EXECUTABLE_NAME)))
	ar rc $@ ${OBJECTS}
else 
	${CC} $(CFLAGS) ${OBJECTS} -o $@ ${ADD_LIB}
endif
	@make -s clean_obj

${OBJECTS}: 
	$(CC) $(CFLAGS) $(GCOV_FLAGS_TEMP) -c $(patsubst %.o,%.c, $@) -o $@ ${ADD_LIB}

$(TEST_EXECUTABLE_NAME): clean_test_exe $(EXECUTABLE_NAME) ${TEST_OBJECTS}
	${CC} ${CFLAGS} ${TEST_OBJECTS} $(EXECUTABLE_NAME) -o $@ ${ADD_TEST_LIB} ${ADD_LIB} 
	@make -s clean_obj

${TEST_OBJECTS}:
	$(CC) $(CFLAGS) -c $(patsubst %.o,%.c, $@) -o $@ ${ADD_TEST_LIB} ${ADD_LIB}

test: ${EXECUTABLE_NAME} $(TEST_EXECUTABLE_NAME)
	./$(TEST_EXECUTABLE_NAME)

gcov_report: clean_test_exe clean_gcov_test gcov_compile ${OBJECTS} ${TEST_OBJECTS} 
	${CC} ${CFLAGS} ${GCOV_FLAGS} ${OBJECTS} ${TEST_OBJECTS} -o ${GCOV_REPORT_NAME} ${ADD_TEST_LIB} ${ADD_LIB}
	@make -s clean_obj
	./${GCOV_REPORT_NAME}
	lcov --capture  --test-name "${GCOV_REPORT_NAME}" --output-file ${GCOV_REPORT_NAME}.info --directory .
	genhtml --output-directory $(REPORT_LIB)/html_info ${GCOV_REPORT_NAME}.info
	@make -s clean_gcov_test

clean_obj:
	rm -f *.o */*.o */*/*.o */*/*/*.o */*/*/*/*.o

clean_gcov_test:
	rm -f *.gcno */*.gcno */*/*.gcno */*/*/*.gcno */*/*/*/*.gcno
	rm -f *.gcov */*.gcov */*/*.gcov */*/*/*.gcov */*/*/*/*.gcov
	rm -f *.info */*.info */*/*.info */*/*/*.info */*/*/*/*.info
	rm -f *.gcda */*.gcda */*/*.gcda */*/*/*.gcda */*/*/*/*.gcda

clean_exe: 
	rm -f $(EXECUTABLE_NAME)

clean_test_exe: 
	rm -f $(TEST_EXECUTABLE_NAME)
	rm -f ${GCOV_REPORT_NAME}

clean_gcov_test_exe:
	rm -rf $(REPORT_LIB)

clean: clean_obj clean_exe clean_test_exe clean_gcov_test_exe clean_gcov_test

gcov_compile: $($(eval gcov_report: GCOV_FLAGS_TEMP += $(GCOV_FLAGS)))

clang:
	clang-format -i -style=google ${SOURCE} ${TEST_SOURCE}

clang_check:
	clang-format -n -style=google ${SOURCE} ${TEST_SOURCE}

valgrind:
	valgrind --tool=memcheck --leak-check=yes  ./$(TEST_EXECUTABLE_NAME)

.PHONY: all $(EXECUTABLE_NAME) $(TEST_EXECUTABLE_NAME) all test gcov_report clean_obj clean_gcov_test clean_exe clean_test_exe clean_gcov_test_exe clean, clang, clang_check

