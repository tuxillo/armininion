TOOLCHAIN?=/opt/cross/bin/aarch64-none-dragonfly-
BASEDIR?=/build/tuxillo/s/armininion
OBJDIR=${BASEDIR}/build
CC=${TOOLCHAIN}gcc

# Kernel files
KFILES=  $(OBJDIR)/boot.o
KFILES+= $(OBJDIR)/uart.o
KFILES+= $(OBJDIR)/caches.o
KFILES+= $(OBJDIR)/kern.o
KFILES+= $(OBJDIR)/lokern.o
KFILES+= $(OBJDIR)/subr_prf.o
