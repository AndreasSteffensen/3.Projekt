SOURCES=spi_test_3.cpp PSoCIF.cpp
OBJECTS=$(addprefix $(BUILD_DIR)/, $(SOURCES:.cpp=.o))
DEPS=$(addprefix $(BUILD_DIR)/, $(SOURCES:.cpp=.d))
EXE=$(addprefix $(BIN_DIR)/, spi_test_3)
CXXFLAGS=-I.
ARCH ?= host

#Making for host
# > make ARCH=host
ifeq (${ARCH},host)
CXX=g++
BUILD_DIR=build/host
BIN_DIR=bin/host
endif

#Making for target
# > make ARCH=target
ifeq (${ARCH},target)
CXX=arm-rpizw-g++
BUILD_DIR=build/target
BIN_DIR=bin/target
endif

all: $(EXE)

${EXE}: ${DEPS} ${OBJECTS} # << Check the ${DEPS} new dependency
	@mkdir -p $(BIN_DIR)
	${CXX} ${CXXFLAGS} ${OBJECTS} -o $@ -lpthread

#Rule that describes how a .d(dependency) file is created from a .cpp file
#Similar to the assignment that you just completed %.cpp -> %.o
$(BUILD_DIR)/%.d: %.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) -MT$@ -MM $(CXXFLAGS) $< > $@
	$(CXX) -MT$(@:.d=.o) -MM $(CXXFLAGS) $< >> $@

$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) -c $< -o $@ $(CXXFLAGS)

@PHONY:clean
clean:
	@rm -rf bin/
	@rm -rf build/
	@rm -rf *.tidy
	@rm -rf *.format

#formater .cpp filerne
@PHONY:format
format: $(SOURCES:.cpp=.format)
%.format: %.cpp
	@echo "Formatting file '$<'"
	@clang-format -i $<
	@echo ""> $@

#foorbedring til .cpp filerne
@PHONY:tidy
tidy: $(SOURCES:.cpp=.tidy)
%.tidy: %.cpp
	@echo "Tidying file '$<'"
	@clang-tidy $< -- $(CXXFLAGS)
	@echo "" > $@


#undgå dependcie genering
ifneq ($(filter -out clean format tidy ,$(MAKECMDGOALS)) ,)
-include $(DEPS)
endif