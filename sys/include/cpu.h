#ifndef _CPU_H_
#define _CPU_H_

/* Memory specific features */
#define MEM_GRAN4K_SUPP		0x0001
#define MEM_GRAN16K_SUPP	0x0002
#define MEM_GRAN64K_SUPP	0x0004
#define MEM_SEC_NONSEC_SUPP	0x0008

/* CPU Implementers and other features */
enum cpu_implementers {
	CPU_VENDOR_ARM      = 0x41,
	CPU_VENDOR_BROADCOM = 0x42,
	CPU_VENDOR_CAVIUM   = 0x43,
	CPU_VENDOR_DEC      = 0x44,
	CPU_VENDOR_INFINEON = 0x49,
	CPU_VENDOR_MOTOROLA = 0x4d,
	CPU_VENDOR_NVIDIA   = 0x4e,
	CPU_VENDOR_APCC     = 0x50,
	CPU_VENDOR_QUALCOMM = 0x51,
	CPU_VENDOR_MARVELL  = 0x56,
	CPU_VENDOR_INTEL    = 0x69
};

#define CPU_ENDIAN_EL0	0x0010
#define CPU_ENDIAN_MIX	0x0020

uint8_t cpu_asid_bits = 0;
uint8_t cpu_pa_range = 0;

#endif	/* !_CPU_CPU_H_ */
