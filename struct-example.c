#include <stdint.h>
#include <stdio.h>

typedef uint16_t WORD;
typedef void* LPTR;
typedef LPTR *PLPTR;

// typedef struct _IMAGE_RELOC {
// 	WORD offset :12;
// 	WORD type :4;
// } IMAGE_RELOC, *PIMAGE_RELOC;

// .................................
//             ^
// |       |       |       |       |    
// 0       8      16      24      32

typedef struct _IMAGE_RELOC {
	int16_t offset  :12;
	int16_t type    :4;
	LPTR *array;
} IMAGE_RELOC, *PIMAGE_RELOC;

/*
====
SF:main (0x1000)

1: offset
2: type
3: LPTR
4
5
6
..
19: 


====
*/

void dump_image(PIMAGE_RELOC p_reloc) {
	fprintf(stderr, ".offset: %02x, .type: %04x\n",
		p_reloc->offset, p_reloc->type);
	fprintf(stderr, ".array:\n");
	for(LPTR *p = p_reloc->array; *p != NULL ; p++) {
		fprintf(stderr, " [%lu] = %p\n", p - p_reloc->array, *p);
	}
}

int main() {
	fprintf(stderr, "sizeof(WORD): %lu\n", sizeof(WORD));
	fprintf(stderr, "sizeof(IMAGE_RELOC): %lu\n", sizeof(IMAGE_RELOC));
	fprintf(stderr, "sizeof(PIMAGE_RELOC): %lu\n", sizeof(PIMAGE_RELOC));

	LPTR permanent_array[] =   { (LPTR) 0xdead, (LPTR) 0xbeef, NULL };

	IMAGE_RELOC foo = {
		.offset = 4,
		.type = 2,
		.array = permanent_array,
	};

	dump_image(&foo);

	return 0;
}
