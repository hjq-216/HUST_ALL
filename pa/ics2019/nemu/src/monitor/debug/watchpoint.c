#include "monitor/watchpoint.h"
#include "common.h"
#include "debug.h"
#include "monitor/expr.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NR_WP 32

static WP wp_pool[NR_WP] = {};
static WP *head = NULL, *free_ = NULL;

void init_wp_pool() {
  int i;
  for (i = 0; i < NR_WP; i ++) {
    wp_pool[i].NO = i;
    wp_pool[i].next = &wp_pool[i + 1];
  }
  wp_pool[NR_WP - 1].next = NULL;

  head = NULL;
  free_ = wp_pool;
}

/* TODO: Implement the functionality of watchpoint */

void info_w() {
  if (head == NULL) {
    printf("No watchpoints. Please use order 'w' to add watchpoint.\n");
    return;
  }
  printf("watchpoints: \n");
  printf("Num    Expr    Value\n");
  for(WP* node = head; node != NULL; node = node->next) {
    printf("%-4d%-16s%-8d\n", node->NO, node->expr, node->value);
  }
}

void new_wp(char* str) {
  if (free_ == NULL) {
    Assert(0, "No free watchpoint now. Please use order 'd' to free one watchpoint first.");
    return;
  }
  WP* wp = free_;
  bool success = true;
  uint32_t value = expr(str, &success);
  if (!success) {
    Log("expr error");
    return;
  }
  free_ = free_->next;
  // insert to head
  wp->next = head;
  head = wp;
  // share memory avoid escape.
  wp->expr = (char*)malloc(strlen(str) + 1);
  strcpy(wp->expr, str);
  wp->expr[strlen(str)] = '\0';
  wp->value = value;
}

void free_wp(int n) {
  if (n >= NR_WP) {
    Log("Please input a number less than NR_WP: %d", NR_WP);
    return;
  }
  if (head == NULL) {
    Log("No watchpoints. Please use order 'w' to add watchpoint.");
    return;
  }
  if (head->NO == n) {
    WP* p = head;
    head = head->next;
    p->expr = 0;
    p->value = 0;
    p->next = free_;
    free_ = p;
    return;
  }
  for(WP* node = head; node != NULL; node = node->next) {
    if (node->next && node->next->NO == n) {
      WP* p = node->next;
      node->next = p->next;
      p->expr = NULL;
      p->value = 0;
      // insert to head
      p->next = free_;
      free_ = p;
      return;
    }
  }
  printf("Number %d watchpoint is not used\n", n);
}

bool check_wp() {
  bool flag = false;
  for (WP* node = head; node != NULL; node = node->next) {
    bool success = true;
    uint32_t value = expr(node->expr, &success);
    if (value != node->value) {
      flag = true;
      printf("No.%d watchpoint's value changed: from %d to %d. It's expr is %s\n", node->NO, node->value, value, node->expr);
      node->value = value;
    }
  }
  return flag;
}

