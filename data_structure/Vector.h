#ifndef zhch_vector
#define zhch_vector
#include <stdlib.h>   
// stdlib.h for rand() func


// #include <iostream>
// using namespace std;



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
    void swap(T const& a, T const& b){T& t = a; a = b; b = t;} // 交换两个元素位置
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
    Rank insertBinSearch(T const& e) const//有序向量区间查找
    { return (0 >= _size) ? -1 : insertBinSearch(_elem, e, 0, _size); }
    Rank insertBinSearch(T const& e, Rank lo, Rank hi) const;//有序向量区间查找
    Rank search(T const& e, Rank lo, Rank hi) const;//有序向量区间查找
    Rank binSearch(T* A, T const& e, Rank lo, Rank hi) const;//有序向量区间查找
    Rank insertBinSearch(T* A, T const& e, Rank lo, Rank hi) const;//有序向量区间查找

    // 可写访问接口
    T& operator[](Rank r) const; //重载下标操作符,可以类似于数组形式引用各元素
    Vector<T> & operator=(Vector<T> const&);//重载赋值操作符,以便直接克隆向量
    T remove(Rank r); //删除秩为r的元素
    int remove(Rank lo, Rank hi); //删除秩在区间[lo, hi)之内的元素
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
template <typename T> bool Vector<T>::bubble(Rank lo, Rank hi){ //扫描交换
    bool sorted = true;
    lo++;
    while(lo < hi){
        if(_elem[lo] < _elem[lo - 1]){
            sorted = false;
            swap(_elem[lo], _elem[lo - 1]);
        }
        lo++;
    }
    return sorted;
}
template <typename T> void Vector<T>::bubbleSort(Rank lo, Rank hi){ //起泡排序算法
    while(!bubble(lo, hi--));
}
template <typename T> Rank Vector<T>::max(Rank lo, Rank hi){ //选取最大元素
    Rank result = lo;
    for(Rank i = lo; i < hi - 1; i++){
        if(_elem[lo] < _elem[lo + 1]){
            result = lo + 1;
        }
    }
    return result;
}
template <typename T> void Vector<T>::selectionSort(Rank lo, Rank hi){} //选择排序算法
template <typename T> //有序向量的归并
void Vector<T>::merge(Rank lo, Rank mi, Rank hi) { //以mi为界、各自有序的子向量[lo, mi)和[mi, hi)
    T* A = _elem + lo; //合并后的向量A[0, hi - lo) = _elem[lo, hi)
    int lb = mi - lo; T* B = new T[lb]; //前子向量B[0, lb) = _elem[lo, mi)
    for (Rank i = 0; i < lb; B[i] = A[i++]); //复制前子向量
    int lc = hi - mi; T* C = _elem + mi; //后子向量C[0, lc) = _elem[mi, hi)
    for (Rank i = 0, j = 0, k = 0; (j < lb) || (k < lc); ) { //将B[j]和C[k]中的小者续至A末尾
        if ( (j < lb) && ( !(k < lc) || (B[j] <= C[k]) ) ) A[i++] = B[j++];
        if ( (k < lc) && ( !(j < lb) || (C[k] <B[j]) ) ) A[i++] = C[k++];
    }
    delete [] B; //释放临时空间B
    
} //归并后得到完整的有序向量[lo, hi)
template <typename T> void Vector<T>::mergeSort(Rank lo, Rank hi){ //归并排序算法
    if (hi - lo < 2) return; //单元素区间自然有序,否则...
    int mi = (lo + hi) >> 1; //以中点为界
    mergeSort(lo, mi); mergeSort(mi, hi); merge(lo, mi, hi); //分删对前、后半段排序,然后归并
}
template <typename T> Rank Vector<T>::partition(Rank lo, Rank hi){} //轴点构造算法
template <typename T> void Vector<T>::quickSort(Rank lo, Rank hi){ //快速排序算法

}
template <typename T> void Vector<T>::heapSort(Rank lo, Rank hi){} //堆排序(稍后结合完全堆讲解)

template <typename T> int Vector<T>::disordered() const{ //判断向量是否已排序, 返回逆序对的个数
    int n = 0;
    for( Rank i=1;i<_size;i++){
        if( _elem[i] < _elem[i - 1]){
            n++;
        }
    }
    return n;
}

template <typename T> Rank Vector<T>::find(T const& e, Rank lo, Rank hi) const{//无序向量区间查找
    for(int i = hi - 1; i >= lo; i--){
        if(_elem[i] == e){
            return i;
        }
    }
    return -1;
}
template <typename T> Rank Vector<T>::search(T const& e, Rank lo, Rank hi) const{ //在有序向量的区间[lo, hi)内,确定不大于e的最后一个节点的秩
    //assert: 0 <= lo < hi <= _size
    // return (rand() % 2) ? //按各50%的概率随机使用
    //     binSearch(_elem, e, lo, hi) : fibSearch(_elem, e, lo, hi); //二分查找或Fibonacci查找
    return binSearch(_elem, e, lo, hi);
}

// 二分查找算法(版本A):在有序向量的区间[lo, hi)内查找元素e,0 <= lo <= hi <= _size
template <typename T> Rank  Vector<T>::binSearch(T* A, T const& e, Rank lo, Rank hi) const{
    while (lo < hi) { //每步迭代可能要做两次比较判断,有三个分支
        Rank mi = (lo + hi) >> 1; //以中点为轴点
        if(e < A[mi]) hi = mi; //深入前半段[lo, mi)继续查找
        else if (A[mi] < e) lo = mi + 1; //深入后半段(mi, hi)继续查找
        else
            return mi; //在mi处命中
    } //成功查找可以提前终止
    return -1; //查找失败
} //有多个命中元素时,不能保证返回秩最大者;查找失败时,简单地返回-1,而不能指示失败的位置


template <typename T> Rank Vector<T>::insertBinSearch(T const& e, Rank lo, Rank hi) const//有序向量区间查找
{
    lo = lo < 0 ? 0 : lo;
    hi = hi > _size ? _size : hi; 
    return (0 >= _size) ? -1 : insertBinSearch(_elem, e, lo, hi); 
}
// 二分查找算法(版本C):在有序向量的区间[lo, hi)内查找元素e,0 <= lo <= hi <= _size
template <typename T> Rank Vector<T>::insertBinSearch(T* A, T const& e, Rank lo, Rank hi) const{

        // cout<<lo;
    while (lo < hi) { //每步迭代仅需做一次比较判断,有两个分支
        Rank mi = (lo + hi) >> 1; //以中点为轴点
        (e < A[mi]) ? hi = mi : lo = mi + 1; //经比较后确定深入[lo, mi)或(mi, hi)
    } //成功查找不能提前终止
    return --lo; //循环结束时,lo为大于e的元素的最小秩,故lo - 1即不大于e的元素的最大秩
} //有多个命中元素时,总能保证返回秩最大者;查找失败时,能够返回失败的位置

// 可写访问接口
template <typename T> T& Vector<T>::operator[](Rank r) const{ //重载下标操作符,可以类似于数组形式引用各元素
    return _elem[r];
}
template <typename T> Vector<T>& Vector<T>::operator=(Vector<T> const& V ) { //重载赋值操作符,以便直接克隆向量
    if (_elem) delete [] _elem; //释放原有内容
    copyFrom(V._elem, 0, V.size()); //整体复制
    return *this; //返回当前对象的引用,以便链式赋值
}
template <typename T> T Vector<T>::remove(Rank r){ //移除秩为r的元素
    T result = _elem[r];
    remove(r, r + 1);
    return result;
}
template <typename T> int Vector<T>::remove(Rank lo, Rank hi){ //删除秩在区间[lo, hi)之内的元素
    int delta = _size - hi;
    for(Rank i = 0 ; i < delta; i++){
        _elem[lo + i] = _elem[hi + i];
    }
    _size = lo + delta;
    return delta;
}
template <typename T> Rank Vector<T>::insert(Rank r, T const& e){ //插入元素
    expand();
    for(Rank i = _size; i > r; i--){
        _elem[i] = _elem[i - 1];
    }
    _elem[r] = e;
    _size++;
    return r;
}
template <typename T> void Vector<T>::sort(Rank lo, Rank hi){ //对[lo, hi)排序
    switch (rand() % 5) { //随机选取排序算法。可根据具体问题的特点灵活选取或扩充
        // case 1: bubbleSort(lo, hi); break; //起泡排序
        // case 2: selectionSort(lo, hi); break; //选择排序(习题)
        // case 3: mergeSort(lo, hi); break; //归并排序
        // case 4: heapSort(lo, hi); break; //堆排序(稍后介绍)

        // default: quickSort(lo, hi); break; //快速排序(稍后介绍)
        default: mergeSort(lo, hi); break; //快速排序(稍后介绍)
    }
}
template <typename T> void Vector<T>::unsort(Rank lo, Rank hi){ //对[lo, hi)置乱
    T* v = _elem + lo; //将子向量_elem[lo, hi)视作另一向量V[0, hi - lo)
    for (Rank i = hi - lo; i > 0; i--){ //自后向前
        //将V[i - 1]与V[0, i)中某一元素随机交换
        Rank tempRank = rand() % 1;
        swap(v[i - 1], v[tempRank]);
    }
}
template <typename T> int Vector<T>::deduplicate(){ //无序去重
    int oldSize = _size; //记录原规模
    Rank i = 1; //从_elem[1]开始
    while (i < _size) //自前向后逐一考查各元素_elem[i]
        (find(_elem[i], 0, i) < 0) ? //在其前缀中寻找与之雷同者(至多一个)
            i++ : remove(i); //若无雷同则继续考查其后继,否则删除雷同者
    return oldSize - _size; //向量规模变化量,即被删除元素总数
}
template <typename T> int Vector<T>::uniquify(){ //有序去重
    Rank i = 0, j = 0; //各对互异“相邻”元素的秩
    while (++j < _size) //逐一扫描,直至末元素
        if (_elem[i] != _elem[j]) //跳过雷同者
            _elem[++i] = _elem[j]; //发现不同元素时,向前移至紧邻于前者右侧
    _size = ++i; shrink(); //直接截除尾部多余元素
    return j - i; //向量规模变化量,即被删除元素总数
}


// 遍历
template <typename T> void Vector<T>::traverse(void (*visit)(T&)){//利用函数指针机制的遍历,只读或局部性修改
    for (int i = 0; i < _size; i++) visit(_elem[i]); 
}

template <typename T> template <typename VST> //元素类型、操作器
void Vector<T>::traverse(VST& visit){ 
    for (int i = 0; i < _size; i++) visit(_elem[i]); //利用函数对象机制的遍历,可全局性修改
}


template <typename T> static bool lt(T* a, T* b) { return lt(*a, *b); }//less than
template <typename T> static bool lt(T& a, T& b) { return a < b; }//less than
template <typename T> static bool eq(T* a, T* b) { return eq(*a, *b); }//equal
template <typename T> static bool eq(T& a, T& b) { return a == b; }//equal

 #endif /* zhch_vector */