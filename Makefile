.SUFFIXES:

ifeq ($(strip $(DEVKITARM)),)
$(error "Please set DEVKITARM in your environment. export DEVKITARM=<path to>devkitARM")
endif

TOPDIR 		?= 	$(CURDIR)
include $(DEVKITARM)/3ds_rules

CTRPFLIB	?=	$(DEVKITPRO)/libctrpf

NAME		:=	mk7-pid-grabber
ABOUT		:=	$(NAME) is a CTRPluginFramework for Mario Kart 7.
GITHUB		:=	https://github.com/H4x0rSpooky/mk7-pid-grabber

TARGET		:= 	$(notdir $(CURDIR))
PLGINFO 	:= 	ctrpf.plgInfo

BUILD		:= 	build
DEBUG		:=	debug

INCLUDES	:= 	include \
				include/ctrpf \
				include/glaze \
				include/base

SOURCES 	:= 	src \
				src/base \
				src/base/entries \
				src/base/features \
				src/base/hook_types \
				src/base/hooks \
				src/base/memory \
				src/base/services

#---------------------------------------------------------------------------------
# options for code generation
#---------------------------------------------------------------------------------
ARCH		:= -march=armv6k -mtune=mpcore -mfloat-abi=hard -mtp=soft

DEFINES 	:= -D__3DS__ -DNNSDK -DNAME="\"$(NAME)\"" -DABOUT="\"$(ABOUT)\"" -DGITHUB="\"$(GITHUB)\""

CFLAGS		:= $(ARCH) -Os -mword-relocations -fomit-frame-pointer -ffunction-sections -fno-strict-aliasing -Wno-psabi
CFLAGS		+= $(INCLUDE) $(DEFINES)

CXXFLAGS	:= $(CFLAGS) -fno-rtti -fno-exceptions -std=gnu++23

ASFLAGS		:= $(ARCH)
LDFLAGS		:= -T $(TOPDIR)/3gx.ld $(ARCH) -Os -fno-lto -Wl,--gc-sections,--strip-discarded,--strip-debug

LIBS		:= -lctrpf -lctru
LIBDIRS		:= $(CTRPFLIB) $(CTRULIB) $(PORTLIBS)

#---------------------------------------------------------------------------------
# no real need to edit anything past this point unless you need to add additional
# rules for different file extensions
#---------------------------------------------------------------------------------
ifneq ($(BUILD),$(notdir $(CURDIR)))
#---------------------------------------------------------------------------------

export OUTPUT	:=	$(CURDIR)/$(NAME)
export TOPDIR	:=	$(CURDIR)
export VPATH	:=	$(foreach dir,$(SOURCES),$(CURDIR)/$(dir)) \
					$(foreach dir,$(DATA),$(CURDIR)/$(dir))

export DEPSDIR	:=	$(CURDIR)/$(BUILD)

CFILES			:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.c)))
CPPFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.cpp)))
SFILES			:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.s)))

export LD 		:= 	$(CXX)
export OFILES	:=	$(CPPFILES:.cpp=.o) $(CFILES:.c=.o) $(SFILES:.s=.o)
export INCLUDE	:=	$(foreach dir,$(INCLUDES),-I $(CURDIR)/$(dir) ) \
					$(foreach dir,$(LIBDIRS),-I $(dir)/include) \
					-I $(CURDIR)/$(BUILD)

export LIBPATHS	:=	$(foreach dir,$(LIBDIRS),-L $(dir)/lib)

.PHONY: $(BUILD) clean all

#---------------------------------------------------------------------------------
all: $(BUILD)

$(BUILD):
	@[ -d $(DEBUG) ] || mkdir -p $(DEBUG)
	@[ -d $@ ] || mkdir -p $@
	@$(MAKE) --no-print-directory -C $(BUILD) -f $(CURDIR)/Makefile

#---------------------------------------------------------------------------------
clean:
	@echo clean ... 
	@rm -fr $(DEBUG) $(BUILD) $(OUTPUT).3gx $(OUTPUT).elf

re: clean all

#---------------------------------------------------------------------------------

else

DEPENDS	:=	$(OFILES:.o=.d)

#---------------------------------------------------------------------------------
# main targets
#---------------------------------------------------------------------------------
$(OUTPUT).3gx : $(OFILES)

#---------------------------------------------------------------------------------
# you need a rule like this for each extension you use as binary data
#---------------------------------------------------------------------------------
%.bin.o	:	%.bin
#---------------------------------------------------------------------------------
	@echo $(notdir $<)
	@$(bin2o)

#---------------------------------------------------------------------------------
#.PRECIOUS: %.elf
%.3gx: %.elf
#---------------------------------------------------------------------------------
	@echo creating $(notdir $@)
	@3gxtool -d -s $(word 1, $^) $(TOPDIR)/$(PLGINFO) $@
	@-mv $(TOPDIR)/$(BUILD)/*.lst $(TOPDIR)/$(DEBUG)/
	@-mv $(TOPDIR)/*.elf $(TOPDIR)/$(DEBUG)/
	@echo $(NAME).3gx successfully created!

-include $(DEPENDS)

#---------------------------------------------------------------------------------
endif
