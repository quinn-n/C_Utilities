/* simpleCalc.c
 * Made to do a quick math operation from the command line, where opening up clac is overkill.
 * Written by Quinn Neufeld
 * Feb. 09 2019
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tgmath.h>
#include <progutil.h>
#define HELP_MSG "Usage: simpleCalc <first num> <operator> <second num>\nPerforms a single operation on two numbers from the command line.\nMade to support operations with massive numbers.\n"

long double performOp(long double num1, char op, long double num2) {
  long double result = 0;
  switch(op) {
    case '*':
      result = num1 * num2;
      break;
    case '/':
      result = num1 / num2;
      break;
    case '+':
      result = num1 + num2;
      break;
    case '-':
      result = num1 - num2;
      break;
    case '%':
      result = remainder(num1, num2);
      break;
    case '^':
      result = powl(num1, num2);
      break;
    //sqrt
    case 's':
      result = sqrtl(num2);
    default:
      printf("I didn't recognise that operation.\n");
      break;
  }
  return result;
}

int main(int argc, char* argv[]) {
  if (!checkInputs(argc, argv, 4, HELP_MSG)) {
    return 0;
  }
  long double num1 = atof(argv[1]);
  char op = argv[2][0];
  long double num2 = atof(argv[3]);
  long double result = performOp(num1, op, num2);
  printf("%Le\n", result);
}
