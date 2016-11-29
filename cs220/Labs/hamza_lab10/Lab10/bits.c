#include <stdio.h>
#include <sys/time.h>
#include <math.h>

#define BIT(n) (1 << (n))
#define BIT_SET(v, mask) (v |= (mask))
#define BIT_CLEAR(v, mask) (v &= ~(mask))
#define BIT_FLIP(v, mask) (v ^= (mask))
#define IS_SET_ANY(v, mask) (v & (mask))
#define IS_CLEAR_ANY(v, mask) (v ^ (mask))

#define BIT_MASK(len)  (BIT(len) - 1)
#define BF_MASK(start, len)  ( BIT_MASK(len) << (start) )
#define BF_PREP(x, start, len) ( ((x)&BIT_MASK(len)) << (start) )

#define BF_GET(y, start, len)  ( ((y) >> (start)) & BIT_MASK((len)))
#define BF_SET(y, x, start, len) ( (BIT_CLEAR((y), BF_MASK((start), (len)))) | (BF_PREP((x), (start), (len))))

void print_in_binary(unsigned int x){
	int i;
	for(i=31; i>=0; i--){
		if(IS_SET_ANY(x, BIT(i))) printf("1");
		else printf("0");	
	}
	printf("\n");
}

void testMacros(){
	print_in_binary(100);
	unsigned int i, x, y;

	x  = BIT(4);
	printf("The fifth bit should be set and all other bits should be 0: \n");
	print_in_binary(x);

	puts("Before the 5th bit is set:");
	print_in_binary(6);
	puts("After the 5th bit is set:");
	y = BIT_SET(x, 6);
	print_in_binary(y);
	
	puts("Before 3rd bit is cleared");
	print_in_binary(y);
	BIT_CLEAR(y, BIT(2));
	puts("After 3rd bit is cleared");
	print_in_binary(y);

	puts("Before 19th bit is flipped");
	print_in_binary(y);
	puts("After 19th bit is flipped");
	BIT_FLIP(y, BIT(18));
	print_in_binary(y);

	puts("Is the first bit set?");
	print_in_binary(y);;
	int a = IS_SET_ANY(y, 1);
	if (a) printf("The bit is set.\n");
	else printf("The bit is not set\n");
	
	
	puts("Is the 3rd bit clear?");
	print_in_binary(y);
	a = IS_CLEAR_ANY(y, 3);
	if (a) puts("The bit is clear");
	else puts("The bit is not clear");


	int b = BIT_MASK(4);
	print_in_binary(b);
	
	b = BF_MASK(13, 4);
	print_in_binary(b);
	
	y = 0xffffffff;
	print_in_binary(y);
	y = BF_PREP(y, 13, 4);
	print_in_binary(y);

	puts("------------------------------------------------------");
		
	y = 0xD626;
	print_in_binary(y);
	int g = BF_GET(y, 2, 4);
	print_in_binary(g);
	
	puts("------------------------------------------------------");
	
	y = 0x009cea20;
	print_in_binary(y);
	x = 0xd;
	print_in_binary(x);
	unsigned int z = BF_SET(y,x,14,4);
	print_in_binary(z);
	
}
unsigned int get_page_offset(unsigned int address){
	return BF_GET(address, 0, 12);
}
unsigned int get_tlb_id(unsigned int address){
	return BF_GET(address, 12, 3);
}
unsigned int get_tlb_tag(unsigned int address){
	return BF_GET(address, 24, 8);
}
unsigned int set_page_offset(unsigned int address, unsigned int new_offset){    
	return  BF_SET(address, new_offset, 0, 12);
}	
unsigned int set_tlb_id(unsigned int address, unsigned int new_tlb_id){
	return BF_SET(address, new_tlb_id, 12, 3);
}
unsigned int set_tlb_tag(unsigned int address, unsigned int new_tag){
	return BF_SET(address, new_tag, 24, 8);
}
int main(){
	unsigned int address = 0xf712c0d0;
	puts("Original Address: ");
	print_in_binary(address);
	
	printf("Page offset: \n");
	print_in_binary(get_page_offset(address));
	
	printf("TLB ID: \n");
	print_in_binary(get_tlb_id(address));
	
	printf("TLB tag: \n");
	print_in_binary(get_tlb_tag(address));
	
	unsigned int page_offset = 0x1a3;
	printf("page offset: \n");
	print_in_binary(page_offset);
	unsigned int tlb_id = 0;
	printf("tlb id: \n");
	print_in_binary(tlb_id);
	unsigned int tlb_tag = 0x84;
	printf("tlb_tag: \n");
	print_in_binary(tlb_tag);
	
	printf("Page offset set: \n");
	print_in_binary(set_page_offset(address, page_offset));
	
	printf("TLB ID set: \n");
	print_in_binary(set_tlb_id(address, tlb_id));
	
	printf("TLB tag set: \n");
	print_in_binary(set_tlb_tag(address,tlb_tag));
}
















