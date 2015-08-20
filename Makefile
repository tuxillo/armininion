# Main GNU Makefile
include Makefile.inc

SUBDIRS = sys/kern
QEMUDBG?= int
QDBGLOG?= /tmp/qemudebug.log
QMEM?=	  1024

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
	@-rm /tmp/qemudebug.log
	qemu-system-aarch64 -D $(QDBGLOG) -d $(QEMUDBG) -serial stdio\
		-M virt -cpu cortex-a57 -m $(QMEM) -kernel \
		$(OBJDIR)/boot.bin -display none
