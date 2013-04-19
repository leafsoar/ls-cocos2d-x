CC      = gcc
CXX     = g++
TARGET	= leafsoar
CCFLAGS = -Wall
CXXFLAGS = -Wall
VISIBILITY = 

# COCOS2DX_ROOT = /home/leafsoar/...

COCOS2DX_PATH = $(COCOS2DX_ROOT)/cocos2dx
INCLUDES =  -I../ \
			-I../Classes \
			-I$(COCOS2DX_PATH) \
			-I$(COCOS2DX_PATH)/platform/third_party/linux \
			-I$(COCOS2DX_PATH)/platform/third_party/linux/libfreetype2 \
			-I$(COCOS2DX_PATH)/cocoa \
			-I$(COCOS2DX_PATH)/include \
			-I$(COCOS2DX_PATH)/platform \
			-I$(COCOS2DX_PATH)/platform/linux \
			-I$(COCOS2DX_PATH)/platform/third_party/linux/glew-1.7.0/glew-1.7.0/include/ \
			-I$(COCOS2DX_PATH)/kazmath/include \
			-I$(COCOS2DX_PATH)/platform/third_party/linux/libxml2 \
			-I$(COCOS2DX_PATH)/platform/third_party/linux/libjpeg  \
			-I$(COCOS2DX_ROOT)/CocosDenshion/include \
#			-I$(COCOS2DX_ROOT)/extensions/ \

DEFINES = -DLINUX

define all-cpp-files
$(patsubst ./%,%, $(shell find  ../Classes ./ -name "*.cpp"))  
endef

define all-cpp-dir
$(patsubst ../%,obj/%, $(shell find  ../Classes -type d))  
endef

OBJDIR=obj/Classes

OBJECTS=$(patsubst %.cpp,$(OBJDIR)/%.o,$(call all-cpp-files))
OBJECTS_DIR=$(call all-cpp-dir)

# 如果目录不存在，则创建相应的目录
$(shell mkdir -p obj)
$(shell mkdir -p $(OBJECTS_DIR))

#echo:
#	@echo $(OBJECTS_DIR)

#OBJECTS = ./main.o \
#        ../Classes/AppDelegate.o

LBITS := $(shell getconf LONG_BIT)
ifeq ($(LBITS),64)
STATICLIBS_DIR = $(COCOS2DX_ROOT)/cocos2dx/platform/third_party/linux/libraries/lib64
else
STATICLIBS_DIR = $(COCOS2DX_ROOT)/cocos2dx/platform/third_party/linux/libraries
endif
STATICLIBS = 
STATICLIBS = $(STATICLIBS_DIR)/libfreetype.a \
				$(STATICLIBS_DIR)/libxml2.a \
				$(STATICLIBS_DIR)/libpng.a \
				$(STATICLIBS_DIR)/libjpeg.a \
				$(STATICLIBS_DIR)/libtiff.a \
#				$(STATICLIBS_DIR)/libGLEW.a \

SHAREDLIBS = 
ifeq ($(LBITS),64)
SHAREDLIBS_DIR = $(COCOS2DX_ROOT)/CocosDenshion/third_party/fmod/lib64/api/lib
SHAREDLIBS = -L$(SHAREDLIBS_DIR) -lfmodex64
else
SHAREDLIBS_DIR = $(COCOS2DX_ROOT)/CocosDenshion/third_party/fmod/api/lib
SHAREDLIBS = -L$(SHAREDLIBS_DIR) -lfmodex
endif

SHAREDLIBS += -lglfw -lGL
SHAREDLIBS += -Wl,-rpath,$(SHAREDLIBS_DIR)
SHAREDLIBS += -L$(COCOS2DX_ROOT)/cocos2dx/platform/third_party/linux/glew-1.7.0/glew-1.7.0/lib -lGLEW
SHAREDLIBS += -Wl,-rpath,$(COCOS2DX_ROOT)/cocos2dx/platform/third_party/linux/glew-1.7.0/glew-1.7.0/lib


BIN_DIR_ROOT=bin
BIN_DIR = $(BIN_DIR_ROOT)

debug: BIN_DIR = $(BIN_DIR_ROOT)/debug
debug: CCFLAGS += -g3 -O0
debug: CXXFLAGS += -g3 -O0
debug: SHAREDLIBS += -L$(COCOS2DX_ROOT)/lib/linux/Debug -lcocos2d -lrt -lz -lcocosdenshion
debug: SHAREDLIBS += -Wl,-rpath,$(COCOS2DX_ROOT)/lib/linux/Debug/
debug: DEFINES += -DDEBUG
debug: $(TARGET)

release: BIN_DIR = $(BIN_DIR_ROOT)/release
release: CCFLAGS += -O3
release: CXXFLAGS += -O3
release: SHAREDLIBS += -L.$(COCOS2DX_ROOT)/lib/linux/Release -lcocos2d -lrt -lz -lcocosdenshion
release: SHAREDLIBS += -Wl,-rpath,$(COCOS2DX_ROOT)/lib/linux/Release/
release: DEFINES += -DNDEBUG
release: $(TARGET)

####### Build rules
$(TARGET): $(OBJECTS) 
	mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(DEFINES) $(OBJECTS) -o $(BIN_DIR)/$(TARGET) $(SHAREDLIBS) $(STATICLIBS)

####### Compile
$(OBJDIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(DEFINES) $(VISIBILITY) -c $< -o $@

%.o: %.c
	$(CC) $(CCFLAGS) $(INCLUDES) $(DEFINES) $(VISIBILITY) -c $< -o $@

clean: 
	rm -f $(OBJECTS) $(TARGET) core
