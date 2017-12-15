# Generic functions
cfilesfromdir = $(wildcard $(1)*.c)
cppfilesfromdir = $(wildcard $(1)*.cpp)
objectfilesfromlist =$(addprefix $(1), $(addsuffix .o, $(basename $(notdir $(2)))))
