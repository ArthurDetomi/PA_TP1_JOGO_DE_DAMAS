# ------------------------------------------------------------------------------
# Platform specific tweaks
# ------------------------------------------------------------------------------

ifeq ($(OS),Windows_NT)
	MKDIR=powershell -file .\utils\mkdir.ps1 -dirs
	RMRF=powershell -file .\utils\rm.ps1 -dirs
else
	MKDIR=mkdir -p
	RMRF=rm -rf
endif

# ------------------------------------------------------------------------------
# Variables
# ------------------------------------------------------------------------------

CC=gcc -std=c17
CCPP=g++ -std=c++17
CFLAGS=-g

INCLUDE_DIRS=-I. $(foreach path,$(wildcard ./lib/*), -I$(path)/include/)
LINK_DIRS=
LINKS=
DEFINE=

SRC_DIR=src
SRC=$(wildcard $(SRC_DIR)/*.c) $(wildcard $(SRC_DIR)/**/*.c)
OBJ_DIR=obj
OBJ=$(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))
OBJ_SUB_DIRS=$(sort $(dir $(OBJ)))
EXE=main

# Dev executable with hot reloading
DEV=dev
DEV_INCLUDE_DIRS=-I. -I./lib/cr/
SHARED_OBJECT=$(EXE).so
DEV_SRC_DIR=dev_src
GUEST_SRC_DIR=$(DEV_SRC_DIR)/guest
HOST_SRC=$(DEV_SRC_DIR)/host/cr_host.cpp

DEV_OBJ=$(patsubst $(GUEST_SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(wildcard $(GUEST_SRC_DIR)/*.cpp))
DEV_DEFINES=-DCR_DEBUG

VPATH=$(wildcard $(SRC_DIR)/*)

# ------------------------------------------------------------------------------
# Rules
# ------------------------------------------------------------------------------

all: $(EXE)

$(OBJ_DIR):
	$(MKDIR) "$@"
	$(MKDIR) $(OBJ_SUB_DIRS)

$(EXE): $(OBJ_DIR) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@ $(INCLUDE_DIRS) $(LINK_DIRS) $(LINKS) $(DEFINE)

$(OBJ): $(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE_DIRS) $(LINK_DIRS) $(LINKS) $(DEFINE)

full-clean: clean

clean:
	$(RMRF) $(OBJ_DIR) $(EXE) $(SHARED_OBJECT) *.so $(DEV)

$(DEV): $(HOST_SRC) $(SHARED_OBJECT)
	$(CCPP) $(CFLAGS) $< -o $@ $(DEV_INCLUDE_DIRS) $(DEV_DEFINES)

$(SHARED_OBJECT): $(OBJ_DIR) $(OBJ) $(DEV_OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(DEV_OBJ) -shared -o $@ $(INCLUDE_DIRS) $(LINK_DIRS) $(LINKS) $(DEFINE)

$(DEV_OBJ): $(OBJ_DIR)/%.o: $(GUEST_SRC_DIR)/%.cpp
	$(CCPP) $(CFLAGS) -c $< -o $@ $(INCLUDE_DIRS) $(DEV_INCLUDE_DIRS) $(LINK_DIRS) $(LINKS) $(DEV_DEFINES)


# ------------------------------------------------------------------------------
# Profiles
# ------------------------------------------------------------------------------

release: CFLAGS=-Wno-unused-result -ffunction-sections -fdata-sections -ffast-math -Wl,--gc-sections -Wl,--print-gc-sections
release: all