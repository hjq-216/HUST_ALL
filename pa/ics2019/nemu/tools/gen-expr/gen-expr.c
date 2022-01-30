#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>

// this should be enough
static char buf[1000];
static inline uint32_t choose(uint32_t n){
  return rand() % n;
}

// random insert 0-2 " "
void gen_rand_whitespace(){
  for (int i = 0; i <= choose(3); i++)
  {
    sprintf(buf + strlen(buf), " ");
  }
}

static inline void gen_rand_expr();

// put expr in buf
void gen(char* expr){
  // over 65535 after generate, reset the buf
  if (strlen(buf) + strlen(expr) + 3 > 500)
  {
    memset(buf, 0, sizeof(buf));
    gen_rand_expr();
    return;
  }
  sprintf(buf + strlen(buf), "%s", expr);
  gen_rand_whitespace();
}

void gen_num(){
  char num[15];
  sprintf(num, "%d", rand() % INT32_MAX);
  gen(num);
}

void gen_rand_op(){
  switch (choose(4))
  {
  case 0:
    gen("+");
    break;
  case 1:
    gen("-");
    break;
  case 2:
    gen("*");
    break;
  default: 
    gen("/");
    break;
  }
}

static inline void gen_rand_expr() {
  switch (choose(3)) {
    case 0: gen_num(); break;
    case 1: gen("("); gen_rand_expr(); gen(")"); break;
    default: gen_rand_expr(); gen_rand_op(); gen_rand_expr(); break;
  }
}

static char code_buf[75536];
static char *code_format =
"#include <stdio.h>\n"
"int main() { "
"  unsigned result = %s; "
"  printf(\"%%u\", result); "
"  return 0; "
"}";

int main(int argc, char *argv[]) {
  int seed = time(0);
  srand(seed);
  int loop = 1;
  if (argc > 1) {
    sscanf(argv[1], "%d", &loop);
  }
  int i;
  for (i = 0; i < loop; i ++) {
    memset(buf, 0, sizeof(buf));
    gen_rand_expr();

    sprintf(code_buf, code_format, buf);

    FILE *fp = fopen("/tmp/.code.c", "w");
    assert(fp != NULL);
    fputs(code_buf, fp);
    fclose(fp);

    int ret = system("gcc /tmp/.code.c -o /tmp/.expr");
    if (ret != 0) continue;

    fp = popen("/tmp/.expr", "r");
    assert(fp != NULL);

    int result = 0;
    fscanf(fp, "%d", &result);
    pclose(fp);

    printf("%u %s\n", result, buf);
    
  }
  return 0;
}
