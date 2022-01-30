#include "common.h"
#include <amdev.h>
#include <am.h>
#include <nemu.h>

size_t serial_write(const void *buf, size_t offset, size_t len) {
  _yield();
  for(int i = 0; i < len; i++) {
      _putc(*((char *)buf + i));
    }
  return len;
}

#define NAME(key) \
  [_KEY_##key] = #key,

static const char *keyname[256] __attribute__((used)) = {
  [_KEY_NONE] = "NONE",
  _KEYS(NAME)
};

/*
* 实现events_read()(在nanos-lite/src/device.c中定义), 把事件写入到buf中, 最长写入len字节, 
* 然后返回写入的实际长度. 其中按键名已经在字符串数组names中定义好了. 你需要借助IOE的API来获得设备的输入
*/
size_t events_read(void *buf, size_t offset, size_t len) {
  _yield();
  int k = read_key();
  if ((k & 0xfff) == _KEY_NONE) {
    int time = uptime();
    len = sprintf(buf,"t %d\n", time);
  } else {
    if (k & 0x8000) {
      len = sprintf(buf,"kd %s\n",keyname[k&0xfff]);
    } else {
      len = sprintf(buf,"ku %s\n",keyname[k&0xfff]);
    }
  }
  return len;
}

static char dispinfo[128] __attribute__((used)) = {};

// 用于把字符串dispinfo中offset开始的len字节写到buf中.
size_t dispinfo_read(void *buf, size_t offset, size_t len) {
   Log("%s", dispinfo + offset);
  len = sprintf(buf, "%s", dispinfo + offset);
  return len;
}

size_t fb_write(const void *buf, size_t offset, size_t len) {
  _yield();
  int x = (offset/4) % screen_width();
  int y = (offset/4) / screen_width();
  draw_sync();
  draw_rect((uint32_t*)buf, x, y, len/4, 1);
  return 0;
}

// 直接调用IOE的相应API即可
size_t fbsync_write(const void *buf, size_t offset, size_t len) {
  draw_sync();
  return 0;
}

// 将/proc/dispinfo的内容提前写入到字符串dispinfo中.
void init_device() {
  Log("Initializing devices...");
  _ioe_init();

  // TODO: print the string to array `dispinfo` with the format
  // described in the Navy-apps convention
  /*
  * WIDTH:640
  * HEIGHT:480
  */
  sprintf(dispinfo, "WIDTH:%d\nHEIGHT:%d\n", screen_width(), screen_height());
}
