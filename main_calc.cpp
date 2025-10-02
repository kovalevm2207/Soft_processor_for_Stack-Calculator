#include <stdio.h>
#include <cstring>
#include <math.h>
#include <assert.h>
#include "my_stack.h"

const size_t CAPACITY = 2;

typedef enum
{
    START_PROGRAM,
    HELP,
    PUSH,
    ADD,
    SUB,
    DIV,
    OUT,
    MUL,
    POW,
    SQRT,
    INVALID_COMMAND,
    RESET_STK,
    END_PROGRAM
} command_t;

command_t find_command(void);
void do_command(command_t command, stack_s* stk);
void do_help(void);
void do_push(stack_s* stk);
void do_add(stack_s* stk);
void do_sub(stack_s* stk);
void do_div(stack_s* stk);
void do_out(stack_s* stk);
void do_mul(stack_s* stk);
void do_pow(stack_s* stk);
void do_sqrt(stack_s* stk);

int main()
{
    stack_s stk = {};
    StackCtor(&stk, CAPACITY);

    // obrabotka vvoda:
    command_t command = START_PROGRAM;

    while (command != END_PROGRAM) {
        command = find_command();
        do_command(command, &stk);
    }

    StackDtor(&stk);
    return 0;
}


command_t find_command(void)
{
    char command[20] = {};
    scanf("%s", command);
    if (strcmp(command,  "HELP") == 0) return HELP;
    if (strcmp(command,  "PUSH") == 0) return PUSH;
    if (strcmp(command,   "ADD") == 0) return ADD;
    if (strcmp(command,   "SUB") == 0) return SUB;
    if (strcmp(command,   "DIV") == 0) return DIV;
    if (strcmp(command,   "OUT") == 0) return OUT;
    if (strcmp(command,   "MUL") == 0) return MUL;
    if (strcmp(command,   "POW") == 0) return POW;
    if (strcmp(command,  "SQRT") == 0) return SQRT;
    if (strcmp(command,   "HLT") == 0) return END_PROGRAM;
    if (strcmp(command, "RESET") == 0) return RESET_STK;
    else return INVALID_COMMAND;
}

void do_command(command_t command, stack_s* stk)
{
    assert(stk != NULL);

    if (command == END_PROGRAM) printf("You end the calc program\n");
    if (command == HELP)  do_help();
    if (command == PUSH)  do_push(stk);
    if (command == ADD)   do_add(stk);
    if (command == SUB)   do_sub(stk);
    if (command == DIV)   do_div(stk);
    if (command == OUT)   do_out(stk);
    if (command == MUL)   do_mul(stk);
    if (command == POW)   do_pow(stk);
    if (command == SQRT)  do_sqrt(stk);
    if (command == RESET_STK) {
        StackDtor(stk);
        StackCtor(stk, CAPACITY);
    }
    if (command == INVALID_COMMAND) {
        printf(CHANGE_ON RED TEXT_COLOR "INVALID_COMMAND, "
               CHANGE_ON RED TEXT_COLOR "please read help:\n" RESET);
        do_help();
    }
}

void do_help(void)
{
    printf("\nusage: main_calc " CHANGE_ON BLUE TEXT_COLOR "[HELP] [HLT] [PUSH] [OUT]\n"
           "                 [SUB] [DIV] [MUL] [POW] [SQRT]\n"
           RESET "\n"
	       "These are common main_calc commands used in various situations:\n"
           "You can use " CHANGE_ON PURPLE TEXT_COLOR "only integers" RESET " value\n"
	       "\n"
           CHANGE_ON GREEN TEXT_COLOR "HELP     " RESET "         cli flags help message\n"
	       CHANGE_ON GREEN TEXT_COLOR "HLT      " RESET "         HaLT (end the program)\n"
           CHANGE_ON GREEN TEXT_COLOR "PUSH  num" RESET "         save the value (num) to calculator memory\n"
           CHANGE_ON GREEN TEXT_COLOR "OUT      " RESET "         retrieve the last saved value from calculator memory\n"
           CHANGE_ON GREEN TEXT_COLOR "ADD      " RESET "         add the two last numbers stored in memory\n"
           CHANGE_ON GREEN TEXT_COLOR "SUB      " RESET "         subtract the last number in memory from the second last number in memory\n"
           CHANGE_ON GREEN TEXT_COLOR "DIV      " RESET "         divide the last number stored in memory by the second last number stored in memory\n"
           CHANGE_ON GREEN TEXT_COLOR "MUL      " RESET "         multiply the two last numbers stored in memory\n"
           CHANGE_ON GREEN TEXT_COLOR "POW   num" RESET "         raise the last number stored in memory to a power (num)\n"
           CHANGE_ON GREEN TEXT_COLOR "SQRT     " RESET "         calculate the square root of the last number in memory\n"
           "\n");
}

void do_push(stack_s* stk)
{
    assert(stk != NULL);

    stack_t data = 0;
    if (scanf("%d", &data) == 0) {
        printf(CHANGE_ON RED TEXT_COLOR "You can use only integers\n" RESET);
        do_help();
        return;
    }

    StackPush(stk, data);
}

void do_add(stack_s* stk)
{
    assert(stk != NULL);

    stack_t a = 0, b = 0;
    StackPop(stk, &a);
    StackPop(stk, &b);
    stack_t c = a + b;
    StackPush(stk, c);
}

void do_sub(stack_s* stk)
{
    assert(stk != NULL);

    stack_t a = 0, b = 0;
    StackPop(stk, &a);
    StackPop(stk, &b);
    stack_t c = b - a;
    StackPush(stk, c);
}

void do_div(stack_s* stk)
{
    assert(stk != NULL);

    stack_t a = 0, b = 0;
    StackPop(stk, &a);
    StackPop(stk, &b);
    stack_t c = b / a;
    StackPush(stk, c);
}

void do_out(stack_s* stk)
{
    assert(stk != NULL);

    stack_t data = 0;
    StackPop(stk, &data);
    printf("%d\n", data);
}

void do_mul(stack_s* stk)
{
    assert(stk != NULL);

    stack_t a = 0, b = 0;
    StackPop(stk, &a);
    StackPop(stk, &b);
    stack_t c = a * b;
    StackPush(stk, c);
}

void do_pow(stack_s* stk)
{
    assert(stk != NULL);

    stack_t a = 0, n = 0;

    if (scanf("%d", &n) == 0) {
        printf(CHANGE_ON RED TEXT_COLOR "Invalid exponent for the number\n" RESET);
        do_help();
        return;
    }

    StackPop(stk, &a);
    stack_t c = pow(a,n);
    StackPush(stk, c);
}

void do_sqrt(stack_s* stk)
{
    assert(stk != NULL);

    stack_t a = 0;
    StackPop(stk, &a);
    stack_t b = sqrt(a);
    StackPush(stk, b);
}
