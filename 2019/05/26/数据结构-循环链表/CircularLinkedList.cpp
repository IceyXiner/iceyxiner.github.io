#include <iostream>
#define ElemType int

enum Status {
    ERROR,
    OK
};

typedef struct Node {
    int data;
    struct Node *next;
} Node, *CircularLinkedList;

/**
 * 随即产生n个元素的值,建立循环链表L
 * 头插法 -- 即倒序填装
 * @param L 单链表头结点地址
 * @param n 生成链表长度
 */
void CreateListHead(CircularLinkedList *L, int n) {
    CircularLinkedList newNode;
    srand(time_t(0));        // 初始化随机数种子
    // 初始化循环链表的第一个结点
    *L = (CircularLinkedList) malloc(sizeof(Node));
    (*L)->data = rand() % 100 + 1;
    (*L)->next = *L;
    // 循环生成链表结点
    for (int i = 1; i < n; i++) {
        // 为新链表结点分配一个地址
        newNode = (CircularLinkedList) malloc(sizeof(Node));
        // 初始化新链表结点中的域,随机生成100以内的数字
        newNode->data = rand() % 100 + 1;
        // 将新链表结点插入到头结点与前一新结点之间
        newNode->next = (*L)->next;
        (*L)->next = newNode;
    }
}

/**
 * 随即产生n个元素的值,建立循环链表L
 * 尾插法 -- 即顺序填装
 * @param L 单链表头结点地址
 * @param n 生成链表长度
 */
void CreateListTail(CircularLinkedList *L, int n) {
    CircularLinkedList tailNode, newNode;
    srand(time_t(0)); // 初始化随机数种子
    // 初始化循环链表的第一个结点
    *L = (CircularLinkedList) malloc(sizeof(Node));
    (*L)->data = rand() % 100 + 1;
    // 指向尾部的结点
    tailNode = *L;
    // 循环生成链表结点
    for (int i = 1; i < n; i++) {
        // 为新链表结点分配一个地址
        newNode = (CircularLinkedList) malloc(sizeof(Node));
        // 初始化新链表结点中的域,随机生成100以内的数字
        newNode->data = rand() % 100 + 1;
        // 将链表尾部终端结点的指针指向新结点
        tailNode->next = newNode;
        // 将当前新结点定义为链表尾部终端结点
        tailNode = newNode;
    }
    // 将链表尾部连接到头部
    tailNode->next = *L;
}

/**
 * 在L中的第i个位置前插入新数据元素e,L的长度加1
 * 时间复杂度O(1)
 * @param L 循环链表头结点地址
 * @param i 第i个位置
 * @param e 新数据元素
 * @return Status
 */
Status Insert(CircularLinkedList *L, int i, ElemType e) {
    CircularLinkedList p = *L, s;
    // 对于循环链表,因为头结点相对特殊,需要单独处理
    // 即在头结点前插入元素后,将表头结点地址更改为新插入结点地址
    if (i == 1) {
        // 将p指针指向链表最后一个元素
        for (; p->next != *L; p = p->next);
        // 创建新结点并为之分配内存
        s = (CircularLinkedList) malloc(sizeof(Node));
        // 为新结点初始化数据
        s->data = e;
        // 将新结点的后继结点设置为插入位置后的结点(即之前的头结点)
        s->next = p->next;
        // 前驱结点设置为插入位置前的结点(即尾结点)
        p->next = s;
        //将表头结点地址更改为新插入结点地址
        *L = s;
    } else {
        int j = 1;
        // 遍历查找第i个元素
        for (;p->next != *L && j < i - 1;p = p->next, ++j);
        // 第i个元素不存在
        if (p == *L && j > i)
            return ERROR;
        // 创建新结点并为之分配内存
        s = (CircularLinkedList) malloc(sizeof(Node));
        // 为新结点初始化数据
        s->data = e;
        // 将新结点的后继结点设置为插入位置后的结点
        s->next = p->next;
        // 前驱结点设置为插入位置前的结点
        p->next = s;
    }
    return OK;
}


/**
 * 删除L中的第i个数据元素,并用e返回其值,L的长度减1
 * 时间复杂度O(1)
 * @param L 单链表头结点地址
 * @param i 第i个位置
 * @param e 被删除的数据元素
 * @return Status
 */
Status Delete(CircularLinkedList *L, int i, ElemType *e) {
    CircularLinkedList p = *L, q;
    if (i == 1){
        // q指针指向第二个结点
        q = p->next;
        // 遍历到链表尾
        for (; p->next != *L; p = p->next);
        // 将p(尾结点)的后继元素定义为q(第1个元素)的后继元素
        // 即空开第1个元素,将第i个元素和第2个元素相连
        p->next = q;
        // 重新将p指针指向被孤立的元素(即马上被删掉的头结点)
        p = *L;
        // e返回删除元素的数据域
        *e = p->data;
        *L = q;
        // free函数回收q所占用的内存
        free(p);
    } else {
        // 遍历计数器设置为2(从第二个开始)
        int j = 2;
        // 获取头节点
        CircularLinkedList p = *L, q;
        // 遍历查找第i个元素
        for (;p->next != *L && j < i;p = p->next, ++j);
        // 第i个元素不存在
        if (i >= j)
            return ERROR;
        // 将q指针指向为第i个元素,此时p指针指向第i-1个元素,q指针指向第i个元素
        q = p->next;
        // 将p(第i-1个元素)的后继元素定义为q(第i个元素)的后继元素
        // 即空开第i个元素,将第i-1个元素和第i个元素相连
        p->next = q->next;
        // e返回删除元素的数据域
        *e = q->data;
        // free函数回收q所占用的内存
        free(q);
    }
    return OK;
}

void PrintList(CircularLinkedList L) {
    CircularLinkedList target = L;
    do {
        std::cout << target->data << " ";
        target = target->next;
    } while ((target != L));
    std::cout << std::endl;
}

