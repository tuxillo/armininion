#ifndef _CPUFUNC_H_
#define _CPUFUNC_H_

static __inline int
get_currentEL(void)
{
	int el;

	__asm __volatile("mrs %0, CurrentEL": "=r" (el));

	return el >> 2;
}
#endif	/* !_CPU_CPUFUNC_H_ */
