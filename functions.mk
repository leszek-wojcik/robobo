# Generic functions
objforfile = $(dir $(1))$(OBJ_DIR)$(addsuffix .o, $(basename $(notdir $(1))))
csrcforfile = $(addsuffix .c, $(dir $(1))../$(basename $(notdir $(1))))
cppsrcforfile = $(addsuffix .cpp, $(dir $(1))../$(basename $(notdir $(1))))
cfilesfromdir = $(wildcard $(1)*.c)
cppfilesfromdir = $(wildcard $(1)*.cpp)
objectfilesfromlist =$(addprefix $(1), $(addsuffix .o, $(basename $(notdir $(2)))))
