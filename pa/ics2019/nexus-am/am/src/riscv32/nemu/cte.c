#include <am.h>
#include <riscv32.h>
#include <klib.h>

static _Context* (*user_handler)(_Event, _Context*) = NULL;

_Context* __am_irq_handle(_Context *c) {
  _Context *next = c;
  if (user_handler) {
    _Event ev = {0};
    switch (c->cause) {
      case -1:
        ev.event = _EVENT_YIELD;
        break;
      // exit
      case 0:
      // yield
      case 1:
      // open
      case 2:
      // read
      case 3:
      // write
      case 4:
      // close
      case 7:
      // lseek
      case 8:
      case 9:
      // exec
      case 13:
        ev.event = _EVENT_SYSCALL;
        break;
      default: printf("[__am_irq_handle] c->cause: %d not implement\n", c->cause);ev.event = _EVENT_ERROR; break;
    }

    next = user_handler(ev, c);
    if (next == NULL) {
      next = c;
    }
  }

  return next;
}

extern void __am_asm_trap(void);

int _cte_init(_Context*(*handler)(_Event, _Context*)) {
  // initialize exception entry
  asm volatile("csrw stvec, %0" : : "r"(__am_asm_trap));

  // register event handler
  user_handler = handler;

  return 0;
}

/*
* 在stack的底部创建一个以entry为返回地址的上下文结构(目前你可以先忽略arg参数), 然后返回这一结构的指针
*/
_Context *_kcontext(_Area stack, void (*entry)(void *), void *arg) {
  _Context *context = stack.end - sizeof(_Context);
  memset(context, 0, sizeof(_Context));
  context->epc = (uintptr_t)entry;
  return context;
}

void _yield() {
  asm volatile("li a7, -1; ecall");
}

int _intr_read() {
  return 0;
}

void _intr_write(int enable) {
}
