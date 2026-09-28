#pragma once

#include <stdint.h>

// Using AI was necessary to teach me so I could do it on my own; I couldn't find any reliable sources—like OSDev or Intel documentation—that explain how to do it.
// I DO NOT VIBECODING!
// Say no to Vibecode!

struct vmm_structs{

    unsigned int table_page[1024];
    unsigned int page_directory[1024];


};

