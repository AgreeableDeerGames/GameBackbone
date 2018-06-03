TARGET_EXEC ?= Demo
EXEC_DIR ?= GameBackboneSln/GameBackboneExe/
BUILD_DIR ?= ./bld
SRC_DIRS ?= GameBackboneSln/GameBackboneExe GameBackboneSln/GameBackboneDll

OS=$(shell lsb_release -si)

SRCS := $(shell find $(SRC_DIRS) -name *.cpp)
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))
CPPFLAGS ?= $(INC_FLAGS) -MMD -MP -std=c++17

ifeq ($(OS),Ubuntu)
	CXX := g++-6
else
	CXX := g++
endif

$(EXEC_DIR)/$(TARGET_EXEC): $(OBJS)
	@$(MKDIR_P) $(dir $@)
	$(info $ Building Demo executable)
	@#these flags assume that tgui,sfml,and boost are installed to your system
	@$(CXX) $(OBJS) -o $@ $(LDFLAGS) -ltgui -lsfml-graphics -lsfml-window -lsfml-system -lsfml-system -lboost_system -lboost_unit_test_framework
	@$(info $ Demo location: $(EXEC_DIR)$(TARGET_EXEC))
# c++ source
$(BUILD_DIR)/%.cpp.o: %.cpp
	@$(MKDIR_P) $(dir $@)
	$(info $ Building ${<})
	@$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@


.PHONY: clean

clean:
	$(RM) -r $(BUILD_DIR)
	$(RM) -r $(EXEC_DIR)$(TARGET_EXEC)


-include $(DEPS)

MKDIR_P ?= mkdir -p
