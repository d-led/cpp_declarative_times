# GNU Make solution makefile autogenerated by Premake

.NOTPARALLEL:

ifndef config
  config=debug_x32
endif

ifndef verbose
  SILENT = @
endif

ifeq ($(config),debug_x32)
  times_benchmark_config = debug_x32
  times_test_config = debug_x32
endif
ifeq ($(config),debug_x64)
  times_benchmark_config = debug_x64
  times_test_config = debug_x64
endif
ifeq ($(config),release_x32)
  times_benchmark_config = release_x32
  times_test_config = release_x32
endif
ifeq ($(config),release_x64)
  times_benchmark_config = release_x64
  times_test_config = release_x64
endif

PROJECTS := times_benchmark times_test

.PHONY: all clean help $(PROJECTS) 

all: $(PROJECTS)

times_benchmark:
ifneq (,$(times_benchmark_config))
	@echo "==== Building times_benchmark ($(times_benchmark_config)) ===="
	@${MAKE} --no-print-directory -C . -f times_benchmark.make config=$(times_benchmark_config)
endif

times_test:
ifneq (,$(times_test_config))
	@echo "==== Building times_test ($(times_test_config)) ===="
	@${MAKE} --no-print-directory -C . -f times_test.make config=$(times_test_config)
endif

clean:
	@${MAKE} --no-print-directory -C . -f times_benchmark.make clean
	@${MAKE} --no-print-directory -C . -f times_test.make clean

help:
	@echo "Usage: make [config=name] [target]"
	@echo ""
	@echo "CONFIGURATIONS:"
	@echo "  debug_x32"
	@echo "  debug_x64"
	@echo "  release_x32"
	@echo "  release_x64"
	@echo ""
	@echo "TARGETS:"
	@echo "   all (default)"
	@echo "   clean"
	@echo "   times_benchmark"
	@echo "   times_test"
	@echo ""
	@echo "For more information, see http://industriousone.com/premake/quick-start"
