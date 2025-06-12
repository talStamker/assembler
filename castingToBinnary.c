#include <stdio.h>
#include <string.h>
#include <math.h>
#include "castingToBinnary.h"
#include <stdlib.h>
/*This class converts some variable types to their binary form or in base 32,
 to make coding easier*/

/*This function converts a number to its binary form in 4 bits.
variables:
int num-The number we want to convert.
char *ans-The number in its binary form inside a string*/
void numTo4Bits(int num, char *ans)
{
  int i = 3;
  ans[4] = '\0';
  for (; num > 0; i--)
  {
    ans[i] = num % 2 + 48;
    num = num / 2;
  }
  for (; i >= 0; i--)
  {
    ans[i] = '0';
  }
}

/*This function converts a number to its binary form in 8 bits.
This function works in the 2's complement method(Handles negative numbers).
variables:
char num-The number we want to convert inside string like "1".
char *ans-The number in its binary form inside a string.*/
void numTo8Bits(char *num, char *ans)
{
  int isnegative = 0, n = atoi(num), i = 7;
  ;
  if (n < 0)
  {
    n = -n;
    isnegative = 1;
  }
  ans[8] = '\0';
  for (; n > 0; i--)
  {
    ans[i] = n % 2 + 48;
    n = n / 2;
  }
  for (; i >= 0; i--)
  {
    ans[i] = '0';
  }
  if (isnegative)
  {
    for (i = 7; i >= 0 && ans[i] != '1'; i--)
    {
    }
    i--;
    for (; i >= 0; i--)
    {
      if (ans[i] == '0')
        ans[i] = '1';
      else
        ans[i] = '0';
    }
  }
}

/*This function converts a number to its binary form in 10 bits.
This function works in the 2's complement method(Handles negative numbers).
variables:
char num-The number we want to convert inside string like "1".
char *ans-The number in its binary form inside a string.*/
void numTo10Bits(char *num, char *ans)
{
  int isnegative = 0, n = atoi(num), i = 9;
  ;
  if (n < 0)
  {
    n = -n;
    isnegative = 1;
  }
  ans[10] = '\0';
  for (; n > 0; i--)
  {
    ans[i] = n % 2 + 48;
    n = n / 2;
  }
  for (; i >= 0; i--)
  {
    ans[i] = '0';
  }
  if (isnegative)
  {
    for (i = 9; i >= 0 && ans[i] != '1'; i--)
    {
    }
    i--;
    for (; i >= 0; i--)
    {
      if (ans[i] == '0')
        ans[i] = '1';
      else
        ans[i] = '0';
    }
  }
}

/*This function converts a register to its binary form in 4 bits.
variables:
char num-The number we want to convert inside string like "1".
char *ans-The number in its binary form inside a string.*/
void registerTo4Bits(char *r, char *ans)
{
  int n;
  if (strlen(r) == 0)
  {
    return;
  }
  r++;
  n = atoi(r);
  numTo4Bits(n, ans);
}

/*This function converts a number to its number in base 32.
The function does a conversion in the array value:
char base32Digits[100]={'!','@','#','$','%','^',
'&','*','<','>','a','b','c','d','e','f','g','h','i','j',
'k','l','m','n','o','p','q','r','s','t','u','v'};
variables:
int num-The number we want to convert.
char *ans-The number in bace 32 inside a string.*/
void castingNumto32Bit(int num, char *ans)
{
  char base32Digits[100] = {'!', '@', '#', '$', '%', '^', '&', '*', '<', '>', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v'};
  int i = 1, rest;
  ans[2] = '\0';
  for (; num > 0; num /= 32, i--)
  {
    rest = num % 32;
    ans[i] = base32Digits[rest];
  }
  for (; i >= 0; i--)
  {
    ans[i] = base32Digits[0];
  }
}

/*This function converts a number to its number in base 32.
The function does a conversion in the array value:
char base32Digits[100]={'!','@','#','$','%','^',
'&','*','<','>','a','b','c','d','e','f','g','h','i','j',
'k','l','m','n','o','p','q','r','s','t','u','v'};
variables:
cha num-The number we want to convert inside a string like "1".
char *ans-The number in bace 32 inside a string.*/
void castingWordTo32Bits(char *word10, char *ans)
{
  int decimalNumber = 0, i = 0;
  for (; i < strlen(word10); i++)
  {
    if (word10[9 - i] - '0')
    {
      decimalNumber += pow(2.0, (double)i);
    }
  }
  castingNumto32Bit(decimalNumber, ans);
}