#pragma once
#include "stdafx.h"
#include "iostream"
#include "malloc.h"

typedef int Status;
typedef Status (*func_cmp)(void *a,void *b);
//typedef Status(*func_cmp)(double &a, double &b);
typedef Status (*pvisit)(int temp);

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1

template <typename T>
class ADTList {
public:
	virtual Status InitList() = 0;
	virtual Status DestroyList() = 0;
	virtual Status ClearList() = 0;
	virtual bool ListEmpty() = 0;
	virtual int ListLength() = 0;
	virtual T& GetElem(int index) = 0;
	virtual int LocateElem(T e, func_cmp *p) = 0;
	virtual T& PriorElem(T cur_e) = 0;
	virtual T& NextElem(T cur_e) = 0;
	virtual Status ListInsert(int index, T e) = 0;
	virtual Status ListDelete(int index, T &e) = 0;
	virtual Status ListTraverse(pvisit *p) = 0;
};


template <typename T>
class LinearList_Sq {
private:
	T * elem;
	int length;
	int listsize;
	int listincrement;
public:
	LinearList_Sq(int listsize=0, int listincrement=10) {
		this->elem = (T*)(malloc(listsize * sizeof(T)));
		if (this->elem == NULL) {
			exit(OVERFLOW);
		}
		this->listsize = listsize;
		this->length = 0;
		this->listincrement = listincrement;
	}
	~LinearList_Sq() {
		if (this->elem != NULL) free(this->elem);
		this->length = 0;
		this->listsize = 0;
		this->listincrement = 0;
	}
	Status InitList(int listsize=0, int listincrement = 10) {
		// 构造一个空的线性表L
		this->elem = (T*)(malloc(listsize * sizeof(T)));
		if (this->elem == NULL) {		  // 存储分配失败
			exit(OVERFLOW);
		}
		this->listsize = listsize;	// 初始化存储容量
		this->length = 0;			// 空表长度为0
		this->listincrement = listincrement;
		return OK;
	}
	Status DestroyList() {
		if (this->elem != NULL) free(this->elem);
		this->length = 0;
		this->listsize = 0;
		this->listincrement = 0;
		return OK;
	}
	Status ClearList() {
		memset(this->elem, NULL , this->length * sizeof(T));
		this->length = 0;
		return OK;
	}
	bool ListEmpty() {
		return (bool)(!(this->length));
	}
	int ListLength() {
		return this->length;
	}
	T& PriorElem(T cur_e) {
		T *p = this->elem;
		while (*(p + 1) != cur_e) ++p;
		return *p;
	}
	T& NextElem(T cur_e) {
		T *p = this->elem;
		while (*p != cur_e) ++p;
		return *(++p);
	}
	Status ListInsert(int i, T e) {
		// 在顺序线性表L中第i个位置之前插入新元素e
		// i的合法值为1 <= i <= (ListLength+1)
		if (i<1 || i>(this->length + 1)) return ERROR;		// i值不合法
		if (this->length >= this->listsize) {			// 当前存储空间已满， 增加分配
			T *newbase = (T*)realloc(this->elem, (this->listsize + this->listincrement) * sizeof(T));	  
			if (newbase == NULL) exit(OVERFLOW);			// 存储分配失败
			this->elem = newbase;						  // 新基址
			this->listsize += this->listincrement;		 // 增加存储容量
		}
		T *q = &(this->elem[i - 1]);					 // q为插入位置
		for (T *p = &(this->elem[this->length - 1]); p >= q; --p) *(p + 1) = *p;	 //插入位置及其之后的元素右移
		*q = e;
		++(this->length);
		return OK;
	}
	Status ListDelete(int i, T &e) {
		// 在顺序线性表L中删除第i个元素， 并用e返回其值
		// i的合法值为 1 <= i <= ListLength
		if ((i < 1) || (i > this->length)) return ERROR;   // i值不合法
		T *p = &(this->elem[i - 1]);				// p为被删除元素的位置
		e = *p;										// 被删除元素的值赋给e
		T *q = this->elem + this->length - 1;		// 表尾元素的位置
		for (++p; p <= q; ++p) *(p - 1) = *p;		// 被删除元素之后的元素左移
		--this->length;								// 表长减1
		return OK;
	}
	int LocateElem(T e, func_cmp compare) {
		// 在顺序线性表L中查找第一个值与e满足compare()的元素的位序
		// 若找到， 则返回其在L中的位序， 否则返回0
		int i = 1;		// i的初值的第一个元素的位序
		T *p = this->elem;	   // p的初值为第一个元素的存储位置
		while (i <= this->length && !(*compare)(p++, &e)) ++i;
		if (i <= this->length) return i;
		else return 0;
	}
	T& GetElem(int i) {
		return this->elem[i];
	}
	Status ListTraverse(pvisit visit) {
		T *p = this->elem;
		T *q = this->elem + this->length;
		while (p != q) {
			++p;
			visit(p);
		}
	}
	LinearList_Sq& MergeList(LinearList_Sq &Lb) {
		// 已知顺序线性表La和Lb的元素按值非递减排列
		// 归并La和Lb得到新的顺序线性表Lc， Lc的元素也按值非递减排列
		LinearList_Sq *Lc = new LinearList_Sq;
		T *pa = this->elem;
		T *pb = Lb.elem;
		Lc->listsize = Lc->length = this->length + Lb.length;
		T *pc = Lc->elem = (T*)malloc(Lc->length * sizeof(T));
		if (Lc->elem == NULL) exit(OVERFLOW); // 存储分配失败
		T *pa_last = this->elem + this->length - 1;
		T *pb_last = Lb.elem + Lb.length - 1;
		while (pa <= pa_last && pb <= pb_last) {		  //归并
			if (*pa <= *pb) *pc++ = *pa++;
			else *pc++ = *pb++;
		}
		while (pa <= pa_last) *pc++ = *pa++;	 // 插入剩余的元素
		while (pb <= pb_last) *pc++ = *pb++;
		return *Lc;
	}
};

template <typename T>
struct SLKNode {
	T data;
	int cur;
};

template <typename T>
class SLinkList {
private:
	SLinkList * space;
	int size;
public:
	SLinkList(int size) {
		this->size = size;
		// 将一维数组space中各分量链成一个备用表， space[0].cur为头指针
		// "0"表示空指针
		space = new SLKNode<T>[size];
		for (int i = 0; i < this->size - 1; ++i)	space[i].cur = i + 1;
		space[size - 1].cur = 0;
	}
	void InitSpace_SL(int size) {
		this->size = size;
		// 将一维数组space中各分量链成一个备用表， space[0].cur为头指针
		// "0"表示空指针
		space = new SLKNode<T>[size];
		for (int i = 0; i < this->size - 1; ++i)	space[i].cur = i + 1;
		space[size - 1].cur = 0;
	}
	int Malloc_SL() {
		// 若备用空间链表非空， 则返回分配的结点下标， 否则返回0
		int i = this->space[0].cur;
		if (this->space[0].cur) this->space[0].cur = this->space[i].cur;
		return i;
	}
	void Free_SL(int k) {
		// 将下标为k的空闲结点回收到备用链表
		this->space[k].cur = this->space[0].cur;
		this->space[0].cur = k;
	}
};

template <typename T>
struct LNode{
	T data;
	struct LNode *next;
};

template <typename T>
class LinkList {
private:
	LNode<T> *phead, *ptail;
	LNode<T> head;
	int len;
public:
	LinkList() {       
		phead = &head;
		ptail = phead;
		phead->next = nullptr;
	}
	~LinkList() {
		LNode<T> *p = phead->next;
		LNode<T> *q = p;
		while (q->next!=nullptr) {
			p = q->next;
			if (q != nullptr) {
				free(q);
				q = p;
			}
		}
		this->len = 0;
	}
	Status InitList() {	       // 构建一个空的线性链表L
		phead = &head;
		ptail = phead;
		phead->next = nullptr;
		return OK;
	}
	Status ClearList() {		// 将线性链表置为空表， 并释放原链表的结点空间
		LNode<T> *p = phead->next;
		LNode<T> *q = p;
		while (q->next != nullptr) {
			p = q->next;
			if (q != nullptr) {
				free(q);
				q = p;
			}
		}
		this->len = 0;
		return OK;
	}
	Status InsFirst(LNode<T> *s) {
		// 将s所指结点插入在第一个结点之前
		s->next = this->phead->next;
		this->phead->next = s;
		if (this->phead == this->ptail) this->ptail = s;
		return OK;
	}
	Status DelFirst(LNode<T> *s) {
		LNode *q = this->phead->next;
		*s = *q;
		this->phead->next = this->phead->next->next;
		delete q;
		q = nullptr;
		return OK;
	}
	Status Append(LNode<T> *s) {
		// 将指针s指向的一串结点链接在链表的最后一个结点之后， 并改变链表的尾指针指向新的结点
		LNode *p = s;
		while (p->next != nullptr) ++p;
		this->ptail->next = s;
		this->ptail = p;
	}
	Status ListTraverse(pvisit visit) {
		LNode<T> *p = this->phead;
		LNode<T> *q = this->ptail;
		while (p != q) {
			p = p->next;
			visit(p->data);
		}
		return OK;
	}
};
