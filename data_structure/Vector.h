#include <stdlib.h>   
// stdlib.h for rand() func
typedef int Rank; //秩
#define DEFAULT_CAPACITY  3 //默认的初始容量(实际应用中可设置为更大)
template <typename T> class Vector { //向量模板类
protected:
    Rank _size; int _capacity;T* _elem; //规模、容量、数据区
    void copyFrom(T const* A, Rank lo, Rank hi); //复数组区间A[lo, hi)
    void expand(); //空间不足时扩容
    void shrink(); //装填因子过小时压缩
    bool bubble(Rank lo, Rank hi); //扫描交换
    void bubbleSort(Rank lo, Rank hi); //起泡排序算法
    Rank max(Rank lo, Rank hi); //选取最大元素
    void selectionSort(Rank lo, Rank hi); //选择排序算法
    void merge(Rank lo, Rank mi, Rank hi); //归并算法
    void mergeSort(Rank lo, Rank hi); //归并排序算法
    Rank partition(Rank lo, Rank hi); //轴点构造算法
    void quickSort(Rank lo, Rank hi); //快速排序算法
    void heapSort(Rank lo, Rank hi); //堆排序(稍后结合完全堆讲解)
public:

    // 构造函数
    Vector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0) //容量为c、规模为s、所有元素刜始为v
    { _elem = new T[_capacity = c]; for (_size = 0; _size < s; _elem[_size++] = v); } //s <= c
    Vector(T const* A, Rank lo, Rank hi) { copyFrom(A, lo, hi); }//数组区间复制
    Vector(T const* A, Rank n) { copyFrom(A, 0, n); }//数组整体复制
    Vector(Vector<T> const& V, Rank lo, Rank hi) { copyFrom(V._elem, lo, hi); }//向量区间复制
    Vector(Vector<T> const& V) { copyFrom(V._elem, 0, V._size); }//向量整体复制

    // 析构函数
    ~Vector() { delete [] _elem; } //释放内部空间
    // 只读访问接口
    Rank size() const { return _size; } //规模
    bool empty() const { return !_size; } //判空
    int disordered() const; //判断向量是否已排序
    Rank find(T const& e) const { return find(e, 0, _size); }//无序向量整体查找
    Rank find(T const& e, Rank lo, Rank hi) const;//无序向量区间查找
    Rank search(T const& e) const//有序向量整体查找
    { return (0 >= _size) ? -1 : search(e, 0, _size); }
    Rank search(T const& e, Rank lo, Rank hi) const;//有序向量区间查找

    // 可写访问接口
    T& operator[](Rank r) const; //重载下标操作符,可以类似于数组形式引用各元素
    Vector<T> & operator=(Vector<T> const&);//重载赋值操作符,以便直接克隆向量
    T remove(Rank r); //初除秩为r的元素
    int remove(Rank lo, Rank hi); //初除秩在区间[lo, hi)之内的元素
    Rank insert(Rank r, T const& e); //插入元素
    Rank insert(T const& e) { return insert(_size, e); }//默认作为末元素插入
    void sort(Rank lo, Rank hi); //对[lo, hi)排序
    void sort() { sort(0, _size); } //整体排序
    void unsort(Rank lo, Rank hi); //对[lo, hi)置乱
    void unsort() { unsort(0, _size); } //整体置乱
    int deduplicate(); //无序去重
    int uniquify(); //有序去重
    
    
    // 遍历
    void traverse(void (*)(T&));//遍历(使用函数指针,只读或局部性修改)
    template <typename VST> void traverse(VST&);//遍历(使用函数对象,可全局性修改)
}; //Vector

template <typename T> void Vector<T>::copyFrom(T const* A, Rank lo, Rank hi){
    if(hi <= lo){return;}
    _elem = new T[_capacity = 2*(hi - lo)]; 
    _size = 0;
    while(lo < hi){
        _elem[_size++] = A[lo++];
    }
}

template <typename T> void Vector<T>::expand(){ //空间不足时扩容
    if(_size < _capacity) return;   // 窗口;未满时不扩容
    _capacity = _capacity > 0 ? 2* _capacity : DEFAULT_CAPACITY;  //容量扩大
    T* temp = _elem;
    _elem = new T[_capacity];
    for(int i=0;i<_size;i++){  // 复制内容
        _elem[i] = temp[i];
    }
    delete [] temp;  // 释放旧空间
} 
template <typename T> void Vector<T>::shrink(){ //装填因子过小时压缩
    if (_capacity < DEFAULT_CAPACITY << 1) return; //不致收缩到DEFAULT_CAPACITY以下
    if (_size << 2 > _capacity) return; //以25%为界
    T* oldElem = _elem; _elem = new T[_capacity >>= 1]; //容量减半
    for (int i = 0; i < _size; i++) _elem[i] = oldElem[i]; //复制原向量内容
    delete [] oldElem; //释放原空间
} 
template <typename T> bool Vector<T>::bubble(Rank lo, Rank hi){} //扫描交换
template <typename T> void Vector<T>::bubbleSort(Rank lo, Rank hi){} //起泡排序算法
template <typename T> Rank Vector<T>::max(Rank lo, Rank hi){} //选取最大元素
template <typename T> void Vector<T>::selectionSort(Rank lo, Rank hi){} //选择排序算法
template <typename T> void Vector<T>::merge(Rank lo, Rank mi, Rank hi){} //归并算法
template <typename T> void Vector<T>::mergeSort(Rank lo, Rank hi){} //归并排序算法
template <typename T> Rank Vector<T>::partition(Rank lo, Rank hi){} //轴点构造算法
template <typename T> void Vector<T>::quickSort(Rank lo, Rank hi){} //快速排序算法
template <typename T> void Vector<T>::heapSort(Rank lo, Rank hi){} //堆排序(稍后结合完全堆讲解)


template <typename T> int Vector<T>::disordered() const{ //判断向量是否已排序
    if(_size < 1 ) return 0;
    for( Rank i=1;i<_size;i++){
        if( _elem[i] < _elem[i - 1]){
            return 1;
        }
    }
    return 0;
}

template <typename T> Rank Vector<T>::find(T const& e, Rank lo, Rank hi) const{//无序向量区间查找
    for(int i = lo; i < hi; i++){
        if(_elem[i] == e){
            return i;
        }
    }
    return -1;
}
template <typename T> Rank Vector<T>::search(T const& e, Rank lo, Rank hi) const{//有序向量区间查找
    for(int i = lo; i < hi; i++){
        if(_elem[i] == e){
            return i;
        }
    }
    return -1;
}

// 可写访问接口
template <typename T> T& Vector<T>::operator[](Rank r) const{ //重载下标操作符,可以类似于数组形式引用各元素
    return _elem[r];
}
template <typename T> Vector<T>& Vector<T>::operator=(Vector<T> const& V ) { //重载赋值操作符,以便直接克隆向量
    if (_elem) delete [] _elem; //释放原有内容
    copyFrom(V._elem, 0, V.size()); //整体复刢
    return *this; //迒回当前对象的引用,以便链式赋值
}
template <typename T> T Vector<T>::remove(Rank r){} //初除秩为r的元素
template <typename T> int Vector<T>::remove(Rank lo, Rank hi){} //初除秩在区间[lo, hi)之内的元素
template <typename T> Rank Vector<T>::insert(Rank r, T const& e){} //插入元素
template <typename T> void Vector<T>::sort(Rank lo, Rank hi){} //对[lo, hi)排序
template <typename T> void Vector<T>::unsort(Rank lo, Rank hi){ //对[lo, hi)置乱
    T* v = _elem + lo; //将子向量_elem[lo, hi)视作另一向量V[0, hi - lo)
    for (Rank i = hi - lo; i > 0; i--){ //自后向前
        //将V[i - 1]与V[0, i)中某一元素随机交换
        Rank tempRank = rand() % 1;
        T temp = v[i - 1];
        v[i - 1] = v[tempRank];
        v[tempRank] = temp;
    }
}
template <typename T> int Vector<T>::deduplicate(){} //无序去重
template <typename T> int Vector<T>::uniquify(){} //有序去重


// 遍历
template <typename T> void Vector<T>::traverse(void (*)(T&)){}//遍历(使用函数指针,只读或局部性修改)
template <typename T> template <typename VST> void Vector<T>::traverse(VST&){}//遍历(使用函数对象,可全局性修改)
