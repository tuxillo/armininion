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

static uint64_t
mem_features(void)
{
	uint64_t cpureg, flags;
	uint32_t reg;
	uint8_t field;

	flags = 0;

	/*
	 * ID_AA64MMFR0_EL1 on D7.2.42
	 * 	63:32 is RES0 so not useful for us
	 */
	cpureg = get_ID_AA64MMFR0_EL1();
	reg = (uint32_t)cpureg;

	/* Find out supported granule sizes */
	field = (reg >> 28) & 0xf;
	if (field == 0)
		flags |= MEM_GRAN4K_SUPP;

	field = ((reg << 4) >> 28) & 0xf;
	if (field == 0)
		flags |= MEM_GRAN16K_SUPP;

	field = ((reg << 8) >> 28) & 0xf;
	if (field == 0)
		flags |= MEM_GRAN64K_SUPP;

	field = ((reg << 16) >> 28) & 0xf;
	if (field == 1)
		flags |= MEM_SEC_NONSEC_SUPP;

	field = ((reg << 24) >> 28) & 0xf;
	if ((field & 0x2) == 0x2)
		cpu_asid_bits = 16;
	else
		cpu_asid_bits = 8;

	field = ((reg << 28) >> 28) & 0xf;
	switch (field) {
	case 0:
		cpu_pa_range = 32;
		break;
	case 1:
		cpu_pa_range = 36;
		break;
	case 2:
		cpu_pa_range = 40;
		break;
	case 3:
		cpu_pa_range = 42;
		break;
	case 4:
		cpu_pa_range = 44;
		break;
	case 5:
		cpu_pa_range = 48;
		break;
	default:
		cpu_pa_range = 32;
	}

	return flags;
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

static void
show_meminfo()
{
	uint64_t flags = mem_features();

	kprintf("Memory: Granules %s%s%s. %s ASID: %d bits PA range: %d bits\n",
	    flags & MEM_GRAN4K_SUPP ? "4K" : "",
	    flags & MEM_GRAN16K_SUPP ? ",16K" : "",
	    flags & MEM_GRAN64K_SUPP ? ",64K" : "",
	    flags & MEM_SEC_NONSEC_SUPP ? "SEC/NON-SEC" : "NO SEC",
	    cpu_asid_bits,
	    cpu_pa_range);

}

void
kern(void)
{
	kprintf("ARMininion kernel initialising...\n");
	show_cpuinfo();
	show_meminfo();
	for (;;);

	return;
}
