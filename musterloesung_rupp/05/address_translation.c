#include <stdio.h>
#include <stdint.h>  // requires C99

#define PAGE_WIDTH 6       // number of bits to index pages
#define FRAME_WIDTH 4      // number of bits to index page frames
#define OFFSET_WIDTH 10    // number of bits within a page (frame)
#define OFFSET_MASK 0x3FF  // offset bits (lowest OFFSET_WIDTH bits) set
 
#define PA_BIT 0x80000000  // P/A bit, highest bit, 32-bit page table
#define PAGE_FAULT 0xFFFF  // special value indicates page fault

void binary_to_string(unsigned long int b, unsigned char k, char* s);
// Ihre 

uint_least16_t translate_address(
    uint_least16_t virtual, 
    uint_least32_t const* page_table
);

int main(void) {
    const uint_least32_t page_table[] = { 
        /* 0 */  PA_BIT | 4,
        /* 1 */  PA_BIT | 7,
        /* 2 */  PA_BIT | 3,
        /* 3 */  PA_BIT | 2,
        /* 4 */  ~PA_BIT,
        /* 5 */  PA_BIT | 0
    };
    
    const uint_least16_t pages[] = {5555, 4100, 2048, 2047};
    
    char sp[PAGE_WIDTH + OFFSET_WIDTH + 1];
    char sf[FRAME_WIDTH + OFFSET_WIDTH + 1];
    
    for (size_t i = 0; i < sizeof(pages)/sizeof(pages[0]); ++i) { 
        const uint_least16_t frame = translate_address(pages[i], page_table);
        binary_to_string(pages[i], PAGE_WIDTH + OFFSET_WIDTH, sp);
        binary_to_string(frame, FRAME_WIDTH + OFFSET_WIDTH, sf);
        printf("%u = %s -> %u = %s\n", pages[i] & (~PA_BIT), sp, frame, sf);
    }

    return 0;
}


void binary_to_string(unsigned long int b, unsigned char k, char *s) {
    for (unsigned char i = 0; i < k; ++i) {
        *(s + i) = ((b >> (k - 1 - i)) & 1) == 1 ? '1' : '0';
    }
    printf("%.*s\n", k, s);
}

uint_least16_t translate_address(uint_least16_t virtual, uint_least32_t const *page_table) {
    uint_least32_t page_table_entry = *(page_table + (virtual  >> OFFSET_WIDTH));

    if (page_table_entry >> 31 == 0) {
        return PAGE_FAULT;
    }

    return (((uint_least16_t) ((page_table_entry & ~PA_BIT) << OFFSET_WIDTH)) | (virtual & OFFSET_MASK));
}
