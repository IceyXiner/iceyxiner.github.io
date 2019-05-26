#include<iostream>

#define MAXSIZE 20
#define ElemType int

enum Status {
    ERROR,
    OK
};

typedef struct {
    ElemType data;
    int cur;
} StaticLinkedList[MAXSIZE];

/**
 * 初始化静态链表
 * 例:
 * 下标   0    1   2   3   4   5   6   7   8   9
 * 游标   1    2   3   4   5   6   7   8   9   0
 * 数据   头   -   -   -   -   -   -   -   -   尾
 * 其中 头结点、尾结点、空结点数据为空
 * 头结点的游标指向第一个空结点的下标,尾结点的游标指向第一个非空结点的下标
 * @param space
 * @return Status
 */
Status InitList(StaticLinkedList space) {

    for (int i = 0; i < MAXSIZE - 1; i++){
        space[i].cur = i + 1;
        space[i].data = 0;
    }
    space[MAXSIZE - 1].cur = 0;
    return OK;
}

/**
 * 取得StaticLinkedList的长度
 * @param L
 * @return int Length
 */
int Length(StaticLinkedList L){
    int j = 0;
    //从尾结点获取第一个有元素的结点
    int i = L[MAXSIZE - 1].cur;
    //遍历计数
    while (i) {
        i = L[i].cur;
        j++;
    }
    return j;
}

/**
 * 若备用空间链表非空,则返回分配的结点下标,否则返回0
 * 例:
 * 下标   0    1   2   3   4   5   6   7   8   9
 * 游标   4    2   3   4   0   6   7   8   9   1
 * 数据   头   +   +   +   +   -   -   -   -   尾
 * @param space
 * @return 分配的链表下标
 */
int Malloc_SLL(StaticLinkedList space) {
    int i = space[0].cur; //当前数组第一个元素cur存的值,即链表总长的下个元素的下标
    if (space[0].cur)     //判断是否为链表尾
        space[0].cur = space[i].cur; //将这个空间分量分配出去,并取下个分量备用
    return i;
}

/**
 * 在L中第i个元素之前插入新的数据元素e
 * 例(插入前):
 * 下标   0    1   2   3   4   5   6   7   8   9
 * 游标   4    2   3   4   0   6   7   8   9   1
 * 数据   头   +   +   +   +   -   -   -   -   尾
 * 例(插入后, i=3):
 *                |---------->|(2->5)
 * 下标   0    1   2   3   4   5   6   7   8   9
 * 游标   4    2   5   4   0   6   7   8   9   1
 * 数据   头   +   +   +   +   *   -   -   -   尾
 *                    |<------|(5->3)
 * @param L
 * @param i 在下标为i的元素前,插入一个新的元素
 * @param e 新元素
 * @return Status
 */
Status Insert(StaticLinkedList L, int i, ElemType e) {
    //判断是否越界
    if (i < 1 || i > Length(L) + 1) {
        return ERROR;
    }
    int j = Malloc_SLL(L);
    //尾结点下标
    int k = MAXSIZE - 1;
    if (j) {
        //为新元素赋值
        L[j].data = e;
        //找到插入元素的前一个元素的游标
        for (int l = 1; l <= i - 1; l++)
            k = L[k].cur;
        /*
         * 简单的来说
         * ① | ② | ③
         * ① 是插入元素前的元素,下标为k,下一元素下标为L[k].cur
         * ② 是新插入元素,下标为j,下一元素下标为L[j].cur
         * ③ 是插入元素后的元素,即插入前在①的下一位,插入后在②的下一位,下标为L[k].cur
         */
        L[j].cur = L[k].cur; //将②的游标定为③
        L[k].cur = j; //将①的游标定为
        return OK;
    }
    return ERROR;
}
/**
 * 将下标为k的空闲结点回收到到备用链表
 * 也就是将删除数据后的空结点直接排在头结点后,并将之前的第一个空结点排在它之后
 * @param space
 * @param k 删除下标为k的元素
 */
void Free_SSL(StaticLinkedList space, int k) {
    space[k].cur = space[0].cur;
    space[0].cur = k;
}
/**
 * 删除下标为i的结点
 * 在L中第i个元素之前插入新的数据元素e
 * 例(删除前):
 *       |------------------------------->|(头结点指向第一个空结点)
 * 下标   0    1   2   3   4   5   6   7   8   9
 * 游标   8    2   7   4   0   6   0   3   9   1
 * 数据   头   +   +   +   +   +   +   *   -   尾
 * 例(删除后, i=1):
 *       |--->|(头结点先指向删除后的备用结点)
 *                |<--------------------------|(尾结点指向第一个非空的结点)
 * 下标   0    1   2   3   4   5   6   7   8   9
 * 游标   1    8   7   4   5   6   0   3   9   2
 * 数据   头   -   +   +   +   *   +   *   -   尾
 *            |-------------------------->|(头结点的后继元素再指向删除前的第一个空结点)
 * @param L
 * @param i 删除第i个结点
 * @return
 */
Status Delete(StaticLinkedList L, int i) {
    int j;
    //判断是否越界
    if (i < 1 || i > Length(L))
        return ERROR;
    //尾结点下标
    int k = MAXSIZE - 1;
    //k = 第i-1个元素的下标
    for (j = 1; j <= i - 1; j++)
        k = L[k].cur;
    //j = 第i个元素的下标
    //解除第i个元素前后索引
    j = L[k].cur;
    L[k].cur = L[j].cur;
    //回收空结点
    L[j].data = - 1;
    Free_SSL(L, j);
    return OK;
}