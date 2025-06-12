#ifndef castingToBinnary_h
#define castingToBinnary_h
/*this header invented functions that convert numbers to base 2 or 32
The classes that use this header:
castingToBinnary.c
directiveSentence.c
teachingSentence.c
encodeLabels.c
secondRun.c
*/
void numTo4Bits(int num, char *ans);
void numTo8Bits(char *num, char *word);
void numTo10Bits(char *num, char *word);
void registerTo4Bits(char *r, char *reg);
void castingWordTo32Bits(char *word10, char *word32);
void castingNumto32Bit(int num, char *word32);
#endif