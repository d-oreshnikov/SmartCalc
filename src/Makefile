CC = gcc
CFLAGS = -Wall -Wextra -pedantic -g
LFLAGS=-lcheck -pthread -lcheck_pic -pthread -lm -lrt -lsubunit
COVERAGE_FLAGS = -fprofile-arcs -ftest-coverage

SRC_DIR= .
TEST_DIR=tests
INCLUDE_DIR := $(shell find $(SRC_DIR) -type d)
BUILD_DIR=build
GCOV_DIR=gcov_report
DOC_DIR=html

SRC  := $(shell find $(SRC_DIR) -name "*.c" | sed -e 's/\.\///')
OBJS := $(SRC:%.c=$(BUILD_DIR)/%.o)
TEST=
TEST_OBJS=$(BUILD_DIR)/$(TEST_DIR)/tests.o

all: install tests clean

QT_PROJECT_NAME = ui
QT_PROJECT_FOLDER = ./$(QT_PROJECT_NAME)
QT_PRO = calcui/$(QT_PROJECT_NAME).pro
QT_MAKEFILE = $(QT_PROJECT_NAME)_Makefile
QT_BUILD_FOLDER = build
QT_APP_FOLDER = ../app
DIST_FOLDER_NAME = SmartCalc-1.0

generate_make:
	@qmake $(QT_PROJECT_FOLDER)/$(QT_PRO) -o ./$(QT_BUILD_FOLDER)/$(QT_MAKEFILE)
	@rm -rf .qmake.stash

install: generate_make
	@echo "Building application..."
	@cd ./$(QT_BUILD_FOLDER) && make -sf $(QT_MAKEFILE)
	@echo "Application builded."
	@echo -n "Moving application to folder \"$(QT_APP_FOLDER)\"..."
	@mkdir ./$(QT_APP_FOLDER)
ifeq ($(OS), Darwin)
	@mv ./$(QT_BUILD_FOLDER)/$(QT_PROJECT_NAME).app/Contents/MacOS/SmartCalc ./$(QT_APP_FOLDER)/$(QT_PROJECT_NAME).app
else
	@mv ./$(QT_BUILD_FOLDER)/$(QT_PROJECT_NAME) ./$(QT_APP_FOLDER)/$(QT_PROJECT_NAME)
endif
	@echo " Done."
	@echo -n "Deleting build folder..."
	@rm -rf $(QT_BUILD_FOLDER)
	@echo " Done."
	@echo "Installation complete!"

uninstall:
	@echo -n "Uninstalling application..."
	@rm -rf $(QT_APP_FOLDER)
	@echo " Done."

test: s21_smart_calc.a $(TEST_OBJS)
	$(CC) $(CFLAGS) $(TEST_OBJS) $(LFLAGS) s21_smart_calc.a -o test.out
	./test.out

s21_smart_calc.a: $(OBJS)
	@mkdir -p $(BUILD_DIR)
	ar rc s21_smart_calc.a $(OBJS)
	ranlib s21_smart_calc.a

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@ $(LFLAGS)

$(BUILD_DIR)/main.o: main.c
	$(CC) $(CLFAGS) -v -c main.c -o $(BUILD_DIR)/main.o

gcov_report: clean
	$(CC) $(CFLAGS) $(COVERAGE_FLAGS) $(SRC) $(LFLAGS) -o gcov.out
	./gcov.out
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info --output-directory gcov_report
	open $(GCOV_DIR)/index.html
	rm -Rf *.gcda *.cov *.gcno *.info

TAR_DIR = SmartCalc_v1.0_Archive

dist:
	rm -Rf $(TAR_DIR)
	mkdir $(TAR_DIR)
	mkdir $(TAR_DIR)/src
	cp $(SRC) ui/calcui/* $(TAR_DIR)/src
	tar cvzf $(TAR_DIR).tgz $(TAR_DIR)
	mv $(TAR_DIR).tgz ..
	rm -Rf $(TAR_DIR)

dvi:
	doxygen Doxyfile
	open html/index.html

clean: 
	rm -f *.gcda *.gcov *.o *.gcno
	rm -f s21_smart_calc.a
	rm -rf $(BUILD_DIR) $(GCOV_DIR)
	rm -rf *out *info
	rm -rf $(DOC_DIR) $(TAR_DIR) ../$(TAR_DIR).tgz

style:
	clang-format -style=Google -n $(SRC)

