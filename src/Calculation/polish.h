#ifndef POLISH_H
#define POLISH_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
  int operation;
  int priority;
  double number;
  struct Node *next;
} Node;

enum operations {
  PLUS,
  MIN,
  MULT,
  DIV,
  MOD,
  POW,
  LEFT_SCOBE,
  COS,
  SIN,
  TAN,
  ACOS,
  ASIN,
  ATAN,
  SQRT,
  LN,
  LOG,
  NUM,
  X,
  EMPTY
};

enum errors { OK, SYNTAX_ERROR, CALCULATION_ERROR };

void pop(Node *head);
void push(Node *head, double number, int priority, int operation);
void create_node(Node *head);
void infix_to_postfix(const char *input, Node *output, int *error, int graph);
double solve_postfix(Node *postfix, int *error);
void stack_to_output(Node *stack, Node *output, int *error);
void free_node(Node *node);
void scan_for_number(const char **input, char *string, int *error);
void push_number(const char **input, int *type, Node *node, char *number_str);
void push_operation(int operation, int *type, Node *output, Node *stack);
void push_function(int operation, int *type, Node *stack, const char **input);
void push_right_scobe(Node *output, Node *stack, int *error);
void swap_x(Node *output, double x);

Node *get_last(Node *head);

#endif  // POLISH_H
