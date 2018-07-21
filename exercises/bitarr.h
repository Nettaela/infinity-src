#ifndef BARR_H
#define BARR_H
#include <stddef.h>

typedef size_t word_t;
typedef enum {FALSE = 0, TRUE = 1} bool;

bool BA_IsSet (word_t b_arr, int b_num);
bool BA_IsClear (word_t b_arr, int b_num);
size_t BA_SetCnt (word_t b_arr);
size_t BA_ClearCnt (word_t b_arr);
word_t BA_ModBit (word_t b_arr, int b_num, int val);
word_t BA_SetBit (word_t b_arr, int b_num);
word_t BA_ClearBit (word_t b_arr, int b_num);
word_t BA_SetAll (void);
word_t BA_ClearAll (void);
word_t BA_FlipBit (word_t b_arr, int b_num);
word_t BA_Mirror (word_t b_arr);
char *BA_ToStr (word_t b_arr, char* dest);
word_t BA_RotR (word_t b_arr, int n_bits);
word_t BA_RotL (word_t b_arr, int n_bits);

word_t BA_MirrorLUT (word_t b_arr);
size_t BA_SetCntLUT (word_t b_arr);

#endif /* BARR_H */

