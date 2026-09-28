#include "vmm.h"
#include "../include/pmm/pmm.h" // aqui ta foda viu infesei depois se puder arruma por favor se nao vai dar erro

// Using AI was necessary to teach me so I could do it on my own; I couldn't find any reliable sources—like OSDev or Intel documentation—that explain how to do it.
// I DO NOT VIBECODING!
// Say no to Vibecode!

// msg to nicoolo line 31-43.

void vmm_remap(struct vmm_structs *vmm){


for (int i = 0; i <  1024; i++ ){

    vmm->table_page[i] = 0;
}

for (int i = 0; i < 1024; i++){

    vmm->page_directory[i] = 0;

}

vmm->page_directory[0];

}

// daqui pra frente e seu nicoolo a sua parte, NAO FAZ TUDO, siga as dicas abaixo deixadas por mim:


/*
 * MSG: NICOOLO
 * alloque um frame fisico e faça o page_directory e table_page existirem dentro desse frame do endereço da memoria como ex: 0x00000
 * depois acessa esses frames a onde o kernel consiga escrever
 * se o pmmm te retornar ex: 0x001000 isso nao move os arrays da struct pra esse endereço real
 * entao nao alloque os frames ainda
 * de acordo com que aprendi com a ia e osdev eu percebi que podemos fazer vmm simples por enqanto baseado nisso:
 * page directory = 1 pagina fisica gerada pelo pmm de 1kb (1 kilobytes)
 * page_table = mesma coisa: uma pagina fisica de 4kib criada pelo pmm (1 kylobytes)
 * tenta nao pensar depois disso como array comuns de uma struct aqui.
 * agora e contigo meu amigo, nao tenho tanto tempo de sobra faça a sua parte de allocar etc eu ativo a paginação e tals.
 * se precisar eu faço o assembly eu to indo trabalhar agora.
 */
