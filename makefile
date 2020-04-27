CC      = aarch64-linux-gnu-gcc
CXX     = aarch64-linux-gnu-g++
#CXXFLAGS = -O3 -Wall -ansi -g `pkg-config --cflags opencv`
ARMCC	= arm-linux-gnueabihf-gcc
IDIR	= ./include
CFLAGS	= -I$(IDIR)
CFLAGS += -I${SOCEDS_DEST_ROOT}/ip/altera/hps/armv8/hwlib/include/soc_s10/socal
#CFLAGS += -g
CFLAGS += -Werror
CFLAGS += -std=c11
CFLAGS += -Wall -O3
CFLAGS += -DPRINT_REG_VALUE
CFLAGS += -DDEBUG_PRINT
#CFLAGS += -DWRITE_ON_CHANGE
CFLAGS += -DDEBUG_C_DRIVER_ALL
CFLAGS += -DDEBUG_COMP_LAST
CFLAGS += -DDEBUG_MOVE_BLOCK_BIN_FIRST
#CFLAGS += -DTASK02_DBG
#CFLAGS += -DTASK02_USE_BUFFER
#CFLAGS += -DDEBUG_C_DRIVER_ALL_COMP
CFLAGS += -DSOFT_SOLVE

CXXFLAGS = $(CFLAGS)
LDLIBS	= -lm
UNAME	= $(shell uname -m)
MANU	= $(shell uname -n)

ifeq ($(UNAME), armv7l)
ifeq ($(MANU), pynq)
# CXXFLAGS+= `pkg-config --cflags opencv`
# LDLIBS	+= `pkg-config --libs opencv`
else
#OPENCVPATH	= /opt/arm-opencv-4.1.0
#CXXFLAGS+= -I$(OPENCVPATH)/include/opencv
#LDFLAGS = -L$(OPENCVPATH)/lib/
#LDLIBS	+= -lpthread -lrt -lopencv_core -lopencv_videoio -lopencv_highgui -lopencv_imgproc -lopencv_imgcodecs -lpthread -ldl 
# CXXFLAGS+= `pkg-config --cflags opencv4`
# LDLIBS	+= `pkg-config --libs opencv4`
endif
endif

ifeq ($(UNAME), x86_64)
# CXXFLAGS+= `pkg-config --cflags opencv4`
# LDLIBS	+= `pkg-config --libs opencv4`
endif

MODULES	= src
#MODULES+= test
MODULES+= block_op/task2_op_c block_op/resnet50_op_c block_op/resnet18_op_c block_op/mobilenet_op_c
MODULES+= run_api
SRC_DIR	= $(addprefix ./,$(MODULES))
#BUILDR = $(addprefix build/,$(MODULES))
BUILD	= build
BUILDXX	= buildxx

SRC	= $(foreach sdir, $(SRC_DIR), $(wildcard $(sdir)/*.c))
OBJ	= $(patsubst %.c, build/%.o, $(notdir $(SRC)))
SRCXX	= $(foreach sdir, $(SRC_DIR), $(wildcard $(sdir)/*.cpp))
OBJXX	+= $(patsubst %.cpp, buildxx/%.o, $(notdir $(SRCXX)))
DEP	= $(OBJ:.o=.d)
DEP	+= $(OBJXX:.o=.d)
#INCLUDES  := $(addprefix -I,$(SRC_DIR))

vpath %.c $(SRC_DIR)
vpath %.cpp $(SRC_DIR)


define make-goal
$1/%.o:	%.c
	$(CC) $(CFLAGS) -c $$< -o $$@
	@$(CC) $(CFLAGS) $$< -MM -MT $$@ >$$(@:.o=.d)
endef

define make-xxgoal
$1/%.o:	%.cpp
	$(CXX) $(CXXFLAGS) -c $$< -o $$@
	@$(CXX) $(CXXFLAGS) $$< -MM -MT  $$@ >$$(@:.o=.d) 
endef


.PHONY: all checkdirs clean

all: checkdirs cnntest

cnntest: $(OBJ) $(OBJXX)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

-include $(DEP)   # include all dep files in the makefile

checkdirs: $(BUILD) $(BUILDXX)

$(BUILD):
	@mkdir -p $@

$(BUILDXX):
	@mkdir -p $@

clean:
	rm -rf $(BUILD) $(BUILDXX)
	rm -f cnntest


$(foreach bdir,$(BUILD),$(eval $(call make-goal,$(bdir))))
$(foreach bdir,$(BUILDXX),$(eval $(call make-xxgoal,$(bdir))))


