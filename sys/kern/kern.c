#include <subr.h>
#include <cpu.h>
#include <cpufunc.h>

static const char *
cpu_implementer(uint8_t id)
{
	switch(id) {
	case CPU_VENDOR_ARM:
		return "ARM Limited";
	case CPU_VENDOR_BROADCOM:
		return "Broadcom";
	case CPU_VENDOR_CAVIUM:
		return "Cavium";
	case CPU_VENDOR_DEC:
		return "Digital Equipment Corp.";
	case CPU_VENDOR_INFINEON:
		return "Infineon";
	case CPU_VENDOR_MOTOROLA:
		return "Motorola";
	case CPU_VENDOR_NVIDIA:
		return "nVidia";
	case CPU_VENDOR_APCC:
		return "Applied Micro Circuits Corp.";
	case CPU_VENDOR_QUALCOMM:
		return "Qualcomm";
	case CPU_VENDOR_MARVELL:
		return "Marvell Intl.";
	case CPU_VENDOR_INTEL:
		return "Intel";
	default:
		return "Unknown";
	}
}

static void
show_cpuinfo(void)
{
	uint8_t cpuid, cpuarch, cpuvari, cpurev;
	uint16_t cpupart;
	u_int64_t mp;
	uint32_t idr;

	/* Get reg values */
	mp = get_MPIDR_EL1();
	idr = get_MIDR_EL1();

	/* Get CPU identification */
	cpuid = (idr >> 24) & 0xff;
	cpuvari = ((idr << 8) >> 28) & 0xf;
	cpuarch = ((idr << 12) >> 28) & 0xf;
	cpupart = ((idr << 16) >> 20) & 0xfff;
	cpurev = ((idr << 28) >> 28) & 0xf;

	kprintf("CPU: %s Variant=0x%x Arch=0x%x Part=0x%0x Rev=0x%x\n",
	    cpu_implementer(cpuid),
	    cpuvari, cpuarch, cpupart, cpurev);
}

void
kern(void)
{
	kprintf("ARMininion kernel initialising...\n");
	show_cpuinfo();
	kprintf("Running on EL%d\n", get_currentEL());

	return;
}
