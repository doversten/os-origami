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

#SIMICS=/home/lisu9273/simics-workspace 
SIMICS=/home/thno6071/simics-workspace 




#### RULE USED TO START SIMICS 

do_boot: bin/boot
	./scripts/run.sh $(SIMICS) $<

#### RULES TO BUILD BINARIES FROM OBJECT FILES

bin/boot: $(addprefix build/, boot.o init.o malta_display.o syscall.o console.o folding.o interrupt.o scheduler.o pcb_queue.o pcb.o api.o malta_scroller.o message_pool.o og_stdlib.o programs.o random.o supervision.o dining_philo.o increment.o fibonacci.o shell.o top.o ring.o input_queue.o char_fifo.o change_priority.o kill_process.o supervisor_test.o help.o credit.o)
	$(LD) $(ARCH) -o $@ $^

#### Add dependency on headerfile of various *.o files

build/api.o: src/api.c include/pcb.h include/syscall.h include/api.h include/console.h include/scheduler.h include/types.h include/malta_display.h include/message_pool.h include/message.h include/random.h include/supervision.h include/pids.h 
	$(CC) $(ARCH) $(CFLAGS)  -c $< -o $@

build/change_priority.o: src/change_priority.c include/api.h include/og_stdlib.h
	$(CC) $(ARCH) $(CFLAGS)  -c $< -o $@

build/char_fifo.o: src/char_fifo.c include/char_fifo.h include/types.h
	$(CC) $(ARCH) $(CFLAGS)  -c $< -o $@

build/console.o: src/console.c include/console.h include/ns16550.h include/char_fifo.h include/scheduler.h include/input_queue.h
	$(CC) $(ARCH) $(CFLAGS)  -c $< -o $@

build/credit.o: src/credit.c include/api.h
	$(CC) $(ARCH) $(CFLAGS)  -c $< -o $@

build/dining_philo.o: src/dining_philo.c include/api.h include/og_stdlib.h
	$(CC) $(ARCH) $(CFLAGS)  -c $< -o $@

build/fibonacci.o: src/fibonacci.c include/api.h include/og_stdlib.h
	$(CC) $(ARCH) $(CFLAGS)  -c $< -o $@

build/folding.o: src/folding.c include/programs.h include/api.h include/og_stdlib.h
	$(CC) $(ARCH) $(CFLAGS)  -c $< -o $@

build/help.o: src/help.c include/api.h include/og_stdlib.h
	$(CC) $(ARCH) $(CFLAGS)  -c $< -o $@

build/increment.o: src/increment.c include/api.h include/og_stdlib.h
	$(CC) $(ARCH) $(CFLAGS)  -c $< -o $@

build/init.o: src/init.c include/console.h include/ns16550.h include/registers.h include/asm.h include/mips4kc.h include/scheduler.h include/malta_display.h include/programs.h
	$(CC) $(ARCH) $(CFLAGS)  -c $< -o $@

build/input_queue.o: src/input_queue.c include/input_queue.h include/types.h
	$(CC) $(ARCH) $(CFLAGS)  -c $< -o $@

build/interrupt.o: src/interrupt.c include/console.h include/ns16550.h include/registers.h include/asm.h include/mips4kc.h include/scheduler.h include/syscall.h
	$(CC) $(ARCH) $(CFLAGS)  -c $< -o $@

build/kill_process.o: src/kill_process.c include/api.h include/og_stdlib.h
	$(CC) $(ARCH) $(CFLAGS)  -c $< -o $@

build/malta_display.o: src/malta_display.c include/malta_display.h
	$(CC) $(ARCH) $(CFLAGS)  -c $< -o $@

build/malta_scroller.o: src/malta_scroller.c include/api.h include/og_stdlib.h
	$(CC) $(ARCH) $(CFLAGS)  -c $< -o $@

build/message_pool.o: src/message_pool.c include/message.h include/message_pool.h include/pcb.h include/scheduler.h include/types.h
	$(CC) $(ARCH) $(CFLAGS)  -c $< -o $@	

build/og_stdlib.o: src/og_stdlib.c include/types.h include/og_stdlib.h
	$(CC) $(ARCH) $(CFLAGS)  -c $< -o $@
	
build/pcb_queue.o: src/pcb_queue.c include/pcb_queue.h include/pcb.h include/types.h include/console.h
	$(CC) $(ARCH) $(CFLAGS)  -c $< -o $@	
	
build/pcb.o: src/pcb.c include/pcb.h include/types.h include/stack.h include/message_pool.h include/pids.h
	$(CC) $(ARCH) $(CFLAGS)  -c $< -o $@

build/programs.o: src/programs.c include/programs.h include/og_stdlib.h include/console.h
	$(CC) $(ARCH) $(CFLAGS)  -c $< -o $@

build/random.o: src/random.c include/types.h include/random.h
	$(CC) $(ARCH) $(CFLAGS)  -c $< -o $@
	
build/ring.o: src/ring.c include/api.h include/og_stdlib.h
	$(CC) $(ARCH) $(CFLAGS)  -c $< -o $@

build/scheduler.o: src/scheduler.c include/pcb.h include/stack.h include/console.h include/asm.h include/types.h include/pcb_queue.h include/scheduler.h include/message_pool.h include/programs.h include/malta_display.h
	$(CC) $(ARCH) $(CFLAGS)  -c $< -o $@

build/shell.o: src/shell.c include/api.h include/programs.h include/og_stdlib.h
	$(CC) $(ARCH) $(CFLAGS)  -c $< -o $@

build/supervision.o: src/supervision.c include/pcb.h include/scheduler.h include/supervision.h
	$(CC) $(ARCH) $(CFLAGS)  -c $< -o $@

build/supervisor_test.o: src/supervisor_test.c include/api.h
	$(CC) $(ARCH) $(CFLAGS)  -c $< -o $@

build/top.o: src/top.c include/api.h include/og_stdlib.h
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

pack: clean
	tar -czvf origami_os.tar.gz src/*.c include/*.h scripts/*.* Makefile
