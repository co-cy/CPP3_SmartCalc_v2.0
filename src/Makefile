build_path	:=	build
source_path	:=	.

CMAKE_FLAGS :=

install:
	@cmake $(CMAKE_FLAGS) -S $(source_path) -B $(build_path) -G "Unix Makefiles"
.PHONY: install


clear: clean
clean: uninstall
uninstall:
	rm -rf $(build_path)
.PHONY: uninstall clean clear

test: all
	@make -C $(build_path) $@ -j 16
.PHONY: test

all: install
	@make -C $(build_path) $@ -j 16
	@echo "\n"\
"-FIX график ( показывать Error + Сложных графиков )\n"\
"\n"\
"+ Пофиксить гугл стиль\n"\
"\n"\
"+ експонента ( странная дичь ) + e как константа\n"\
"+ стирание целых чисел ( inf, nan ... )\n"\
"+ ). и прочие\n"\
"+ )e и прочие\n"\
"+ Добавить проверки в модели\n"\
"\n"\
"\n"\
"+ переделать pi (на другой символ)\n"\
"+ Переписать на Ac\n"\
"+ Пофиксить размер e и x_value\n"\
"\n"\
"+ Переписать тесты на другой формат\n"\
"\n"\
"+ Вынести функции из кредита иначе нарушения MVC\n"\
"\n"\
"+ Кредитный / Депозитный калькулятор числа больше по длине в нескольких форматах\n"\
"\n"\
"+ Перечекать округление\n"\
"\n"\
"+ Дописать доку\n"\
"+ Доделать Cmake (на покруче и на сборку только тестов)\n"\
"\n"\
"+ Gtest Double eq"

.PHONY: all

dist: install
	cd $(build_path)
	cpack -C CPackConfig.cmake
.PHONY: dist

dvi:
	open ../materials/SmartCalc_v2.pdf
.PHONY: dvi

%:
	@make -C $(build_path) $@ -j 16
.PHONY: %

mem: all
	valgrind --leak-check=full \
	--leak-resolution=med \
	--track-origins=yes \
	--vgdb=no \
	--show-leak-kinds=all \
	./build/tests
.PHONY: mem

coverage: CMAKE_FLAGS += -DCMAKE_CXX_FLAGS="-fprofile-arcs -ftest-coverage"
coverage: clean install all test
	geninfo $(shell find $(build_path) -not -path "*_autogen*" -and -path "*tests.dir*.gcno" -or -path "*tests.dir*.gcda") -o $(build_path)/lcov.info
	genhtml $(build_path)/lcov.info -o $(build_path)/coverage
	open $(build_path)/coverage/index.html
.PHONY: coverage

style: clean
	clang-format -n $(shell find . -name "*.cpp" -or -name "*.cc" -or -name "*.h" -or -name "*.h") --verbose -Werror
.PHONY: style

