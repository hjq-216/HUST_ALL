#include "common.h"
#include "syscall.h"
#include <stdint.h>

size_t do_brk(uint32_t addr) {
  programe_break = addr;
  return 0;
}

_Context* do_syscall(_Context *c) {
  uintptr_t a[4];
  a[0] = c->GPR1;
  a[1] = c->GPR2;
  a[2] = c->GPR3;
  a[3] = c->GPR4;

  switch (a[0]) {
    case SYS_exit:
      // _halt(0);
      naive_uload(NULL, "/bin/init");
      break;
    case SYS_yield:
      _yield();
      c->GPRx = 0;
      break;
    case SYS_write:
      /*
       * a[1] int fd
       * a[2] void * buf 
       * a[3] size_t count
       * cman write: 成功时返回所写入的字节数(若为零则表示没有写入数据).  错误时返回-1,并置errno为相应值.  
       * 若count为零,对于普通文件无任何影响,但对特殊文件 将产生不可预料的后果.
      */
      // test for brk
      // Log("hhh");
      c->GPRx = fs_write(a[1], (void *)a[2], a[3]);
      break;
    case SYS_brk:
      c->GPRx = do_brk(a[1]);
      break;
    case SYS_open:
      c->GPRx = fs_open((const char *)(a[1]), a[2], a[3]);
      break;
    case SYS_lseek:
      c->GPRx = fs_lseek(a[1], a[2], a[3]);
      break;
    case SYS_read:
      c->GPRx = fs_read(a[1], (void*)(a[2]), a[3]);
      break;
    case SYS_close:
      c->GPRx = fs_close(a[1]);
      break;
    case SYS_execve:
      printf("%s\n", a[1]);
      naive_uload(NULL, (const char*)a[1]);
      c->GPR2 = SYS_exit;
      do_syscall(c);
      break;
    default: panic("Unhandled syscall ID = %d", a[0]);
  }

  return NULL;
}
