#include "monitor/expr.h"
#include "debug.h"

#include <stdio.h>
#include <stdlib.h>
int init_monitor(int, char *[]);
void ui_mainloop(int);

int main(int argc, char *argv[]) {
  /* Initialize the monitor. */
  int is_batch_mode = init_monitor(argc, argv);

  // test expr
  // int ret = system("tools/gen-expr/gen-expr 10 > tools/gen-expr/input");
  // if (ret != 0)
  // {
  //   printf("please make gen-expr tools first\n");
  // } else {
  //   FILE* in = fopen("tools/gen-expr/input", "r");
  //   Assert(in != NULL, "open gen-expr/input error");
  //   uint32_t result;
  //   FILE* out = fopen("tools/gen-expr/output", "w");
  //   int i = 0;
  //   while (i < 10)
  //   {
  //     fscanf(in, "%u", &result);
  //     char e[1000];
  //     fgets(e, 1000, in);
  //     e[strlen(e) - 1] = '\0';
  //     bool success = true;
  //     if (result != expr(e, &success))
  //     {
  //       fprintf(out, "%u %s", result, e);
  //     }
  //     i++;
  //   }
  //   fclose(in);
  //   fclose(out);
  // }
  

  /* Receive commands from user. */
  ui_mainloop(is_batch_mode);

  return 0;
}
