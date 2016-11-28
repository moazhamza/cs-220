#include <stdlib.h>
#include "file_recognizer.h"

/*
 * Scans the file for the first 8 bytes. Creates a list
 * of the first 8 bytes. Returns a pointer to the start of the list
 */
unsigned char *scan_for_sig(FILE * fp){
    unsigned char *sig = (unsigned char *) malloc(8*sizeof(int));
    fscanf(fp, "%c%c%c%c%c%c%c%c", sig, sig+1, sig+2, sig+3, sig+4, sig+5, sig+6, sig+7);
    return sig;
}
/*
 * Check to see which type of file this could possibly be. g = GIF, e = ELF, p = PDF, z = ZIP, 
 * j = JavaClassFile, n = PNG. Returns the corresponding character. Only to check first char in file
 */
unsigned char on_list(unsigned char sig){
    switch (sig) {
        case 0x47:
            return 'g';
        case 0x7f:
            return 'e';
        case 0x25:
            return 'p';
        case 0x50:
            return 'z';
        case 0xCA:
            return 'j';
        case 0x89:
            return 'n';
        default:
            return 0;
    }
}
/*
 * 47 49 46 38 39 61
 */
void check_gif(unsigned char* sigPtr){
    if(sigPtr[1] == 0x49 &&
       sigPtr[2] == 0x46 &&
       sigPtr[3] == 0x38 &&
       (sigPtr[4] == 0x39 || sigPtr[4] == 0x37) &&
       sigPtr[5] == 0x61) printf("This is a GIF file.\n");
    else printf("File type unknown.\n");
}
/* 7f 45 4C 46 */
void check_elf(unsigned char* sigPtr){
    if(sigPtr[1] == 0x45 &&
       sigPtr[2] == 0x4C &&
       sigPtr[3] == 0x46)
        printf("This is a ELF file.\n");
    else printf("File type unknown.\n");
}
/* 25 50 44 46  */
void check_pdf(unsigned char* sigPtr){
    if(sigPtr[1] == 0x50 &&
       sigPtr[2] == 0x44 &&
       sigPtr[3] == 0x46)
        printf("This is a PDF file.\n");
    else printf("File type unknown.\n");
}
/* 50 4B  */
void check_zip(unsigned char* sigPtr){
    if(sigPtr[1] == 0x4b) printf("This is a ZIP file.\n");
    else printf("File type unknown.\n");
}
/* CA FE BA BE */
void check_java(unsigned char* sigPtr){
    if(sigPtr[1] == 0xFE &&
       sigPtr[2] == 0xBA &&
       sigPtr[3] == 0xBE) printf("This is a Java class file.\n");
    else printf("File type unknown.\n");
}
/* 89 50 4E 47 0D 0A 1A 0A */
void check_png(unsigned char* sigPtr){
    if(sigPtr[1] == 0x50 &&
       sigPtr[2] == 0x4E &&
       sigPtr[3] == 0x47 &&
       sigPtr[4] == 0x0D &&
       sigPtr[5] == 0x0A &&
       sigPtr[6] == 0x1A &&
       sigPtr[7] == 0x0A) printf("This is a PNG file.\n");
    else printf("File type unknown.\n");

}

int main(int argc, const char* argv[]){
    if (argc < 2){
        printf("Invalid input...\n"); exit(1);
    }
    FILE *fp = fopen(argv[1], "r");
    if(fp){
        unsigned char *sigPtr = scan_for_sig(fp);
        
        unsigned char isOnList = on_list(*sigPtr);
        switch (isOnList) {
            case 'g':
                check_gif(sigPtr);
                break;
            case 'e':
                check_elf(sigPtr);
                break;
            case 'p':
                check_pdf(sigPtr);
                break;
            case 'z':
                check_zip(sigPtr);
                break;
            case 'j':
                check_java(sigPtr);
                break;
            case 'n':
                check_png(sigPtr);
                break;
            default:
                printf("File type unknown.\n");
        }
        
    }
    else{
        puts("File failed to open.\n");
    }
    fclose(fp);
}
