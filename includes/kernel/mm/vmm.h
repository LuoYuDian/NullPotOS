// 创建于2024.12.14
// NullPotOS 虚拟内存

#include <stdint.h>
#include <stddef.h>
#include <kernel/mm/page.h>
#include <kernel/error/error.h>

void vmm_init();

ptd_t* vmm_init_pd();

void* vmm_map_page(void* vpn, void* ppn, pt_attr dattr, pt_attr tattr);

void* vmm_alloc_page(void* vpn, pt_attr dattr, pt_attr tattr);

void vmm_unmap_page(void* vpn);

ptd_t* get_pd();

void set_pd(ptd_t* pd);

void* vmm_v2p(void* va);