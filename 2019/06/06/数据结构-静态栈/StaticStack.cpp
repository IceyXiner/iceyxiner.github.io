#include <iostream>

#define MAXSIZE 20
typedef int SElemType;

typedef struct {
    SElemType data[MAXSIZE];
    int top;  // 栈顶指针
} StaticStack;

enum Status {
    ERROR,
    OK
};

/**
 * 初始化栈内元素
 * @param S 栈顶指针
 */
void InitStack(StaticStack *S) {
    for (int i = 0; i < MAXSIZE - 1; ++i) {
        // 整体初始化
        S->data[i] = 0;
    }
    // 栈顶指针指向标志值-1
    S->top = -1;
}

void ClearStack(StaticStack S) {
    S.top = -1;
}

Status GetTop(StaticStack S, SElemType *e) {
    if (S.top == -1)
        return ERROR;
    *e = S.data[S.top];
    return OK;
}

/**
 * 压栈
 * @param S 栈顶指针
 * @param e 压入栈的元素
 * @return Status
 */
Status Push(StaticStack *S, SElemType e) {
    // 如果栈满,返回失败状态
    if (S->top == MAXSIZE - 1)
        return ERROR;
    // 压栈,指针上升一位
    S->top++;
    // 赋值
    S->data[S->top] = e;
    return OK;
}

/**
 * 弹栈
 * @param S 栈顶指针
 * @param e 弹出元素
 * @return Status
 */
Status Pop(StaticStack *S, SElemType *e) {
    // 判断是否为栈底,是则返回失败状态
    if (S->top == -1)
        return ERROR;
    // 取出弹出元素
    *e = S->data[|S->top];
    // 栈顶指针下降一位
    S->top--;
    return OK;
}

bool IsEmpty(StaticStack S) {
    return S.top == -1;
}

int Length(StaticStack S) {
    return S.top + 1;
}
/**
 * 输出栈中内容
 * @param S 栈顶指针
 */
void PrintStack(StaticStack S) {
    for (int i = S.top; i >= 0; --i) {
        std::cout << S.data[i] << " ";
    }
    std::cout << std::endl;
}




