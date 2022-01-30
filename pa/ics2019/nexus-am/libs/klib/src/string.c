#include "klib.h"
#include <assert.h>
#include <stddef.h>
#include <stdio.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

size_t strlen(const char *s) {
  size_t count = 0;
  while (*s != '\0') {
    s++;
    count++;
  }
  return count;
}

// 暂时不考虑内存覆盖
char *strcpy(char* dst,const char* src) {
  char *temp = dst;
  while((*temp++ = *src++) != '\0');
  return dst;
}

// simple implement of man
char* strncpy(char* dst, const char* src, size_t n) {
  size_t i;
  for(i = 0; i < n && src[i] != '\0'; i++) {
    dst[i] = src[i];
  }
  for(;i < n; i++) {
    dst[i] = '\0';
  }
  return dst;
}

char* strcat(char* dst, const char* src) {
  char *temp = dst;
  while (*temp != '\0') {
    temp++;
  }
  while((*temp++ = *src++) != '\0');
  return dst;
}

int strcmp(const char* s1, const char* s2) {
  /*
  * The strcmp() function compares the two strings s1 and s2.  
  * The locale is not taken into account (for a locale-aware comparison, see strcoll(3)).  
  * It returns an integer less than, equal to, or greater than zero 
  * if s1 is found, respectively, to be less than, to match, or be greater than s2.
  * 如果s1存在，大于返回正数，小于返回负数，等于返回0
  */
  while (*s1 && (*s1 == *s2)) {
    ++s1;
    ++s2;
  }

  return *s1 - *s2;
}

int strncmp(const char* s1, const char* s2, size_t n) {
  while (*s1 && (*s1 == *s2)) {
    n--;
    if (n == 0) {
      break;
    }
    ++s1;
    ++s2;
  }
  return *s1 - *s2;
}

void* memset(void* v,int c,size_t n) {
  // 因为memset根据字节进行赋值，因此只需要c的最低字节
  const char init_c = c;
  char *dst = v;
  while (n > 0) {
    *dst++ = init_c;
    n--;
  }
  return v;
}

void* memcpy(void* out, const void* in, size_t n) {
  const unsigned char *src = in;
  unsigned char * dst = out;
  while (n--) {
    *dst++ = *src++;
  }
  return out;
}

int memcmp(const void* s1, const void* s2, size_t n){
  /*
  RETURN VALUE
  The  memcmp()  function returns an integer less than, equal to, or greater than zero 
  if the first n bytes of s1 is found, respectively, to be less than, to match, or
  be greater than the first n bytes of s2.

  For a nonzero return value, 
  the sign is determined by the sign of the difference between the first pair of bytes 
  (interpreted as unsigned char) that differ in s1 and
  s2.
  If n is zero, the return value is zero.
  */
  if (n == 0) {
    return 0;
  }
  const char *a1 = s1;
  const char *a2 = s2;
  while (*a1 == *a2) {
    n--;
    if (n == 0) {
      break;
    }
    a1++;
    a2++;
  }
  return *a1 - *a2;
}

#endif
