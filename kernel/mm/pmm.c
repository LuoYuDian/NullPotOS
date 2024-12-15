// 创建于2024.12.15
// NullPotOS 物理内存

#include <kernel/mm/page.h>
#include <kernel/mm/pmm.h>

#define MARK_PG_AUX_VAR(ppn)                                                   \
    uint32_t group = ppn / 8;                                                  \
    uint32_t msk = (0x80U >> (ppn % 8));                                       \

#define MARK_CHUNK_AUX_VAR(start_ppn, page_count)                              \
    uint32_t group = start_ppn / 8;                                            \
    uint32_t offset = start_ppn % 8;                                           \
    uint32_t group_count = (page_count + offset) / 8;                          \
    uint32_t remainder = (page_count + offset) % 8;                            \
    uint32_t leading_shifts =                                                  \
      (page_count + offset) < 8 ? page_count : 8 - offset;

uint8_t pm_bitmap[PM_BMP_MAX_SIZE];

uintptr_t max_pg;

void pmm_mark_page_free(uintptr_t ppn)
{
    MARK_PG_AUX_VAR(ppn)
    pm_bitmap[group] = pm_bitmap[group] & ~msk;
}

void pmm_mark_page_occupied(uintptr_t ppn)
{
    MARK_PG_AUX_VAR(ppn)
    pm_bitmap[group] = pm_bitmap[group] | msk;
}

void pmm_mark_chunk_free(uintptr_t start_ppn, size_t page_count)
{
    MARK_CHUNK_AUX_VAR(start_ppn, page_count)

    pm_bitmap[group] &= ~(((1U << leading_shifts) - 1) << (8 - offset - leading_shifts));

    group++;

    for (uint32_t i = 0; group_count !=0 && i < group_count - 1; i++, group++) 
    {
        pm_bitmap[group] = 0;
    }

    pm_bitmap[group] &=    ~(((1U << (page_count > 8 ? remainder : 0)) - 1) << (8 - remainder));
}

void pmm_mark_chunk_occupied(uint32_t start_ppn, size_t page_count)
{
    MARK_CHUNK_AUX_VAR(start_ppn, page_count)

    pm_bitmap[group] |= (((1U << leading_shifts) - 1) << (8 - offset - leading_shifts));

    group++;

    for (uint32_t i = 0; group_count !=0 && i < group_count - 1; i++, group++) 
    {
        pm_bitmap[group] = 0xFFU;
    }

    pm_bitmap[group] |=  (((1U << (page_count > 8 ? remainder : 0)) - 1) << (8 - remainder));
}

#define LOOKUP_START 1

size_t pg_lookup_ptr;

void pmm_init(uintptr_t mem_upper_lim)
{
    max_pg = (PG_ALIGN(mem_upper_lim) >> 12);

    pg_lookup_ptr = LOOKUP_START;

    for (size_t i = 0; i < PM_BMP_MAX_SIZE; i++) 
    {
        pm_bitmap[i] = 0xFFU;
    }
}

void* pmm_alloc_page()
{
    uintptr_t good_page_found = NULL;
    size_t old_pg_ptr = pg_lookup_ptr;
    size_t upper_lim = max_pg;
    uint8_t chunk = 0;
    while (!good_page_found && pg_lookup_ptr < upper_lim) 
    {
        chunk = pm_bitmap[pg_lookup_ptr >> 3];

        if (chunk != 0xFFU) {
            for (size_t i = pg_lookup_ptr % 8; i < 8; i++, pg_lookup_ptr++) 
            {
                if (!(chunk & (0x80U >> i))) 
                {
                    pmm_mark_page_occupied(pg_lookup_ptr);
                    good_page_found = pg_lookup_ptr << 12;
                    break;
                }
            }
        } 
        else 
        {
            pg_lookup_ptr += 8;

            if (pg_lookup_ptr >= upper_lim && old_pg_ptr != LOOKUP_START) 
            {
                upper_lim = old_pg_ptr;
                pg_lookup_ptr = LOOKUP_START;
                old_pg_ptr = LOOKUP_START;
            }
        }
    }
    return (void*)good_page_found;
}

int pmm_free_page(void* page)
{
    uint32_t pg = (uintptr_t)page >> 12;
    if (pg && pg < max_pg)
    {
        pmm_mark_page_free(pg);
        return 1;
    }
    return 0;
}