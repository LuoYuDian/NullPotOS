// 创建于2024.12.14
// NullPotOS 虚拟内存

#include <kernel/mm/page.h>
#include <kernel/mm/vmm.h>
#include <kernel/mm/pmm.h>
#include <libs/libc/string.h>
#include <kernel/error/error.h>

ptd_t* get_pd() 
{
    ptd_t* pd;
    #ifdef __ARCH_IA32
    __asm__(
        "movl %%cr3, %0\n"
        "andl $0xfffff000, %0"
        : "=r"(pd)
    );
    #endif
    return P2V(pd);
}

void set_pd(ptd_t* pd) 
{
    #ifdef __ARCH_IA32
    __asm__(
        "movl %0, %%eax\n"
        "andl $0xfffff000, %%eax\n"
        "movl %%eax, %%cr3\n"
        :
        : "r" (pd)
    );
    #endif
}

void vmm_init() 
{

}

ptd_t* vmm_init_pd() 
{
    ptd_t* dir = pmm_alloc_page();
    for (size_t i = 0; i < 1024; i++)
    {
        dir[i] = 0;
    }
    dir[1023] = PDE(T_SELF_REF_PERM, dir);

    return dir;
}

void* vmm_map_page(void* va, void* pa, pt_attr dattr, pt_attr tattr) 
{
    // 不映射空指针
    if (!pa || !va) 
    {
        return NULL;
    }

    uintptr_t pd_offset = PD_INDEX(va);
    uintptr_t pt_offset = PT_INDEX(va);
    ptd_t* ptd = (ptd_t*)PTD_BASE_VADDR;

    ptd_t* pde = ptd[pd_offset];
    pt_t* pt = (uintptr_t)PT_VADDR(pd_offset);
    while (pde && pd_offset < 1024) 
    {
        if (pt_offset == 1024) 
        {
            pd_offset++;
            pt_offset = 0;
            pde = ptd[pd_offset];
            pt = (pt_t*)PT_VADDR(pd_offset);
        }
        
        if (pt && !pt[pt_offset]) 
        {
            pt[pt_offset] = PTE(tattr, pa);
            return V_ADDR(pd_offset, pt_offset, PG_OFFSET(va));
        }
        pt_offset++;
    }
    
    if (pd_offset > 1024) 
    {
        put_error(ERROR_OUT_OF_VMEMORY);
        return NULL;
    }

    uint8_t* new_pt_pa = pmm_alloc_page();
    
    if (!new_pt_pa) 
    {
        put_error(ERROR_OUT_OF_PMEMORY);
        return NULL;
    }
    
    ptd[pd_offset] = PDE(dattr, new_pt_pa);
    
    memset((void*)PT_VADDR(pd_offset), 0, PM_PAGE_SIZE);
    pt[pt_offset] = PTE(tattr, pa);

    return V_ADDR(pd_offset, pt_offset, PG_OFFSET(va));
}

void* vmm_alloc_page(void* vpn, pt_attr dattr, pt_attr tattr) 
{
    void* pp = pmm_alloc_page();
    void* result = vmm_map_page(vpn, pp, dattr, tattr);
    if (!result) 
    {
        pmm_free_page(pp);
    }
    return result;
}

void vmm_unmap_page(void* vpn) 
{
    uintptr_t pd_offset = PD_INDEX(vpn);
    uintptr_t pt_offset = PT_INDEX(vpn);
    ptd_t* self_pde = PTD_BASE_VADDR;

    ptd_t pde = self_pde[pd_offset];

    if (pde) 
    {
        pt_t* pt = (pt_t*)PT_VADDR(pd_offset);
        uint32_t pte = pt[pt_offset];
        if (IS_CACHED(pte) && pmm_free_page(pte)) 
        {
            #ifdef __ARCH_IA32
            __asm__("invlpg (%0)" :: "r"((uintptr_t)vpn) : "memory");
            #endif
        }
        pt[pt_offset] = 0;
    }
}

void* vmm_v2p(void* va) 
{
    uintptr_t pd_offset = PD_INDEX(va);
    uintptr_t pt_offset = PT_INDEX(va);
    uintptr_t po = PG_OFFSET(va);
    ptd_t* self_pde = PTD_BASE_VADDR;

    ptd_t pde = self_pde[pd_offset];
    if (pde) 
    {
        pt_t pte = ((pt_t*)PT_VADDR(pd_offset))[pt_offset];
        if (pte) 
        {
            uintptr_t ppn = pte >> 12;
            return (void*)P_ADDR(ppn, po);
        }
    }

    return NULL;
}