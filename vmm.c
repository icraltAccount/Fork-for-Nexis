
#include <stdint.h>

struct vmm_struct {

 uint32_t  page_directory[1024];
 uint32_t page_table[1024];
uint32_t page_table_index[1024];

};

void map_page(struct vmm_struct) {

    for (int i = 0; i < page_directory; i++){
 page_directory[i] = 0;

 }
