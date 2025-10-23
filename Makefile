EXAMPLE_DIR       ?= $(shell dirname `pwd`)
MOOSE_DIR         ?= $(shell dirname $(EXAMPLE_DIR))
FRAMEWORK_DIR     ?= $(MOOSE_DIR)/framework

# Simple delegating Makefile — expects to find MOOSE framework makefiles.
include $(FRAMEWORK_DIR)/build.mk
include $(FRAMEWORK_DIR)/moose.mk

APPLICATION_NAME := ex03_coupling_app
APPLICATION_DIR  := $(shell pwd)
include $(FRAMEWORK_DIR)/app.mk

ex03_srcfiles := $(shell find $(APPLICATION_DIR) -name "*.C")

test: all
	@echo "Build complete (or failed) — run the executable via MOOSE runner with ex03.i"
