#include <mvisor/mvisor.h>
#include <mvisor/percpu.h>
#include <mvisor/sched.h>

extern unsigned char __percpu_start;
extern unsigned char __percpu_end;
extern unsigned char __percpu_section_size;

unsigned long percpu_offset[CONFIG_NR_CPUS];

void vmm_percpus_init(void)
{
	int i;
	pcpu_t *pcpu;
	size_t size;

	size = (&__percpu_end) - (&__percpu_start);
	memset((char *)&__percpu_start, 0, size);

	for (i = 0; i < CONFIG_NR_CPUS; i++) {
		percpu_offset[i] = (phy_addr_t)(&__percpu_start) +
			(size_t)(&__percpu_section_size) * i;
	}
}

