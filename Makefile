CXX = g++ 
CPPFLAGS = -Wall #-Werror
DEBUG = -O0 -g -ggdb3 # -c

# Prerequisits
# 1. export PROJECTS_PATH environment variable to the full path to the directory housing CppQueryable project
# 2. export GTEST_BASE_DIR environment variable to the full path to the directory housing the src/lib/include directories for gtest

$(warning "Base Project Path: $(PROJECTS_PATH)") # exported environment variable
PROJECT_PATH = $(PROJECTS_PATH)/CppQueryable
PROGRAM_DIR = $(PROJECT_PATH)/Bin
PROGRAM = $(PROGRAM_DIR)/CppQueryable
PROGRAM_TEST_DIR = $(PROJECT_PATH)/CppQueryableTest
FUNCTIONAL_TEST_DIR = $(PROGRAM_TEST_DIR)/Queryable/Functional
UTILITIES_TEST_DIR = $(PROGRAM_TEST_DIR)/Queryable/Utilities
TEST_PROGRAM = $(PROGRAM_TEST_DIR)/CppQueryableTest_testcases

DEPENDENCIES = $(PROJECT_PATH)/Makefile.dep

# gtests setup instructions:
# 1. sudo apt-get install libgtest-dev
# 2. sudo apt-get install cmake
# 3. cd /usr/src/gtest
# 4. sudo cmake CMakeLists.txt
# 5. sudo make
# 6. sudo cp ./lib/*.a /usr/lib

GTEST_BASE = $(GTEST_BASE_DIR)
GTEST_MAIN_CC = $(GTEST_BASE)/src/gtest_main.cc
GTEST = $(GTEST_MAIN_CC)

LIBS =
TEST_LIBS = $(LIBS) -lgtest -lgtest_main -lpthread
INCLUDES =
TEST_INCLUDES = $(INCLUDES) -I$(GTEST_BASE)/include/gtest $(GTEST) -L$(GTEST_BASE)/lib

TEST_TIMEOUT = 10000 # TODO --> get this to work properly

REFS_PATH = $(PROJECT_PATH)/.refs
SRC_COMPILE_REF = $(REFS_PATH)/.sourceCompileRef
TEST_COMPILE_REF = $(REFS_PATH)/.testCompileRef
DEPEND_REF = $(REFS_PATH)/.dependRef
REFS_REF = $(REFS_PATH)/.refsRef

PROGRAM_SRCS_PATHS = $(shell find $(PROJECT_PATH) -not \( -path $(PROGRAM_TEST_DIR) -prune \) -name "*.cpp")
PROGRAM_HDRS_PATHS = $(shell find $(PROJECT_PATH) -not \( -path $(PROGRAM_TEST_DIR) -prune \) -name "*.hpp")

PROGRAM_OBJS = $(PROGRAM_SRCS_PATHS:.cpp=.o)

PROGRAM_SRCS_BASES = $(basename $(PROGRAM_SRCS_PATHS))

TEST_SRCS = $(shell find $(PROGRAM_TEST_DIR) -name "*.cpp")
TEST_SRCS_BASES = $(basename $(TEST_SRCS))

TEST_EXCLUDES = $(PROJECT_PATH)/main.o

TEST_OBJS = $(filter-out $(TEST_EXCLUDES), $(TEST_SRCS:.cpp=.o) $(PROGRAM_OBJS))

$(PROGRAM): $(DEPEND_REF) $(SRC_COMPILE_REF)
	@echo Building $(PROGRAM)...
	$(CXX) -o $(PROGRAM) $(CPPFLAGS) $(PROGRAM_OBJS) $(LIBS)

$(SRC_COMPILE_REF): $(REFS_REF) $(PROGRAM_SRCS_PATHS) $(PROGRAM_HDRS_PATHS)
	@for i in $(PROGRAM_SRCS_BASES); do \
	src=$$i.cpp ; \
	obj=$$i.o ; \
	echo "*** Compile $$src to $$obj..." ; \
	$(CXX) -c $(DEBUG) $(CPPFLAGS) $(INCLUDES) $$src -o $$obj ; \
	done;
	touch $(SRC_COMPILE_REF)

$(DEPEND_REF): $(REFS_REF) $(DEPENDENCIES)
	@echo "*** Regenerating $(DEPENDENCIES)..."
	@/bin/rm -f $(DEPENDENCIES)
	@for i in $(PROGRAM_SRCS_PATHS) $(TEST_SRCS); \
	do \
	$(CXX) -MM $(CPPFLAGS) $$i >> $(DEPENDENCIES) ; \
	done;
	touch $(DEPEND_REF)

$(TEST_COMPILE_REF): $(REFS_REF) $(SRC_COMPILE_REF) $(TEST_SRCS)
	@for i in $(TEST_SRCS_BASES); do \
	src=$$i.cpp ; \
	obj=$$i.o ; \
	echo "*** Compile $$src to $$obj..." ; \
	$(CXX) -c $(CPPFLAGS) $$src -o $$obj ; \
	done;
	touch $(TEST_COMPILE_REF)

$(TEST_PROGRAM): $(TEST_COMPILE_REF)
	@echo "test objs: "
	@echo $(TEST_OBJS)
	$(CXX) -o $(TEST_PROGRAM) $(CPPFLAGS) $(TEST_OBJS) $(TEST_INCLUDES) $(TEST_LIBS)

.PHONY: tests
tests: $(TEST_PROGRAM)
	$(foreach testcase, $(TEST_PROGRAM), $(testcase);)

.PHONY: FuncTests
FuncTests: $(REFS_REF) $(SRC_COMPILE_REF)
	directory="Queryable/Functional" $(MAKE) DirTests

.PHONY: utest
utest: $(REFS_REF) $(SRC_COMPILE_REF)
	directory="Queryable/Utilities" $(MAKE) DirTests

.PHONY: TimeTests
TimeTests: $(REFS_REF) $(SRC_COMPILE_REF)
	directory="Queryable/Performance/Time" $(MAKE) DirTests

# TOOD: for loop through the wildcard files specified
.PHONY: DirTests
DirTests: $(REFS_REF) $(SRC_COMPILE_REF)
	$(eval SRCS := $(wildcard $(PROGRAM_TEST_DIR)/$(directory)/*$(key)*.cpp))
	$(eval OBJS := $(SRCS:.cpp=.o))
	$(eval SRC_BASES := $(basename $(SRCS)))

	@for i in $(SRC_BASES); do \
		src=$$i.cpp ; \
		obj=$$i.o ; \
		echo "*** Compile $$src to $$obj..." ; \
		$(CXX) -c $(CPPFLAGS) $$src -o $$obj ; \
	done;

	-$(CXX) $(DEBUG) -o $(PROGRAM_TEST_DIR)/$(directory)/$(key)Test_testcases \
		$(CPPFLAGS) \
		$(filter-out $(TEST_EXCLUDES), $(PROGRAM_OBJS)) \
		$(OBJS) \
		$(TEST_INCLUDES) \
		$(TEST_LIBS)

	/bin/rm -f $(OBJS)
	/bin/rm -f $(PROGRAM_TEST_DIR)/$(directory)/$(key)Test.o
	# -$(foreach testcase, $(PROGRAM_TEST_DIR)/$(directory)/$(key)Test_testcases, $(testcase);)
	# /bin/rm -f $(PROGRAM_TEST_DIR)/$(directory)/$(key)Test_testcases

.PHONY: memtests
memtests: $(TEST_PROGRAM)
	/usr/bin/valgrind -v --trace-children=yes --track-fds=yes --track-origins=yes \
		--leak-check=full --show-leak-kinds=all $(TEST_PROGRAM)

.PHONY: dmemtest
dmemtest: $(REFS_REF) $(SRC_COMPILE_REF)
	$(CXX) -c $(CPPFLAGS) $(wildcard $(PROGRAM_TEST_DIR)/$(directory)/*$(key)*) \
		-o $(PROGRAM_TEST_DIR)/$(directory)/$(key)Test.o
	$(CXX) -o $(PROGRAM_TEST_DIR)/$(directory)/$(key)Test_testcases \
		$(CPPFLAGS) \
		$(filter-out $(TEST_EXCLUDES), $(PROGRAM_OBJS)) \
		$(PROGRAM_TEST_DIR)/$(directory)/$(key)Test.o \
		$(TEST_INCLUDES) \
		$(TEST_LIBS)

	/bin/rm -f $(PROGRAM_TEST_DIR)/$(directory)/$(key)Test.o
	-/usr/bin/valgrind -v --trace-children=yes --track-origins=yes \
		--leak-check=full --show-leak-kinds=all \
		$(PROGRAM_TEST_DIR)/$(directory)/$(key)Test_testcases
	/bin/rm -f $(PROGRAM_TEST_DIR)/$(directory)/$(key)Test_testcases

$(DEPENDENCIES):
	touch $(DEPENDENCIES)

$(REFS_REF):
	/bin/mkdir -p $(REFS_PATH)
	/bin/mkdir -p $(PROGRAM_DIR)
	/bin/mkdir -p $(PROGRAM_TEST_DIR)
	touch $(REFS_REF)

.PHONY: depend
depend: $(DEPEND_REF)

.PHONY: cleantests
cleantests:
	/bin/rm -f $(TEST_COMPILE_REF) $(TEST_PROGRAM) $(TEST_OBJS) $(SRC_COMPILE_REF)

.PHONY: clean
clean:
	/bin/rm -f $(SRC_COMPILE_REF) $(PROGRAM) $(PROGRAM_OBJS)

.PHONY: cleanall
cleanall: clean cleantests
	/bin/rm -f $(DEPEND_REF) $(DEPENDENCIES)
	find . -name "*.o" -type f -delete
	find . -name "*.gch" -type f -delete

.PHONY: cleanrefs
cleanrefs:
	/bin/rm -rf $(REFS_PATH)

-include $(DEPENDENCIES)
