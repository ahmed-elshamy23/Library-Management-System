sourceFiles := $(wildcard *.c)
executableFile = out.exe
objectFiles := $(patsubst %.c, %.o, $(sourceFiles))
compilerName = gcc
debuggerName = gdb
compilationFlags = -c
debuggingFlags = -g
outputFlags = -o

all: build
	@$(executableFile)

%.o: %.c
	@$(compilerName) $(compilationFlags) $< $(outputFlags) $@

build: $(objectFiles)
	@$(compilerName) $^ $(outputFlags) $(executableFile)