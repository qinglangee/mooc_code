#ifndef zhch_simple_stack
#define zhch_simple_stack
#define DEFAULT_CAPACITY  3 //默认的初始容量(实际应用中可设置为更大)
template <typename T> class ZStack { //向量模板类
protected:
    int _size; int _capacity;T* _elem; //规模、容量、数据区
public:

    // 构造函数
    ZStack(int c = DEFAULT_CAPACITY, int s = 0, T v = 0) //容量为c、规模为s、所有元素刜始为v
    { _elem = new T[_capacity = c]; for (_size = 0; _size < s; _elem[_size++] = v); } //s <= c


    // 析构函数
    ~ZStack() { delete [] _elem; } //释放内部空间


    // 只读访问接口
    bool empty() const { return !_size; } //判空
    bool full() const { return _size == _capacity; } //判满
    int size() const { return _size; } // size
    T top(); // 栈顶元素


    // 可写访问接口
    int push(T const& e);  // 压入栈
    T pop(); // 弹出栈顶元素
    T& operator[](int r) const; //重载下标操作符,可以类似于数组形式引用各元素


    // 遍历
    void traverse(void (*)(T&));//遍历(使用函数指针,只读或局部性修改)
    template <typename VST> void traverse(VST&);//遍历(使用函数对象,可全局性修改)
}; // ZStack

template <typename T> T ZStack<T>::top(){ 
	return _elem[_size - 1];
} 

// 可写访问接口
template <typename T> int ZStack<T>::push(T const& e){ 
	if(_size == _capacity)
		return _size;
	_elem[_size++] = e;
	return _size;
} 

template <typename T> T ZStack<T>::pop(){ 
	return _elem[--_size];
} 

template <typename T> T& ZStack<T>::operator[](int r) const{ //重载下标操作符,可以类似于数组形式引用各元素
    return _elem[r];
}


// 遍历
template <typename T> void ZStack<T>::traverse(void (*visit)(T&)){//利用函数指针机制的遍历,只读或局部性修改
    for (int i = 0; i < _size; i++) visit(_elem[i]); 
}

template <typename T> template <typename VST> //元素类型、操作器
void ZStack<T>::traverse(VST& visit){ 
    for (int i = 0; i < _size; i++) visit(_elem[i]); //利用函数对象机制的遍历,可全局性修改
}





#endif /* zhch_simple_stack */