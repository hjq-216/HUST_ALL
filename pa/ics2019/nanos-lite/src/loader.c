#include "proc.h"
#include <elf.h>
#include <stddef.h>
#include <stdint.h>
#include "fs.h"

#ifdef __ISA_AM_NATIVE__
# define Elf_Ehdr Elf64_Ehdr
# define Elf_Phdr Elf64_Phdr
#else
# define Elf_Ehdr Elf32_Ehdr
# define Elf_Phdr Elf32_Phdr
#endif

/*
* Ehdr:elf文件头表，包含的是一些elf文件信息，其中e_entry为程序入口地址
* Phdr:程序头表，这里应该将文件中的内容拷贝到内存中
* 内存地址已经根据makefile编译好，这里只用将elf文件中相关内容拷贝到虚拟地址即可
*/

static uintptr_t loader(PCB *pcb, const char *filename) {
  // pa3.2
  // Elf_Ehdr Ehdr;
  // ramdisk_read(&Ehdr, 0, sizeof(Ehdr));
  // // e_phnum表示有多少个程序头
  // for(int i = 0; i < Ehdr.e_phnum; i++) {
  //   Elf_Phdr Phdr;
  //   // 得到程序头表
  //   ramdisk_read(&Phdr, Ehdr.e_phoff + i*Ehdr.e_phentsize, sizeof(Phdr));
  //   // 将程序的内容拷贝到内存中
  //   ramdisk_read((void*)Phdr.p_vaddr, Phdr.p_offset, Phdr.p_filesz);
  // }
  // return Ehdr.e_entry;
  // pa3.3
  Elf_Ehdr Ehdr;
  int fd = fs_open(filename, 0, 0);
  fs_lseek(fd, 0, SEEK_SET);
  fs_read(fd, &Ehdr, sizeof(Ehdr));
  for(int i = 0; i < Ehdr.e_phnum;i++){
      Elf_Phdr Phdr;
      fs_lseek(fd, Ehdr.e_phoff + i*Ehdr.e_phentsize, SEEK_SET);
      fs_read(fd, &Phdr, sizeof(Phdr));
      if(!(Phdr.p_type & PT_LOAD)){
          continue;
      }
      fs_lseek(fd, Phdr.p_offset, SEEK_SET);
      fs_read(fd, (void*)Phdr.p_vaddr, Phdr.p_filesz);
      for(unsigned int i = Phdr.p_filesz; i < Phdr.p_memsz;i++){
          ((char*)Phdr.p_vaddr)[i] = 0;
      }
  }

  return Ehdr.e_entry;
}

void naive_uload(PCB *pcb, const char *filename) {
  uintptr_t* entry = loader(pcb, filename);
  Log("Jump to entry = %08x", entry);
  ((void(*)())entry) ();
}

void context_kload(PCB *pcb, void *entry) {
  _Area stack;
  stack.start = pcb->stack;
  stack.end = stack.start + sizeof(pcb->stack);

  pcb->cp = _kcontext(stack, entry, NULL);
}

void context_uload(PCB *pcb, const char *filename) {
  uintptr_t entry = loader(pcb, filename);

  _Area stack;
  stack.start = pcb->stack;
  stack.end = stack.start + sizeof(pcb->stack);

  pcb->cp = _ucontext(&pcb->as, stack, stack, (void *)entry, NULL);
}
