#include <iostream>

#define ElemType int

typedef struct DulNode {
    ElemType data;
    struct DulNode *prior;
    struct DulNode *next;
} DulNode, *DuLinkedList;

enum Status {
    ERROR,
    OK
};

/**
 * 随即产生n个元素的值,建立带表头结点的双向链表L
 * 头插法
 * @param L 链表头结点地址
 * @param n 生成链表长度
 */
void CreateListHead(DuLinkedList *L, int n) {
    DuLinkedList newNode;
    srand(time(0));        // 初始化随机数种子
    // 初始化空链表L
    *L = (DuLinkedList) malloc(sizeof(DulNode));
    (*L)->prior = nullptr;
    (*L)->next = nullptr;
    // 循环生成链表结点
    for (int i = 0; i < n; i++) {
        // 为新链表结点分配一个地址
        newNode = (DuLinkedList) malloc(sizeof(DulNode));
        // 初始化新链表结点中的域,随机生成100以内的数字
        newNode->data = rand() % 100 + 1;
        // 将新链表结点插入到头结点与前一新结点之间
        newNode->next = (*L)->next;
        if (i >= 1)
            (*L)->next->prior = newNode; // 头结点不需要此步操作
        (*L)->next = newNode;
        newNode->prior = *L;
    }
}

/**
 * 随即产生n个元素的值,建立带表头结点的双向链表L
 * 尾插法
 * @param L 链表头结点地址
 * @param n 生成链表长度
 */
void CreateListTail(DuLinkedList *L, int n) {
    DuLinkedList newNode, tailNode;
    srand(time(0));        // 初始化随机数种子
    // 初始化空链表L
    *L = (DuLinkedList) malloc(sizeof(DulNode));
    (*L)->prior = nullptr;
    // 指向尾部的结点
    tailNode = *L;

    // 循环生成链表结点
    for (int i = 0; i < n; i++) {
        // 为新链表结点分配一个地址
        newNode = (DuLinkedList) malloc(sizeof(DulNode));
        // 初始化新链表结点中的域,随机生成100以内的数字
        newNode->data = rand() % 100 + 1;
        // 将链表尾部终端结点的指针指向新结点
        tailNode->next = newNode;
        // 将新结点的前置指针指向链表尾部终端结点
        newNode->prior = tailNode;
        // 将当前新结点定义为链表尾部终端结点
        tailNode = newNode;
    }
    // 当前链表尾部为NULL,链表结束
    tailNode->next = nullptr;
}

/**
 * 在L中的第i个位置前插入新数据元素e,L的长度加1
 * 时间复杂度O(1)
 * @param L 链表头结点地址
 * @param i 第i个位置
 * @param e 新数据元素
 * @return Status
 */
Status Insert(DuLinkedList *L, int n, ElemType e) {
    // 遍历计数器设置为1
    int i = 1;
    // 获取头结点
    DuLinkedList p = *L;
    // 遍历查找第i个元素
    while (p && i < n) {
        p = p->next;
        i++;
    }
    // 第i个元素不存在
    if (!p || i > n) {
        return ERROR;
    }
    // 创建新结点并为之分配内存
    DuLinkedList newNode = (DuLinkedList) malloc(sizeof(DulNode));
    // 为新结点初始化数据
    newNode->data = e;
    // 将新结点的后继结点设置为插入位置后的结点
    newNode->next = p->next;
    // 将插入位置后的结点的前驱结点定义为新结点
    p->next->prior = newNode;
    // 将插入位置前的结点的后继结点定义为新结点
    p->next = newNode;
    // 将新结点的前驱结点设置为插入位置前的结点
    newNode->prior = p;
    return OK;
}

/**
 * 删除L中的第i个数据元素,并用e返回其值,L的长度减1
 * 时间复杂度O(1)
 * @param L 链表头结点地址
 * @param i 第i个位置
 * @param e 被删除的数据元素
 * @return Status
 */
Status Delete(DuLinkedList *L, int n, ElemType *e) {
    // 遍历计数器设置为1
    int i = 1;
    // 获取头节点
    DuLinkedList p = *L, q;
    // 遍历查找第i个元素
    while (p && i < n) {
        p = p->next;
        i++;
    }
    // 第i个元素不存在
    if (!p || i > n) {
        return ERROR;
    }
    // 将q指针指向为第i个元素,此时p指针指向第i-1个元素,q指针指向第i个元素
    q = p->next;
    // 将p(第i-1个元素)的后继元素定义为q(第i个元素)的后继元素
    // 将q(第i个元素)的后继元素的前驱元素定义为p(第i-1个元素)
    // 即空开第i个元素,将第i-1个元素和第i个元素相连
    p->next = q->next;
    q->next->prior = p;
    // e返回删除元素的数据域
    *e = q->data;
    // free函数回收q所占用的内存
    free(q);
    return OK;
}

/**
 * 获取链表中的第i个元素
 * 最坏时间复杂度O(n)
 * @param L 链表头结点地址
 * @param i 第i个元素
 * @param e 第i个元素的数据域
 * @return
 */
Status GetElement(DuLinkedList L, int i, ElemType *e) {
    // 遍历计数器设置为1
    int j = 1;
    // 获取第一个元素节点
    DuLinkedList p = L->next;
    // 遍历链表
    while (p && j < i) {
        p = p->next;
        j++;
    }
    // 判断条件
    if (!p || j > i) {
        return ERROR;
    }
    *e = p->data;
    return OK;
}

/**
 * 将L重置为空表
 * @param L 链表头结点地址
 * @return Status
 */
Status Clear(DuLinkedList *L) {
    DuLinkedList p, q;
    // p指针指向第一个结点
    p = (*L)->next;
    // 循环直至表尾
    while (p) {
        // q指针记录p的下一个结点
        // 如果无此变量,释放p后,无法找到下个元素
        q = p->next;
        free(p);
        p = q;
    }
    // 头结点指针域为NULL
    (*L)->next = nullptr;
    return OK;
}

/**
 * 输出链表中内容
 * @param L 链表
 * @param n 从第n个元素开始
 * @param is_asc 是否顺序输出: true-顺序输出(默认),false-逆序输出
 */
void PrintList(DuLinkedList L, int n, bool is_asc = true) {
    int i = 1;
    DuLinkedList p = L->next;
    while (p && i < n) {
        p = p->next;
        i++;
    }
    if (is_asc) {
        // 循环至表尾
        while (p) {
            std::cout << p->data << " ";
            p = p->next;
        }
    } else {
        // 循环至表头
        while (p->prior) {
            std::cout << p->data << " ";
            p = p->prior;
        }
    }
    std::cout << std::endl;
}
