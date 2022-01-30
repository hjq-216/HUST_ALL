#include "fs.h"

typedef size_t (*ReadFn) (void *buf, size_t offset, size_t len);
typedef size_t (*WriteFn) (const void *buf, size_t offset, size_t len);

// device.c
extern size_t serial_write(const void*, size_t, size_t);
extern size_t events_read(void*, size_t, size_t);
extern size_t fb_write(const void *buf, size_t offset, size_t len);
extern size_t fbsync_write(const void *buf, size_t offset, size_t len);
extern size_t dispinfo_read(void *buf, size_t offset, size_t len);

typedef struct {
  char *name;
  size_t size;
  size_t disk_offset;
  size_t open_offset;  // 文件被打开之后的读写指针,每次对文件读写了多少个字节, 偏移量就前进多少
  ReadFn read;
  WriteFn write;
} Finfo;

enum {FD_STDIN, FD_STDOUT, FD_STDERR, FD_FB};

size_t invalid_read(void *buf, size_t offset, size_t len) {
  panic("should not reach here");
  return 0;
}

size_t invalid_write(const void *buf, size_t offset, size_t len) {
  panic("should not reach here");
  return 0;
}

/* This is the information about all files in disk. */
static Finfo file_table[] __attribute__((used)) = {
  {"stdin", 0, 0, 0, invalid_read, invalid_write},
  {"stdout", 0, 0, 0, invalid_read, serial_write},
  {"stderr", 0, 0, 0, invalid_read, serial_write},
  {"/dev/events", 0xffffff, 0, 0, events_read, invalid_write},
  {"/dev/fb", 0, 0, 0, invalid_read, fb_write},
  {"/dev/fbsync", 0xffff, 0, 0, invalid_read, fbsync_write},
  {"/proc/dispinfo", 128, 0, 0, dispinfo_read, invalid_write},
  {"/dev/tty", 0, 0, 0, invalid_read, serial_write},
#include "files.h"
};

#define NR_FILES (sizeof(file_table) / sizeof(file_table[0]))

// 对文件记录表中/dev/fb的大小进行初始化.
void init_fs() {
  // TODO: initialize the size of /dev/fb
  int fb = fs_open("/dev/fb", 0, 0);
  file_table[fb].size = screen_width() * screen_height() * 4;
}

/*
* 以下文件操作用于nanos.c中的系统调用的实现
*/

int fs_open(const char *pathname, int flags, int mode) {
  Log("%s", pathname);
  for(int i = 0; i < NR_FILES; ++i) {
    if (strcmp(pathname, file_table[i].name) == 0) {
      return i;
    }
  }
  Log("error pathname: %s\n", pathname);
  assert(0);
}

size_t fs_read(int fd, void *buf, size_t len) {
  // 如果读取超出文件末尾，则读到文件末尾
  if (fd >= 3 && file_table[fd].open_offset + len > file_table[fd].size) {
    if (file_table[fd].open_offset <= file_table[fd].size) {
      len = file_table[fd].size - file_table[fd].open_offset;
    } else {
      len = 0;
    }
  }
  // 如果不存在自定义的read，就使用ramdisk_read
  if (!file_table[fd].read) {
    ramdisk_read(buf, file_table[fd].disk_offset + file_table[fd].open_offset, len);
  } else {
    // Log("%s", file_table[fd].name);
    len = file_table[fd].read(buf, file_table[fd].disk_offset + file_table[fd].open_offset, len);
    // Log("%d", len);
  }
  file_table[fd].open_offset += len;
  return len;
}

size_t fs_write(int fd, const void *buf, size_t len) {
  if (fd >= 4 && (file_table[fd].open_offset + len > file_table[fd].size))
  {
    if (file_table[fd].size > file_table[fd].open_offset)
      len = file_table[fd].size - file_table[fd].open_offset;
    else
      len = 0;
  }
  if (!file_table[fd].write)
  {
    ramdisk_write(buf, file_table[fd].disk_offset + file_table[fd].open_offset, len);
  }
  else
  {
    file_table[fd].write(buf, file_table[fd].disk_offset + file_table[fd].open_offset, len);
  }
  file_table[fd].open_offset += len;
  return len;
}

size_t fs_lseek(int fd, size_t offset, int whence) {
  switch (whence)
  {
  case SEEK_SET:
    file_table[fd].open_offset = offset;
    break;
  case SEEK_CUR:
    file_table[fd].open_offset += offset;
    break;
  case SEEK_END:
    file_table[fd].open_offset = file_table[fd].size + offset;
    break;
  }
  return file_table[fd].open_offset;
}

int fs_close(int fd) {
  // 恢复
  file_table[fd].open_offset = 0;
  return 0;
}
