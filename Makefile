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
#SIMICS=/home/thno6071/simics-workspace 




#### RULE USED TO START SIMICS 

do_boot: bin/boot
	./scripts/run.sh $(SIMICS) $<

#### RULES TO BUILD BINARIES FROM OBJECT FILES

bin/boot: $(addprefix build/, boot.o init.o malta_display.o syscall.o console.o folding.o interrupt.o bounded_fifo.o scheduler.o pcb_queue.o pcb.o api.o malta_scroller.o message_pool.o)
	$(LD) $(ARCH) -o $@ $^

#### Add dependency on headerfile of various tty.o files

build/console.o: src/console.c include/console.h include/ns16550.h include/bounded_fifo.h
	$(CC) $(ARCH) $(CFLAGS)  -c $< -o $@	

build/main_loop.o: src/main_loop.c include/console.h include/scheduler.h  include/pcb.h
	$(CC) $(ARCH) $(CFLAGS)  -c $< -o $@

build/interrupt.o: src/interrupt.c include/console.h include/registers.h include/ns16550.h include/asm.h include/mips4kc.h include/syscall.h
	$(CC) $(ARCH) $(CFLAGS)  -c $< -o $@	

build/bounded_fifo.o: src/bounded_fifo.c include/bounded_fifo.h include/types.h
	$(CC) $(ARCH) $(CFLAGS)  -c $< -o $@

build/scheduler.o: src/scheduler.c include/pcb.h include/stack.h include/pcb_queue.h
	$(CC) $(ARCH) $(CFLAGS)  -c $< -o $@

build/pcb_queue.o: src/pcb_queue.c include/pcb.h include/pcb_queue.h include/types.h include/console.h
	$(CC) $(ARCH) $(CFLAGS)  -c $< -o $@

build/pcb.o: src/pcb.c include/pcb.h include/types.h include/stack.h
	$(CC) $(ARCH) $(CFLAGS)  -c $< -o $@

build/api.o: src/api.c include/pcb.h include/syscall.h include/api.h include/console.h include/scheduler.h include/malta_display.h
	$(CC) $(ARCH) $(CFLAGS)  -c $< -o $@

build/malta_display.o: src/malta_display.c include/malta_display.h
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
