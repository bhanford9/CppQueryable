CXX = g++
CPPFLAGS = -Wall #-Werror
DEBUG = -g  -ggdb3# -c

$(warning "Base Project Path: $(PROJECTS_PATH)") # exported environment variable
$(warning "CppQueryable Project Path: $(CPP_QUERYABLE_PATH)") # exported environment variable
PROJECT_PATH = $(PROJECTS_PATH)/CppQueryable
PROGRAM_DIR = $(PROJECT_PATH)/Bin
PROGRAM = $(PROGRAM_DIR)/CppQueryable
PROGRAM_TEST_DIR = $(PROJECT_PATH)/CppQueryableTest
FUNCTIONAL_TEST_DIR = $(PROGRAM_TEST_DIR)/Queryable/Functional
UTILITIES_TEST_DIR = $(PROGRAM_TEST_DIR)/Queryable/Utilities
TEST_PROGRAM = $(PROGRAM_TEST_DIR)/CppQueryableTest_testcases

DEPENDENCIES = $(PROJECT_PATH)/Makefile.dep

GTEST_MAIN_CC = /usr/src/gtest/src/gtest_main.cc
GTEST = $(GTEST_MAIN_CC)

LIBS =
TEST_LIBS = $(LIBS) -lgtest -lgtest_main -pthread
INCLUDES =
TEST_INCLUDES = $(INCLUDES) -I/usr/include/gtest $(GTEST) -L/usr/lib

TEST_TIMEOUT = 10000 # TODO --> get this to work properly

REFS_PATH = $(PROJECT_PATH)/.refs
SRC_COMPILE_REF = $(REFS_PATH)/.sourceCompileRef
TEST_COMPILE_REF = $(REFS_PATH)/.testCompileRef
DEPEND_REF = $(REFS_PATH)/.dependRef
REFS_REF = $(REFS_PATH)/.refsRef

PROGRAM_SRCS_PATHS = $(shell find $(PROJECT_PATH) -not \( -path $(PROGRAM_TEST_DIR) -prune \) -name "*.cpp")
PROGRAM_HDRS_PATHS = $(shell find $(PROJECT_PATH) -not \( -path $(PROGRAM_TEST_DIR) -prune \) -name "*.h")

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

.PHONY: ftest
ftest: $(REFS_REF) $(SRC_COMPILE_REF)
	directory="Queryable/Functional" $(MAKE) dtest

.PHONY: utest
utest: $(REFS_REF) $(SRC_COMPILE_REF)
	directory="Queryable/Utilities" $(MAKE) dtest

.PHONY: time_test
time_test: $(REFS_REF) $(SRC_COMPILE_REF)
	directory="Queryable/Performance/Time" $(MAKE) dtest

.PHONY: dtest
dtest:$(REFS_REF) $(SRC_COMPILE_REF)
	$(CXX) -c $(CPPFLAGS) $(wildcard $(PROGRAM_TEST_DIR)/$(directory)/*$(key)*) \
		-o $(PROGRAM_TEST_DIR)/$(directory)/$(key)Test.o
	$(CXX) -o $(PROGRAM_TEST_DIR)/$(directory)/$(key)Test_testcases \
		$(CPPFLAGS) \
		$(filter-out $(TEST_EXCLUDES), $(PROGRAM_OBJS)) \
		$(PROGRAM_TEST_DIR)/$(directory)/$(key)Test.o \
		$(TEST_INCLUDES) \
		$(TEST_LIBS)

	$(foreach testcase, $(PROGRAM_TEST_DIR)/$(directory)/$(key)Test_testcases, $(testcase);)
	/bin/rm -f $(PROGRAM_TEST_DIR)/$(directory)/$(key)Test_testcases \
		$(PROGRAM_TEST_DIR)/$(directory)/$(key)Test.o ;


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
	/bin/rm -rf **/*.o
	/bin/rm -rf **/*.gch

.PHONY: cleanrefs
cleanrefs:
	/bin/rm -rf $(REFS_PATH)

-include $(DEPENDENCIES)
