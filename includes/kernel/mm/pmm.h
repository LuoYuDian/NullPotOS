// 创建于2024.12.15
// NullPotOS 物理内存

#include <stdint.h>
#include <stddef.h>

#define PM_PAGE_SIZE            4096
#define PM_BMP_MAX_SIZE        (128 * 1024)

void pmm_mark_page_free(uintptr_t ppn);

void pmm_mark_page_occupied(uintptr_t ppn);

void pmm_mark_chunk_free(uintptr_t start_ppn, size_t page_count);

void pmm_mark_chunk_occupied(uintptr_t start_ppn, size_t page_count);

void* pmm_alloc_page();

void pmm_init(uintptr_t mem_upper_lim);

int pmm_free_page(void* page);