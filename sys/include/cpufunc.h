#ifndef _CPUFUNC_H_
#define _CPUFUNC_H_

static __inline int
get_currentEL(void)
{
	int el;

	__asm __volatile("mrs %0, CurrentEL": "=r" (el));

	return el >> 2;
}

static __inline uint32_t
get_SPSel(void)
{
	uint32_t sps;

	__asm __volatile("mrs %0, SPSel" : "=r" (sps));

	return sps;
}

static __inline uint32_t
get_DAIF(void)
{
	uint32_t d;

	__asm __volatile("mrs %0, DAIF" : "=r" (d));

	return d;
}

static __inline u_int64_t
get_MPIDR_EL1(void)
{
	u_int64_t mp;

	__asm __volatile("mrs %0, MPIDR_EL1" : "=r" (mp));

	return mp;
}

static __inline uint32_t
get_MIDR_EL1(void)
{
	uint32_t idr;

	__asm __volatile("mrs %0, MIDR_EL1" : "=r" (idr));

	return idr;
}


#endif	/* !_CPU_CPUFUNC_H_ */
