#ifndef zhch_list_node
#define zhch_list_node

typedef int Rank; //秩
#define ListNodePosi(T) ListNode<T>* //列表节点位置
template <typename T> struct ListNode { //列表节点模板类(以双向链表形式实现)
	// 成员
	T data; ListNodePosi(T) pred; ListNodePosi(T) succ; //数值、前驱、后继
	// 构造函数
	ListNode() {} //针对header和trailer的构造
	ListNode( T e, ListNodePosi(T) p = NULL, ListNodePosi(T) s = NULL)
	: data(e), pred(p), succ(s) {} //默讣构造器
	// 操作接口
	ListNodePosi(T) insertAsPred(T const& e); //紧靠弼前节点之前揑入新节点
	ListNodePosi(T) insertAsSucc(T const& e); //紧随弼前节点之后揑入新节点
};
#endif/*zhch_list_node*/