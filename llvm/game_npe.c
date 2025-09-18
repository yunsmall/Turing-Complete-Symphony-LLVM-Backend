// #include <stdint.h>
// #include <stdio.h>
// #include <stdbool.h>
// #include <stdlib.h>
// #include <memory.h>

typedef char bool;
#define true 1
#define false 0

typedef unsigned short uint16_t;

typedef uint16_t dtype;
uint16_t input(){}
void output(uint16_t val){}

// uint16_t input() {
//     char c;
//     scanf("%c", &c);
//     if (c == '\n') {
//         c = ' ';
//     }
//     return (uint16_t) c;
// }

// void output(uint16_t val) {
//     printf("%d\n", val);
// }


enum OP {
    ADD,
    SUB,
    OR,
    AND,
    XOR,
    LSL,
    LSR
};


struct data {
    bool is_value;

    union inner {
        dtype v;
        enum OP op;
    };
    union inner in;
};


extern struct data *stack;


bool is_op(dtype v) {
    switch (v) {
        case '+':
        case '-':
        case '|':
        case '&':
        case '^':
        case '<':
        case '>':
            return true;
        default:
            return false;
    }
}

dtype do_calc(enum OP op, dtype v1, dtype v2) {
    switch (op) {
        case ADD:
            return v1 + v2;
        case SUB:
            return v1 - v2;
        case OR:
            return v1 | v2;
        case AND:
            return v1 & v2;
        case XOR:
            return v1 ^ v2;
        case LSL:
            return v1 << v2;
        case LSR:
            return v1 >> v2;
        default:
            return 0;
    }
}

//void setup() {
//    stack = (struct data *) malloc(1024);
//
//
//}

int main() {
    dtype count = 0;
    bool last_is_space = true;
    //setup();

    while (true) {
        uint16_t in = input();
        // printf("%c\n", in);
        if (in != ' ') {
            if (last_is_space) {
                if ('0' <= in && in <= '9') {
                    //只处理了单个数
                    stack[count].is_value = true;
                    stack[count].in.v = in - '0';
                }
                else if (is_op(in)) {
                    enum OP tmp_op;
                    if (in == '+') {
                        tmp_op = ADD;
                    }
                    else if (in == '-') {
                        tmp_op = SUB;
                    }
                    else if (in == '|') {
                        tmp_op = OR;
                    }
                    else if (in == '&') {
                        tmp_op = ADD;
                    }
                    else if (in == '^') {
                        tmp_op = XOR;
                    }
                    else if (in == '<') {
                        tmp_op = LSL;
                        input();
                    }
                    else if (in == '>') {
                        tmp_op = LSR;
                        input();
                    }
                    stack[count].is_value = false;
                    stack[count].in.op = tmp_op;

                    if (count >= 2) {
                        if (stack[count - 2].is_value && stack[count - 2].is_value) {
                            dtype get_v = do_calc(stack[count].in.op, stack[count - 2].in.v, stack[count - 1].in.v);
                            output(get_v);
                            stack[count - 2].in.v = get_v;
                            count -= 2;
                        }
                    }
                }
                count++;
            }
            last_is_space = false;
        }
        else {
            last_is_space = true;
        }
    }


    return 0;
}
