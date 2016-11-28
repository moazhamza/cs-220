#ifndef file_recognizer_h
#define file_recognizer_h

#include <stdio.h>

unsigned char *scan_for_sig(FILE * fp);
unsigned char on_list(unsigned char sig);
void check_gif(unsigned char* sigPtr);
void check_elf(unsigned char* sigPtr);
void check_pdf(unsigned char* sigPtr);
void check_zip(unsigned char* sigPtr);
void check_java(unsigned char* sigPtr);
void check_png(unsigned char* sigPtr);


#endif /* file_recognizer_h */
