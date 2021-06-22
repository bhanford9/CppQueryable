CXX = g++
CPPFLAGS = -Wall #-Werror
DEBUG = -g # -c

PROJECTS_PATH = ~/Projects
PROJECT_PATH = $(PROJECTS_PATH)/CppQueryable
PROGRAM_DIR = $(PROJECT_PATH)/Bin
PROGRAM = $(PROGRAM_DIR)/CppQueryableProgram
PROGRAM_TEST_DIR = $(PROJECT_PATH)/CppQueryableTest

DEPENDENCIES = $(PROJECT_PATH)/Makefile.dep

REFS_PATH = $(PROJECT_PATH)/.refs
SRC_COMPILE_REF = $(REFS_PATH)/.sourceCompileRef
TEST_COMPILE_REF = $(REFS_PATH)/.testCompileRef
DEPEND_REF = $(REFS_PATH)/.dependRef
REFS_REF = $(REFS_PATH)/.refsRef

PROGRAM_SRCS_PATHS = $(shell find $(PROJECT_PATH) -name "*.cpp")
PROGRAM_HDRS_PATHS = $(shell find $(PROJECT_PATH) -name "*.h")

PROGRAM_OBJS = $(PROGRAM_SRCS_PATHS:.cpp=.o)

PROGRAM_SRCS_BASES = $(basename $(PROGRAM_SRCS_PATHS))

TEST_SRCS = $(shell find $(PROGRAM_TEST_DIR) -name "*.cpp")
TEST_SRCS_BASES = $(basename $(TEST_SRCS))

TEST_EXCLUDES = $(PROJECT_PATH)/main.o

TEST_OBJS = $(filter-out $(TEST_EXCLUDES), $(TEST_SRCS:.spp-.o) $(PROGRAM_OBJS))

$(PROGRAM): $(DEPEND_REF) $(SRC_COMPILE_REF)
	@echo Building $(PROGRAM)...
	$(CXX) -o $(PROGRAM) $(CPPFLAGS) $(PROGRAM_OBJS) # add libs as necessary

$(SRC_COMPILE_REF): $(REFS_REF) $(PROGRAM_SRCS_PATHS) $(PROGRAM_HDRS_PATHS)
	@for i in $(PROGRAM_SRCS_BASES); do \
	src=$$i.cpp ; \
	obj=$$i.o ; \
	echo "*** Compile $$src to $$obj..." ; \
	$(CXX) -c $(DEBUG) $(CPPFLAGS) $$src -o $$obj ; \
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

# $(TEST_PROGRAM): $(TEST_COMPILE_REF) $(GTEST)
# 	$(CXX) -o $(TEST_PROGRAM) $(CPPFLAGS) $(TEST_OBJS) $(GTEST) $(GTEST_LIBS) $(GMOCK) # add libs as necessary

# .PHONY: tests
# tests: $(TEST_PROGRAM)
# 	$(foreach testcase, $(TEST_PROGRAM), $(TEST_TIMEOUT) ./$(testcase) $(GTEST_LOG);)

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

.PHONY: cleanrefs
cleanrefs:
	/bin/rm -rf $(REFS_PATH)

-include $(DEPENDENCIES)
