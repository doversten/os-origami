# Path to cross tools

MIPS_PREFIX=/it/sw/cross/mips-idt/bin/mips-idt-elf

EXECUTABLES=$(addprefix bin/, boot)


# gcc flags for the MIPS architecture:
#  -EL     : Little endian
#  -G0     : Always use small data (using register gp)
#  -mips32 : Compile for a 32-bit MIPS architecture
#

ARCH=-EL -G0 -mips32

# Other gcc flags

CFLAGS	+= -ggdb -Wall -fno-builtin -I include

# Compiler and linker commands

CC=$(MIPS_PREFIX)-gcc

# Tell the linker where to start the text segment. 
LD=$(MIPS_PREFIX)-ld -Ttext 80020000


# Path to Simics installation

SIMICS=/home/lisu9273/simics-workspace 




#### RULE USED TO START SIMICS 

do_boot: bin/boot
	./scripts/run.sh $(SIMICS) $<

#### RULES TO BUILD BINARIES FROM OBJECT FILES

bin/boot: $(addprefix build/, boot.o console.o main_loop.o interrupt.o)
	$(LD) $(ARCH) -o $@ $^

#### Add dependency on headerfile of various tty.o files

build/console.o: src/console.c include/console.h include/ns16550.h
	$(CC) $(ARCH) $(CFLAGS)  -c $< -o $@	

build/main_loop.o: src/main_loop.c include/console.h
	$(CC) $(ARCH) $(CFLAGS)  -c $< -o $@

build/interrupt.o: src/interrupt.c include/console.h include/registers.h include/ns16550.h include/asm.h include/mips4kc.h
	$(CC) $(ARCH) $(CFLAGS)  -c $< -o $@	

###### GENERIC BUILD PATTERNS ########

build/%.o: src/%.c
	$(CC) $(ARCH) $(CFLAGS)  -c $< -o $@	

build/%.o: src/%.S
	$(CC) $(ARCH) $(CFLAGS)  -c $< -o $@


clean: 
	pwd
	rm -f build/*.o
	rm -f include/*~ include/#* include/*#
	rm -f src/*~ src/#* src/*#
	rm -f scripts/*~ scripts/#* scripts/*#
	rm -f ${EXECUTABLES}	
