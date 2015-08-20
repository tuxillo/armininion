#include <subr.h>
#include <cpufunc.h>

void kern(void)
{
	kprintf("ARMininion kernel initialising...\n");
	kprintf("Running on EL%d\n", get_currentEL());

	return;
}
