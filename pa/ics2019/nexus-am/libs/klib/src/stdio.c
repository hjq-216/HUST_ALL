#include "klib.h"
#include <stdarg.h>
#include <stdbool.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

// 使用框架自带的输出
void _printf(const char *out, int n) {
  const char* fmt = out;
  while (n > 0 && *fmt != '\0') {
    _putc(*fmt++);
    n--;
  }
}

// 实现printf用来调试
int printf(const char *fmt, ...) {
  // 这里复用vsprintf
  char out[1024];
  va_list ap;
  // ap指向第一个参数
  va_start(ap, fmt);
  int n = vsprintf(out, fmt, ap);
  va_end(ap);


  _printf(out, n);

  return 0;
}

// 对齐补全
void completion(bool use_zero, int size, char **buf, int len, int* chars){
  if (len >= size) {
    return;
  }
  int num = size - len;
  if (use_zero) {
    while (num > 0) {
      **buf = '0';
      (*buf)++;
      (*chars)++;
      num--;
    }
  } else {
    while (num > 0) {
      **buf = ' ';
      (*buf)++;
      (*chars)++;
      num--;
    }
  }
}

// 将int型数字输出到out, 增加base方便后面增加其他进制
void number(char **out, int n, int base, int *chars, int size, bool use_zero) {
  // 负数增加‘-’
  bool negative = false;
  if (n < 0) {
    n = -n;
    negative = true;
  }
  
  // 先将number倒序输出到num，再放入out。
  char num[128];
  int len = 0;
  while (n != 0) {
    unsigned int b = n%base;
    switch (base) {
      case 10:
        num[len++] = b + '0';
        break;
      case 16:
        if (b < 10) {
          num[len++] = b + '0';
        } else {
          num[len++] = b - 10 + 'a';
        }
        break;
      default:
        printf("[number] base not implement\n");
    }
    n = n/base;
  }

  // 补全
  completion(use_zero, size, out, len, chars);

  // n = 0
  if (len == 0) {
    **out = '0';
    (*out)++;
    (*chars)++;
    return;
  }

  // 输出‘-’
  if (negative) {
    **out = '-';
    (*out)++;
    (*chars)++;
  }
  for(int i = len-1; i >= 0; --i) {
    **out = num[i];
    (*out)++;
    (*chars)++;
  }
}

// 输出指针
void print_p(char **out, unsigned long p, int *chars) {
  char num[128];
  int len = 0;
  while (p > 0) {
    int b = p%16;
    if (b < 10) {
      num[len++] = b + '0';
    } else {
      num[len++] = b - 10 + 'a';
    }
    p /= 16;
  }

  completion(true, 8, out, len, chars);

  for(int i = len-1; i >= 0; --i) {
    **out = num[i];
    (*out)++;
    (*chars)++;
  }
}

// 将fmt指向的字符串输出到out指向的buffer
int vsprintf(char *out, const char *fmt, va_list ap) {
  int num = 0;
  char *str;
  int n;
  // 用于输出指针
  unsigned long p;
  char *buf = out;
  int chars = 0;
  // %s中的字符串长度
  int len = 0;
  // 符号对齐的大小
  int size = 0;
  while (*fmt != '\0') {
    if (*fmt != '%') {
      *buf++ = *fmt++;
      chars++;
      continue;
    }
    // skip '%'
    fmt++;
    bool loop = true;
    bool use_zero = false;
    while (loop) {
      switch (*fmt) {
      case '0':
        use_zero = true;
        break;
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9':
        size = *fmt - '0';
        break;
      case 'c':
        completion(use_zero, size, &buf, 1, &chars);
        n = va_arg(ap, int);
        *buf++ = n;
        chars++;
        loop = false;
        break;
      case 's':
        str = va_arg(ap, char*);
        len = strlen(str);
        completion(use_zero, size, &buf, len, &chars);
        while (*str != '\0') {
          *buf++ = *str++;
          chars++;
        }
        loop = false;
        break;
      case 'd':
        n = va_arg(ap, int);
        number(&buf, n, 10, &chars, size, use_zero);
        loop = false;
        break;
      case 'x':
        // n = va_arg(ap, int);
        // number(&buf, n, 16, &chars, size, use_zero);
        // loop = false;
        // break;
      case 'p':
        p = va_arg(ap, unsigned long);
        *buf++ = '0';
        *buf++ = 'x';
        chars += 2;
        print_p(&buf, p, &chars);
        loop = false;
        break;
      default:
        printf("[vsprintf] not implement\n");
        return 0;
    }
    fmt++;
    }
  }
  *buf = '\0';
  return chars;
}

int sprintf(char *out, const char *fmt, ...) {
  va_list ap;
  // ap指向第一个参数
  va_start(ap, fmt);
  int n = vsprintf(out, fmt, ap);
  va_end(ap);

  return n;
}

int snprintf(char *out, size_t n, const char *fmt, ...) {
  return 0;
}

#endif
