#
# OMNeT++/OMNEST Makefile for Hard2
#
# This file was generated with the command:
#  opp_makemake -f --deep -O out
#

# Name of target to be created (-o option)
TARGET = Hard2$(EXE_SUFFIX)

# User interface (uncomment one) (-u option)
USERIF_LIBS = $(ALL_ENV_LIBS) # that is, $(TKENV_LIBS) $(CMDENV_LIBS)
#USERIF_LIBS = $(CMDENV_LIBS)
#USERIF_LIBS = $(TKENV_LIBS)

# C++ include paths (with -I)
INCLUDE_PATH = \
    -I. \
    -IFER \
    -IFER/Hard2-1 \
    -Iresults \
    -Isrc \
    -Isrc/results

# Additional object and library files to link with
EXTRA_OBJS =

# Additional libraries (-L, -l options)
LIBS =

# Output directory
PROJECT_OUTPUT_DIR = out
PROJECTRELATIVE_PATH =
O = $(PROJECT_OUTPUT_DIR)/$(CONFIGNAME)/$(PROJECTRELATIVE_PATH)

# Object files for local .cc and .msg files
OBJS = \
    $O/src/probability_table.o \
    $O/src/rd_tools.o \
    $O/src/rd_node.o \
    $O/src/query_registry.o \
    $O/src/rd_message_m.o \
    $O/src/discovery_m.o \
    $O/src/subquery_m.o \
    $O/src/signal_m.o \
    $O/src/discovery_reply_m.o

# Message files
MSGFILES = \
    src/rd_message.msg \
    src/discovery.msg \
    src/subquery.msg \
    src/signal.msg \
    src/discovery_reply.msg

#------------------------------------------------------------------------------

# Pull in OMNeT++ configuration (Makefile.inc or configuser.vc)

ifneq ("$(OMNETPP_CONFIGFILE)","")
CONFIGFILE = $(OMNETPP_CONFIGFILE)
else
ifneq ("$(OMNETPP_ROOT)","")
CONFIGFILE = $(OMNETPP_ROOT)/Makefile.inc
else
CONFIGFILE = $(shell opp_configfilepath)
endif
endif

ifeq ("$(wildcard $(CONFIGFILE))","")
$(error Config file '$(CONFIGFILE)' does not exist -- add the OMNeT++ bin directory to the path so that opp_configfilepath can be found, or set the OMNETPP_CONFIGFILE variable to point to Makefile.inc)
endif

include $(CONFIGFILE)

# Simulation kernel and user interface libraries
OMNETPP_LIB_SUBDIR = $(OMNETPP_LIB_DIR)/$(TOOLCHAIN_NAME)
OMNETPP_LIBS = -L"$(OMNETPP_LIB_SUBDIR)" -L"$(OMNETPP_LIB_DIR)" -loppmain$D $(USERIF_LIBS) $(KERNEL_LIBS) $(SYS_LIBS)

COPTS = $(CFLAGS)  $(INCLUDE_PATH) -I$(OMNETPP_INCL_DIR)
MSGCOPTS = $(INCLUDE_PATH)

# we want to recompile everything if COPTS changes,
# so we store COPTS into $COPTS_FILE and have object
# files depend on it (except when "make depend" was called)
COPTS_FILE = $O/.last-copts
ifneq ($(MAKECMDGOALS),depend)
ifneq ("$(COPTS)","$(shell cat $(COPTS_FILE) 2>/dev/null || echo '')")
$(shell $(MKPATH) "$O" && echo "$(COPTS)" >$(COPTS_FILE))
endif
endif

#------------------------------------------------------------------------------
# User-supplied makefile fragment(s)
# >>>
# <<<
#------------------------------------------------------------------------------

# Main target
all: $O/$(TARGET)
	$(Q)$(LN) $O/$(TARGET) .

$O/$(TARGET): $(OBJS)  $(wildcard $(EXTRA_OBJS)) Makefile
	@$(MKPATH) $O
	@echo Creating executable: $@
	$(Q)$(CXX) $(LDFLAGS) -o $O/$(TARGET)  $(OBJS) $(EXTRA_OBJS) $(AS_NEEDED_OFF) $(WHOLE_ARCHIVE_ON) $(LIBS) $(WHOLE_ARCHIVE_OFF) $(OMNETPP_LIBS)

.PHONY: all clean cleanall depend msgheaders

.SUFFIXES: .cc

$O/%.o: %.cc $(COPTS_FILE)
	@$(MKPATH) $(dir $@)
	$(qecho) "$<"
	$(Q)$(CXX) -c $(CXXFLAGS) $(COPTS) -o $@ $<

%_m.cc %_m.h: %.msg
	$(qecho) MSGC: $<
	$(Q)$(MSGC) -s _m.cc $(MSGCOPTS) $?

msgheaders: $(MSGFILES:.msg=_m.h)

clean:
	$(qecho) Cleaning...
	$(Q)-rm -rf $O
	$(Q)-rm -f Hard2 Hard2.exe libHard2.so libHard2.a libHard2.dll libHard2.dylib
	$(Q)-rm -f ./*_m.cc ./*_m.h
	$(Q)-rm -f FER/*_m.cc FER/*_m.h
	$(Q)-rm -f FER/Hard2-1/*_m.cc FER/Hard2-1/*_m.h
	$(Q)-rm -f results/*_m.cc results/*_m.h
	$(Q)-rm -f src/*_m.cc src/*_m.h
	$(Q)-rm -f src/results/*_m.cc src/results/*_m.h

cleanall: clean
	$(Q)-rm -rf $(PROJECT_OUTPUT_DIR)

depend:
	$(qecho) Creating dependencies...
	$(Q)$(MAKEDEPEND) $(INCLUDE_PATH) -f Makefile -P\$$O/ -- $(MSG_CC_FILES)  ./*.cc FER/*.cc FER/Hard2-1/*.cc results/*.cc src/*.cc src/results/*.cc

# DO NOT DELETE THIS LINE -- make depend depends on it.
$O/src/discovery_m.o: src/discovery_m.cc \
	src/discovery_m.h \
	src/probability_table.h \
	src/query.h
$O/src/discovery_reply_m.o: src/discovery_reply_m.cc \
	src/discovery_reply_m.h \
	src/probability_table.h \
	src/query.h
$O/src/probability_table.o: src/probability_table.cc \
	src/probability_table.h
$O/src/query_registry.o: src/query_registry.cc \
	src/probability_table.h \
	src/query.h \
	src/query_registry.h \
	src/rd_message_m.h
$O/src/rd_message_m.o: src/rd_message_m.cc \
	src/probability_table.h \
	src/query.h \
	src/rd_message_m.h
$O/src/rd_node.o: src/rd_node.cc \
	src/dht.h \
	src/discovery.h \
	src/discovery_m.h \
	src/discovery_reply_m.h \
	src/probability_table.h \
	src/query.h \
	src/query_registry.h \
	src/rd_message_m.h \
	src/rd_node.h \
	src/rd_tools.h \
	src/rdp.h \
	src/signal_m.h \
	src/subquery_m.h
$O/src/rd_tools.o: src/rd_tools.cc \
	src/rd_tools.h
$O/src/signal_m.o: src/signal_m.cc \
	src/signal_m.h
$O/src/subquery_m.o: src/subquery_m.cc \
	src/probability_table.h \
	src/query.h \
	src/subquery_m.h

