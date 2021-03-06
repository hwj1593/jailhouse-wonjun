/*
 * Jailhouse, a Linux-based partitioning hypervisor
 *
 * Configuration for linux inmate, 1 CPU, ~60 MB RAM, 1 serial port
 *
 * Copyright (c) Siemens AG, 2013-2015
 *
 * Authors:
 *  Jan Kiszka <jan.kiszka@siemens.com>
 *
 * This work is licensed under the terms of the GNU GPL, version 2.  See
 * the COPYING file in the top-level directory.
 */

#include <linux/types.h>
#include <jailhouse/cell-config.h>

#define ARRAY_SIZE(a) sizeof(a) / sizeof(a[0])

struct {
	struct jailhouse_cell_desc cell;
	__u64 cpus[1];
	struct jailhouse_memory mem_regions[3];
	//struct jailhouse_cache cache_regions[0];
	struct jailhouse_irqchip irqchips[1];
	__u8 pio_bitmap[0x2000];
//	struct jailhouse_pci_device pci_devices[0];
} __attribute__((packed)) config = {
	.cell = {
		.signature = JAILHOUSE_CELL_DESC_SIGNATURE,
		.name = "rtems-demo",
		.flags = JAILHOUSE_CELL_PASSIVE_COMMREG,

		.cpu_set_size = sizeof(config.cpus),
		.num_memory_regions = ARRAY_SIZE(config.mem_regions),
		.num_cache_regions = 0,
		.num_irqchips = ARRAY_SIZE(config.irqchips),
		.pio_bitmap_size = ARRAY_SIZE(config.pio_bitmap),
		.num_pci_devices = 0,
		.num_pci_caps = 0,
	},

	.cpus = {
		0x8,
	},

	.mem_regions = {
		/* low RAM */ {
			.phys_start = 0x3b600000,
			.virt_start = 0,
			.size = 0x00700000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_EXECUTE | JAILHOUSE_MEM_DMA |
				JAILHOUSE_MEM_LOADABLE,
		},
		/* communication region */ {
			.virt_start = 0x00900000,
			.size = 0x00001000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_COMM_REGION,
		},
		/* high RAM */ {
			.phys_start = 0x3bc00000,
			.virt_start = 0x01000000,
			.size = 0x35ff000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_EXECUTE | JAILHOUSE_MEM_DMA |
				JAILHOUSE_MEM_LOADABLE,
		},
		/* MemRegion: fec00000-fec003ff : IOAPIC */
		//{
		//	.phys_start = 0xfec00000,
		//	.virt_start = 0xfec00000,
		//	.size = 0x1000,
		//	.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		//},
		/* MemRegion: fed00000-fed003ff : PNP0103:00 */
		//{
		//	.phys_start = 0xfed00000,
		//	.virt_start = 0xfed00000,
		//	.size = 0x1000,
		//	.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		//},
		/* e100 BAR0 */ //{
		//	.phys_start = 0x80040000,
		//	.virt_start = 0x80040000,
		//	.size = 0x00001000,
		//	.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		//},

		/* IVSHMEM shared memory region */
		//{
		//	.phys_start = 0x3f1ff000,
		//	.virt_start = 0x3f1ff000,
		//	.size = 0x1000,
		//	.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
		//		JAILHOUSE_MEM_ROOTSHARED,
		//},
	},
/*
	.cache_regions = {
		{
			.start = 0,
			.size = 2,
			.type = JAILHOUSE_CACHE_L3,
		},
	},
*/
	.irqchips = {
		/* IOAPIC */ {
			.address = 0xfec00000,
			.id = 0xff01,
			.pin_bitmap = 0x000200, /* ACPI IRQ */
		},
	},

	.pio_bitmap = {
		[     0/8 ...   0x1f/8] = -1, /* floppy DMA controller */
		[  0x20/8 ...  0x3f7/8] = -1,
		[ 0x3f8/8 ...  0x3ff/8] = 0, /* serial1 */
		[ 0x400/8 ...  0x5ff/8] = -1,
		[ 0x600/8 ...  0x607/8] = 0xf0, /* acpi-evt */
		[ 0x608/8 ...  0x7ff/8] = -1,
		[ 0x800/8 ...  0x807/8] = 0xf0 /* apci-pm1a */,
		[ 0x808/8 ... 0xe00f/8] = -1,
		[0xe010/8 ... 0xe017/8] = 0, /* OXPCIe952 serial1 and e100 */
		[0xe018/8 ... 0xffff/8] = -1,
	},

	//.pci_devices = { 
		//{ /* e100 */
		//	.type = JAILHOUSE_PCI_TYPE_DEVICE,
		//	.domain = 0x0000,
		//	.bdf = 0x18,
		//},
		//{
		//	.type = JAILHOUSE_PCI_TYPE_IVSHMEM,
		//	.domain = 0x0,
		//	.bdf = (0x0f<<3),
		//	.shmem_region = 3,
		//	.num_msix_vectors = 1,
		//},
	//},
};
	