################################################################################
#
# Build script for project
#
################################################################################
EXECUTABLE  := stMain.app
CPP_DEPS    := stMain.cpp
################################################################################
# Rules and targets
#VERBOSE ?= @
HOMEPATH	:= /Users/yuzhu/Documents/yuzhu
CUDA_INSTALL_PATH ?= /usr/local/cuda
BOOST_PATH := $(HOMEPATH)/boost_1_60_0
VLFEAT_PATH := $(HOMEPATH)/Lib/vlfeat-0.9.18
#WXGTK_PATH	:= $(HOMEPATH)/Lib/wxGTK
#SDKCDIR    := $(HOMEPATH)/NVIDIA_GPU_Computing_SDK/C
#NVCC       := $(CUDA_INSTALL_PATH)/bin/nvcc
#MEX 		:= /usr/local/matlab/R2012a/bin/mex
CXX	   := g++
LINK       := g++
VERBOSE	   :=
ROOTDIR    ?= .
BINDIR 	   ?= $(ROOTDIR)/bin
OBJDIR	   ?= $(ROOTDIR)/obj
#CUDALIBDIR     := $(SDKCDIR)/lib

#CUDAINCLUES 	:= -I$(CUDA_INSTALL_PATH)/include #-I$(SDKCDIR)/common/inc/
BOOSTINCLUDES	:= -I$(BOOST_PATH)
VLINCLUDES		:= -I$(VLFEAT_PATH)
#WXGTKINCLUDES	:= -I$(WXGTK_PATH)/include -I$(WXGTK_PATH)/lnx
INCLUDES  :=  $(CUDAINCLUES) $(BOOSTINCLUDES) $(VLINCLUDES) #$(WXGTKINCLUDES)

CUDALIBS	:= #-L$(CUDA_INSTALL_PATH)/lib64 -L$(CUDALIBDIR)  -lcudart -lglut -lcublas 
BOOSTLIBS	:= #-L$(BOOST_PATH)/lib
VLLIBS		:= #-L$(VLFEAT_PATH)/bin/glnxa64 -lvl
#WXGTKLIBS	:= -L$(WXGTK_PATH)/lib -pthread -Wl,-Bsymbolic-functions -Wl,-z,relro  -L/usr/lib/x86_64-linux-gnu   -lwx_gtk2u_richtext-2.8 -lwx_gtk2u_aui-2.8 -lwx_gtk2u_xrc-2.8 -lwx_gtk2u_qa-2.8 -lwx_gtk2u_html-2.8 -lwx_gtk2u_adv-2.8 -lwx_gtk2u_core-2.8 -lwx_baseu_xml-2.8 -lwx_baseu_net-2.8 -lwx_baseu-2.8 -ljpeg
LIB			:=	$(CUDALIBS) $(BOOSTLIBS) $(VLLIBS) #$(WXGTKLIBS)

NEWDIRS	  := .
OBJS +=  $(patsubst %.cu,$(OBJDIR)/%.cu.o,$(notdir $(CUFILES)))
OBJS +=  $(patsubst %.cu,$(OBJDIR)/%.cu.o,$(notdir $(CU_DEPS)))
OBJS +=  $(patsubst %.cpp,$(OBJDIR)/%.cpp.o,$(notdir $(CPP_DEPS)))

#$(warning $(OBJS))
TARGETDIR := $(BINDIR)
TARGETGCC    := $(TARGETDIR)/$(EXECUTABLE)
TARGETMEX := $(TARGETDIR)/$(EXECUTABLE)mex

SMVERSIONFLAGS := -arch=sm_13
NVCCFLAGS := -Xcompiler -fPIC #-Xptxas
GCCFLAGS := -lstdc++
#WXGTKFLAGS	:= -D_FILE_OFFSET_BITS=64 -D_LARGE_FILES -D__WXGTK__ -pthread
TARGET = $(TARGETGCC)
all : $(TARGET)
#all:
#	g++ -c test.cpp $(INCLUDES) -D_LARGE_FILES -D__WXGTK__ -pthread -o test.o

#$(TARGETMEX)

$(OBJDIR)/%.cu.o : %.cu $(CU_DEPS)
	@echo -e "\033[31mCompiling " $< "....\033[0m"
	$(VERBOSE)$(NVCC) -c $< $(NVCCFLAGS) -o $@  $(INCLUDES) $(SMVERSIONFLAGS)
$(OBJDIR)/%.cpp.o : %.cpp $(CPP_DEPS)
	@echo -e "\033[31mCompiling " $< "....\033[0m"
	$(VERBOSE)$(CXX)  -c $< $(GCCFLAGS)  -o $@ $(INCLUDES) #$(WXGTKFLAGS)


$(TARGET): makedirectories $(OBJS)
	@echo -e "\033[31mLinking....\033[0m"
	$(VERBOSE)$(LINK) -o $(TARGET)  $(LKFLAG) $(OBJS) $(LIB)
	@echo -e "\033[31mRunning....\033[0m"
		$(VERBOSE)$(TARGET)

rebuild : clean  $(TARGET)

$(TARGETMEX): makedirectories $(OBJS)
	rm -f *.mexa64
	@echo -e "\033[31m mexLinking....\033[0m"
	$(VERBOSE)$(MEX) $(MEX_DEPS)  $(LKFLAG) $(OBJS) $(INCLUDES) $(LIB)


makedirectories:
	$(VERBOSE)mkdir -p $(OBJDIR)
	$(VERBOSE)mkdir -p $(TARGETDIR)

clean :
	$(VERBOSE)rm -f *.stub.c *.gpu *.cu.cpp *.i *.ii
	$(VERBOSE)rm -f *.cubin *.ptx *.fatbin.c *.hash
	$(VERBOSE)rm -f *.cudafe1.c *.cudafe2.c *.cudafe1.cpp *.cudafe2.cpp
	$(VERBOSE)rm -f $(OBJS)
	$(VERBOSE)rm -f $(TARGET)
	$(VERBOSE)rm -rf $(OBJDIR)
	$(VERBOSE)rm -rf $(TARGETDIR)
#include ./common.mk
