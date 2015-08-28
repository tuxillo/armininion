include ../../Makefile.inc

CFLAGS+= -I$(BASEDIR)/sys/include

all: $(KFILES)

$(OBJDIR)/%.o: %.S
	$(COMPILE.c) $< -o $@

$(OBJDIR)/%.o: %.c
	$(COMPILE.c) -fPIE -ffreestanding $< -o $@

clean:
	-rm -fr $(OBJDIR)/*.o
