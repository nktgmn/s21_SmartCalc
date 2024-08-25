#include "polish.h"

void push(Node *head, double number, int priority, int operation) {
  if (head->operation == EMPTY) {
    head->number = number;
    head->priority = priority;
    head->operation = operation;

  } else {
    Node *new = (Node *)malloc(sizeof(Node));
    new->next = NULL;
    new->number = number;
    new->priority = priority;
    new->operation = operation;

    Node *current = head;
    while (current->next != NULL) {
      current = current->next;
    }

    current->next = new;
  }
}

void pop(Node *head) {
  if (head->next == NULL) {
    head->operation = EMPTY;
  } else {
    Node *current = head;
    while (current->next->next != NULL) {
      current = current->next;
    }

    free(current->next);
    current->next = NULL;
  }
}

void create_node(Node *head) {
  head->next = NULL;
  head->number = 0;
  head->priority = 0;
  head->operation = EMPTY;
}

Node *get_last(Node *head) {
  Node *current = head;

  while (current->next != NULL) {
    current = current->next;
  }

  return current;
}

void infix_to_postfix(const char *input, Node *output, int *error, int graph) {
  Node *stack = (Node *)malloc(sizeof(Node));
  create_node(stack);
  int type = EMPTY;

  while (*input != '\0') {
    char *number_str = (char *)calloc(1, sizeof(char));
    scan_for_number(&input, number_str, error);

    if (strlen(number_str) > 0) {
      push_number(&input, &type, output, number_str);
    } else if (*input == '+') {
      push_operation(PLUS, &type, output, stack);
    } else if (*input == '-') {
      push_operation(MIN, &type, output, stack);
    } else if (*input == '*') {
      push_operation(MULT, &type, output, stack);
    } else if (*input == '/') {
      push_operation(DIV, &type, output, stack);
    } else if (*input == '^') {
      push_operation(POW, &type, output, stack);
    } else if (strstr(input, "mod") == input) {
      input = input + 2;
      push_operation(MOD, &type, output, stack);
    } else if (*input == '(') {
      push(stack, 0, -1, LEFT_SCOBE);
      type = LEFT_SCOBE;
    } else if (*input == ')') {
      push_right_scobe(output, stack, error);
    } else if (strstr(input, "sin(") == input) {
      push_function(SIN, &type, stack, &input);
    } else if (strstr(input, "sqrt(") == input) {
      push_function(SQRT, &type, stack, &input);
    } else if (strstr(input, "cos(") == input) {
      push_function(COS, &type, stack, &input);
    } else if (strstr(input, "tan(") == input) {
      push_function(TAN, &type, stack, &input);
    } else if (strstr(input, "acos(") == input) {
      push_function(ACOS, &type, stack, &input);
    } else if (strstr(input, "asin(") == input) {
      push_function(ASIN, &type, stack, &input);
    } else if (strstr(input, "atan(") == input) {
      push_function(ATAN, &type, stack, &input);
    } else if (strstr(input, "ln(") == input) {
      push_function(LN, &type, stack, &input);
    } else if (strstr(input, "log(") == input) {
      push_function(LOG, &type, stack, &input);
    } else if ((*input == 'x') && (graph == 1)) {
      push(output, 0, 0, X);
      type = X;
    } else if (*input != ' ') {
      *error = SYNTAX_ERROR;
    }

    free(number_str);
    input++;
  }

  stack_to_output(stack, output, error);
  free_node(stack);
}

double solve_postfix(Node *postfix, int *error) {
  int len = 0;

  Node *temp = (Node *)malloc(sizeof(Node));
  create_node(temp);

  while (postfix != NULL) {
    if (postfix->operation == NUM) {
      push(temp, postfix->number, postfix->priority, postfix->operation);
      len++;
    } else {
      Node *help = temp;

      int step = 2;
      if ((postfix->operation == SIN) || (postfix->operation == COS) ||
          (postfix->operation == TAN) || (postfix->operation == ACOS) ||
          (postfix->operation == ASIN) || (postfix->operation == ATAN) ||
          (postfix->operation == SQRT) || (postfix->operation == LN) ||
          (postfix->operation == LOG)) {
        step = 1;
      }

      for (int i = 0; i < len - step; i++) {
        help = help->next;
      }

      double result = 0;
      double left = help->number;

      if (step == 2) {
        if (help->next == NULL) {
          *error = SYNTAX_ERROR;
          break;
        }
        double right = help->next->number;

        if (postfix->operation == PLUS) {
          result = left + right;
        } else if (postfix->operation == MIN) {
          result = left - right;
        } else if (postfix->operation == MULT) {
          result = left * right;
        } else if (postfix->operation == DIV) {
          result = left / right;
        } else if (postfix->operation == POW) {
          result = pow(left, right);
        } else if (postfix->operation == MOD) {
          result = fmod(left, right);
        }
      } else {
        if (postfix->operation == SIN) {
          result = sin(left);
        } else if (postfix->operation == COS) {
          result = cos(left);
        } else if (postfix->operation == TAN) {
          result = tan(left);
        } else if (postfix->operation == ACOS) {
          result = acos(left);
        } else if (postfix->operation == ASIN) {
          result = asin(left);
        } else if (postfix->operation == ATAN) {
          result = atan(left);
        } else if (postfix->operation == SQRT) {
          result = sqrt(left);
        } else if (postfix->operation == LN) {
          result = log(left);
        } else if (postfix->operation == LOG) {
          result = log10(left);
        }
      }

      if (result != result) {
        *error = CALCULATION_ERROR;
      }

      help->number = result;

      if (step == 2) {
        free(help->next);
        help->next = NULL;
        len--;
      }
    }

    postfix = postfix->next;
  }

  double final_result = temp->number;

  if (temp->next != NULL) {
    *error = SYNTAX_ERROR;
  }

  free_node(temp);
  return final_result;
}

void stack_to_output(Node *stack, Node *output, int *error) {
  Node *temp = get_last(stack);
  while ((temp->operation != EMPTY) && (temp->operation != LEFT_SCOBE)) {
    push(output, temp->number, temp->priority, temp->operation);
    pop(stack);
    temp = get_last(stack);
  }

  if (temp->operation == LEFT_SCOBE) {
    *error = SYNTAX_ERROR;
  }
}

void free_node(Node *node) {
  Node *current = node;
  while (current != NULL) {
    Node *temp = current->next;
    free(current);
    current = temp;
  }
}

void scan_for_number(const char **input, char *string, int *error) {
  int number_len = 0;
  int number_of_dots = 0;

  while (((**input >= 48) && (**input <= 57)) || (**input == '.')) {
    string = (char *)realloc(string, number_len + 2);
    string = string + number_len;
    *string = **input;
    string = string - number_len;

    if (**input == '.') {
      number_of_dots++;
      if (number_of_dots >= 2) {
        *error = SYNTAX_ERROR;
      }
    }

    number_len++;
    (*input)++;
  }

  if ((*string == '0') && (*(string + 1) != '.') && (*(string + 1) != '\0')) {
    *error = SYNTAX_ERROR;
  }
}

void push_number(const char **input, int *type, Node *node, char *number_str) {
  double number;
  sscanf(number_str, "%lf", &number);
  push(node, number, 0, NUM);
  *type = NUM;
  (*input)--;
}

void push_operation(int operation, int *type, Node *output, Node *stack) {
  Node *last = get_last(stack);

  int priority = 1;
  if (operation == POW) {
    priority = 3;
  } else if ((operation == PLUS) || (operation == MIN)) {
    priority = 0;
  }

  if (((*type == EMPTY) || (*type == LEFT_SCOBE)) &&
      ((operation == PLUS) || (operation == MIN))) {
    push(output, 0, 0, NUM);
  }

  while ((last->priority >= priority) && (last->operation != EMPTY)) {
    push(output, last->number, last->priority, last->operation);
    pop(stack);
    last = get_last(stack);
  }

  push(stack, 0, priority, operation);
  *type = operation;
}

void push_function(int operation, int *type, Node *stack, const char **input) {
  int step = 2;
  if ((operation == SQRT) || (operation == ACOS) || (operation == ASIN) ||
      (operation == ATAN)) {
    step = 3;
  } else if (operation == LN) {
    step = 1;
  }
  *input = *input + step;
  push(stack, 0, 0, operation);
  *type = operation;
}

void push_right_scobe(Node *output, Node *stack, int *error) {
  Node *last = get_last(stack);
  while ((last->operation != LEFT_SCOBE) && (last->operation != EMPTY)) {
    push(output, last->number, last->priority, last->operation);
    pop(stack);
    last = get_last(stack);
  }

  last = get_last(stack);

  if (last->operation == EMPTY) {
    *error = SYNTAX_ERROR;
  }

  pop(stack);

  last = get_last(stack);

  if ((last->operation == SIN) || (last->operation == COS) ||
      (last->operation == TAN) || (last->operation == ACOS) ||
      (last->operation == ASIN) || (last->operation == ATAN) ||
      (last->operation == SQRT) || (last->operation == LN) ||
      (last->operation == LOG)) {
    push(output, last->number, last->priority, last->operation);
    pop(stack);
  }
}

void swap_x(Node *output, double x) {
  Node *current = output;
  while (current != NULL) {
    if (current->operation == X) {
      current->number = x;
      current->operation = NUM;
    }
    current = current->next;
  }
}
