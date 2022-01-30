#include "common.h"
#include "debug.h"
#include "nemu.h"

/* We use the POSIX regex functions to process regular expressions.
 * Type 'man regex' for more information about POSIX regex functions.
 */
#include <stdint.h>
#include <stdio.h>
#include <sys/types.h>
#include <regex.h>

enum {
  TK_NOTYPE = 256, TK_EQ, TK_DEC, TK_HEX, TK_NEQ, TK_OR, TK_AND, TK_REG, TK_NOT, TK_DEREF 

  /* TODO: Add more token types */

};

static struct rule {
  char *regex;
  int token_type;
} rules[] = {

  /* TODO: Add more rules.
   * Pay attention to the precedence level of different rules.
   */

  {" +", TK_NOTYPE},    // spaces
  {"\\+", '+'},         // plus
  {"==", TK_EQ},        // equal
  {"!=", TK_NEQ},       // not equal
  {"-", '-'},          // minus
  {"\\*", '*'},          // multiply
  {"/", '/'},          // divide
  {"\\(", '('},          // LP
  {"\\)", ')'},          // RP
  {"^[1-9][0-9]*", TK_DEC},        // decimal
  {"^(0x|0X)[0-9,a-z,A-Z]+", TK_HEX},       // hex
  {"\\|\\|", TK_OR},    // or
  {"&&", TK_AND},        // and
  {"^(\\$0|ra|sp|gp|tp|t0|t1|t2|s0|s1|a0|a1|a2|a3|a4|a5|a6|a7|s2|s3|s4|s5|s6|s7|s8|s9|s10|s11|t3|t4|t5|t6)", TK_REG}
};

#define NR_REGEX (sizeof(rules) / sizeof(rules[0]) )

static regex_t re[NR_REGEX] = {};

/* Rules are used for many times.
 * Therefore we compile them only once before any usage.
 */
void init_regex() {
  int i;
  char error_msg[128];
  int ret;

  for (i = 0; i < NR_REGEX; i++) {
    ret = regcomp(&re[i], rules[i].regex, REG_EXTENDED);
    if (ret != 0) {
      regerror(ret, &re[i], error_msg, 128);
      panic("regex compilation failed: %s\n%s", error_msg, rules[i].regex);
    }
  }
}

typedef struct token {
  int type;
  char str[32];
} Token;

static Token tokens[65536] __attribute__((used)) = {};
static int nr_token __attribute__((used))  = 0;

// recgonize single token, and put them in tokens
static bool make_token(char *e) {
  int position = 0;
  int i;
  regmatch_t pmatch;

  nr_token = 0;

  while (e[position] != '\0') {
    /* Try all rules one by one. */
    for (i = 0; i < NR_REGEX; i++) {
      if (regexec(&re[i], e + position, 1, &pmatch, 0) == 0 && pmatch.rm_so == 0) {
        char *substr_start = e + position;
        int substr_len = pmatch.rm_eo;

        Log("match rules[%d] = \"%s\" at position %d with len %d: %.*s",
            i, rules[i].regex, position, substr_len, substr_len, substr_start);
        position += substr_len;

        /* TODO: Now a new token is recognized with rules[i]. Add codes
         * to record the token in the array `tokens'. For certain types
         * of tokens, some extra actions should be performed.
         */

        if (substr_len >= 32)
        {
          Log("expr over size\n");
          return false;
        }

        switch (rules[i].token_type) {
          default: 
            tokens[nr_token].type = rules[i].token_type;
            strncpy(tokens[nr_token].str, substr_start, substr_len);
            tokens[nr_token].str[substr_len] = '\0';
        }

        nr_token++;

        break;
      }
    }

    if (i == NR_REGEX) {
      printf("no match at position %d\n%s\n%*.s^\n", position, e, position, "");
      return false;
    }
  }

  return true;
}

/* return 0: error parentheses
* return 1: is surrounded by a matched pair of parentheses.
* return 2: is not surrounded by a matched pair of parentheses.
*/
uint32_t check_parentheses(int p, int q){
  int first = p;
  int top = 0;
  while (first <= q)
  {
    // ')' occur before '('
    if (top < 0) {
      return 0;
    }
    
    if (tokens[first].type == '(') {
      top++;
    }
    if (tokens[first].type == ')') {
      top--;
    }
    first++;
  }
  if (top != 0) {
    return 0;
  }
  
  if (tokens[p].type == '(' && tokens[q].type == ')') {
    int index_p = p+1;
    int index_q = q-1;
    // check if surrounded
    int top = 0;
    while (index_p <= index_q)
    {
      if (top < 0) {
        break;
      }
      if (tokens[index_p].type == '(') {
        top++;
      }
      if (tokens[index_p].type == ')') {
        top--;
      }
      index_p++;
    }
    if (top != 0) {
      Log("top : %d, is not surrounded by a matched pair of parentheses.", top);
      return 2;
    }
    return 1;
  }
  return 2;
}

// search the main op
uint32_t main_op(int p, int q){
  int match = 0;
  int op_stack[1024];
  int top = 0;
  for (int i = p; i <= q; i++)
  {
    if (match > 0 && tokens[i].type != '(' && tokens[i].type != ')') {
      continue;
    }
    if (match < 0) {
      break;
    }
    
    if (tokens[i].type == '(') {
      match++;
      continue;
    }
    if (tokens[i].type == ')') {
      match--;
      continue;
    }
    if (tokens[i].type != '+' && tokens[i].type != '-' &&
    tokens[i].type != '*' && tokens[i].type != '/' &&
    tokens[i].type != TK_EQ && tokens[i].type != TK_NEQ &&
    tokens[i].type != TK_AND && tokens[i].type != TK_OR && tokens[i].type != TK_NOT &&
    tokens[i].type != TK_DEREF) {
      continue;
    }
    op_stack[top++] = i;
  }
  if (match != 0) {
    Log("match: %d", match);
    Log("[main_op] error parentheses");
    return -1;
  }
  // for (int i = 0; i < top; i++)
  // {
  //   Log("%s\n", tokens[op_stack[i]].str);
  // }
  
  int index_op = -1;
  if (top > 0) {
    int priority = 5;
    /* low priority will exec later
    * 0: &&, ||
    * 1: ==, !=
    * 2: +, -
    * 3: *, /
    * 4: deref, not
    */
   for (int i = top-1; i >= 0; --i)
   {
     switch (tokens[op_stack[i]].type)
     {
     case TK_AND:
     case TK_OR: 
      if (priority > 0) {
        priority = 0;
        index_op = op_stack[i];
      }
      break;
    case TK_EQ: 
    case TK_NEQ:
      if (priority > 1) {
        priority = 1;
        index_op = op_stack[i];
      }
      break;
    case '+': 
    case '-': 
      if (priority > 2) {
        priority = 2;
        index_op = op_stack[i];
      }
      break;
    case '*': 
    case '/': 
      if (priority > 3) {
        priority = 3;
        index_op = op_stack[i];
      }
      break;
    case TK_DEREF: 
    case TK_NOT: 
      if (priority > 4) {
        priority = 4;
        index_op = op_stack[i];
      }
      break;
     
     default:
       break;
     }
     
   }
   
  }
  
  return index_op;
}

// evaluate expr
uint32_t eval(int p, int q){
  bool success = true;
  uint32_t value;
  if (p > q) {
    return 0;
  } else if (p == q) {
    /* single token */
    switch (tokens[p].type)
    {
    case TK_NOTYPE:
      return eval(p+1, q);
    case TK_DEC:
      return atoi(tokens[p].str);
    case TK_HEX:
      return strtol(tokens[p].str, NULL, 16);
    case TK_REG:
      value = isa_reg_str2val(tokens[p].str, &success);
      Assert(success, "reg name failed");
      return value;
    default:
      break;
    }
  } else if (tokens[p].type == TK_NOTYPE){
    return eval(p+1,q);
  } else if (tokens[q].type == TK_NOTYPE) {
    return eval(p, q-1);
  } else if (check_parentheses(p, q) == 0) {
    /* error parentheses */
    printf("[error]error parentheses, p: %d, q: %d\n", p, q);
    return 0;
  } else if (check_parentheses(p, q) == 1) {
    /* The expression is surrounded by a matched pair of parentheses.
     * If that is the case, just throw away the parentheses.
     */
    Log("is surrounded by parentheses");
    return eval(p+1, q-1);
  } else {
    int op = main_op(p, q);
    Log("main_op: %d p: %d, q: %d, str: %s", op, p, q, tokens[op].str);
    Assert(op >= p && op <= q, "main op error");
    int op_type = tokens[op].type;
    if (op_type == TK_NOT) {
      return -eval(op+1, q);
    }
    if (op_type == TK_DEREF) {
      return vaddr_read(eval(op+1,q), 4);
    }
    uint32_t val1 = eval(p, op-1);
    uint32_t val2 = eval(op+1, q);
    switch (op_type)
    {
    case '+':
      return val1 + val2;
    case '-': 
      return val1 - val2;
    case '*':
      return val1 * val2;
    case '/': 
      if (val2 == 0) {
        Log("divide 0");
        return INT32_MAX;
      }
      return val1 / val2;
    case TK_AND:
      return val1 && val2;
    case TK_OR:
      return val1 || val2;
    case TK_EQ: 
      return val1 == val2;
    case TK_NEQ:
      return val1 != val2;
    default:
      Assert(0, "unknown type");
    }
  }
}

uint32_t expr(char *e, bool *success) {
  if (!make_token(e)) {
    *success = false;
    return 0;
  }
  for (int i = 0; i < nr_token; i++)
  {
    int pre = i-1;
    while (pre >= 0 && tokens[pre].type == TK_NOTYPE) pre--;
    if (i == 0 || tokens[pre].type == '(' || tokens[pre].type == '+' || 
	    tokens[pre].type == '-' || tokens[pre].type == '*' ||
	    tokens[pre].type == '/' || tokens[pre].type == TK_EQ || tokens[pre].type == TK_NEQ || 
      tokens[pre].type == TK_AND || tokens[pre].type == TK_OR) {
      if (tokens[i].type == '-') {
	      tokens[i].type = TK_NOT;
      }
      if (tokens[i].type == '*') {
	      tokens[i].type = TK_DEREF;
      }
    }
  }
  
  return eval(0, nr_token-1);
}
