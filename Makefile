# Main GNU Makefile
include Makefile.inc

SUBDIRS = sys/kern

all: boot.bin
	-@echo ----------------------------------------------------------
	-@echo Compilation finished at `date`
	-@echo ----------------------------------------------------------

subdirs:
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir; \
	done

boot.bin: subdirs boot.elf
	$(TOOLCHAIN)objcopy -O binary $(OBJDIR)/boot.elf $(OBJDIR)/boot.bin

boot.elf:
	$(TOOLCHAIN)ld -T boot.ld -nostdlib -nodefaultlibs $(KFILES) -o \
		$(OBJDIR)/boot.elf

clean:
	rm -f $(OBJDIR)/*.o $(OBJDIR)/boot.elf $(OBJDIR)/boot.bin

run: clean boot.bin
	qemu-system-aarch64 -serial stdio -M virt -cpu cortex-a57 -m 512 -kernel \
		$(OBJDIR)/boot.bin -display none
