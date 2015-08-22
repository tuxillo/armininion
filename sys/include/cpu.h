#ifndef _CPU_H_
#define _CPU_H_

/* Memory specific features */
#define MEM_GRAN4K_SUPP		0x0001
#define MEM_GRAN16K_SUPP	0x0002
#define MEM_GRAN64K_SUPP	0x0004
#define MEM_SEC_NONSEC_SUPP	0x0008

/* CPU Implementers and other features */
enum cpu_implementers {
	CPU_VENDOR_ARM = 0x41,
	CPU_VENDOR_BROADCOM,
	CPU_VENDOR_CAVIUM,
	CPU_VENDOR_DEC,
	CPU_VENDOR_INFINEON,
	CPU_VENDOR_MOTOROLA,
	CPU_VENDOR_NVIDIA,
	CPU_VENDOR_APCC,
	CPU_VENDOR_QUALCOMM,
	CPU_VENDOR_MARVELL,
	CPU_VENDOR_INTEL
};

#define CPU_ENDIAN_EL0	0x0010
#define CPU_ENDIAN_MIX	0x0020

uint8_t cpu_asid_bits = 0;
uint8_t cpu_pa_range = 0;

#endif	/* !_CPU_CPU_H_ */
