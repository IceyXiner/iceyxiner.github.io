#include <iostream>
#include <time.h>

#define SElemtype char

enum Status {
    ERROR,
    OK
};

// 栈结点
typedef struct StackNode {
    SElemtype data;
    struct StackNode *next;
} StackNode, *LinkedStackPtr;
// 栈顶结构
typedef struct LinkedStack {
    // 栈顶指针
    LinkedStackPtr top;
    // 栈内元素个数
    int count = 0;
} LinkedStack;

/**
 * 初始化栈内元素
 * @param S 栈顶指针
 * @param n 初始化元素个数
 */
void InitLinkedStack(LinkedStack *S, int n) {
    // 定义栈顶指针
    LinkedStackPtr p;
    // 初始化随机种子
    srand(time_t(0));
    // LOOP
    for (int i = 0; i < n; ++i) {
        // 给栈结点分配内存空间
        p = (LinkedStackPtr) malloc(sizeof(StackNode));
        p->data = rand() % 100 + 1;
        // 压栈
        p->next = S->top;
        S->top = p;
    }
    S->count = n;
}

void ClearLinkedStack(LinkedStack *S) {
    LinkedStackPtr p;
    for (int i = 0; i < S->count; ++i) {
        p = S->top;
        S->top = S->top->next;
        free(p);
    }
    S->count = 0;
}

SElemtype GetLinkedStackTop(LinkedStack S) {
    return S.top->data;
}

/**
 * 压栈
 * @param S 栈顶指针
 * @param e 压入栈的元素
 * @return Status
 */
Status Push(LinkedStack *S, SElemtype e) {
    // 为栈节点分配内存空间
    LinkedStackPtr p = (LinkedStackPtr) malloc(sizeof(StackNode));
    p->data = e;
    // 压栈
    p->next = S->top;
    S->count++;
    S->top = p;
    return OK;
}

/**
 * 弹栈
 * @param S 栈顶指针
 * @param e 弹出元素
 * @return Status
 */
Status Pop(LinkedStack *S, SElemtype *e = nullptr) {
    LinkedStackPtr p;
    // 判断栈是否为空，空则不执行弹栈操作
    if (!S->count) {
        return ERROR;
    }
    // 判断弹出元素地址是否为空，空则不执行赋值操作
    if (e)
        *e = S->top->data;
    // 弹栈
    p = S->top;
    S->top = S->top->next;
    S->count--;
    // 释放空间
    free(p);
    return OK;
}

bool IsEmpty(LinkedStack S) {
    return !S.count;
}

int Length(LinkedStack S) {
    return S.count;
}

void PrintStack(LinkedStack S) {
    LinkedStackPtr ptr = S.top;
    while (ptr) {
        std::cout << ptr->data << " ";
        ptr = ptr->next;
    }
    std::cout << std::endl;
}

Status MidToTail() {
    //9+(3-1）*3+9/2
    //931-3*+92/+
    LinkedStack stack_tail_expression;
    LinkedStack stack_symbol;
    char s[20] = "3*(5+4)-4*3-2";
    for (int i = 0; i < 13; ++i) {
        std::cout<<s[i]<<" ";
        if (s[i] >= '0' && s[i] <= '9')
            Push(&stack_tail_expression, s[i]);
        else if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/' || s[i] == '(')
            Push(&stack_symbol, s[i]);
        else if (s[i] == ')') {
            while (GetLinkedStackTop(stack_symbol) != '('){
                SElemtype symbol;
                Pop(&stack_symbol, &symbol);
                Push(&stack_tail_expression, symbol);
            }
            Pop(&stack_symbol);
        }
    }
    char res[20];
    for (int j = 12; j >= 0; --j) {
        Pop(&stack_tail_expression, &res[j]);
        std::cout<<res[12-j]<<" ";
    }
    std::cout<<std::endl;
}
int main(){
    MidToTail();
    return 0;
}