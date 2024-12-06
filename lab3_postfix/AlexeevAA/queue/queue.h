#include<algorithm>

template <class T>
class Queue
{
    T *dMem;
    int start = 0;
    int end = 0;
    int size;

public:
    Queue(int _size = 1):size(_size)
    {
        if(size < 0){
            throw "is negative";
        }
        dMem = new T[size];
    }
    ~Queue()
    {
        delete[] dMem;
    }
    bool empty()
    {
        return (start == end);
    }
    void push(T value)
    {
        if (end == size)
        {
            T* alt = new T[size];
            std::copy(dMem, dMem + size, alt);

            delete[] dMem;

            size *= 2;
            dMem = new T[size];
            std::copy(alt + start , alt + (start + end), dMem);
            delete[] alt;
            end -= start;
            start = 0;
        }
        dMem[end] = value;
        end++;
    }
    void pop(){
        if(!empty()){
            start++;
        }
        else throw "is empty";
    }
    T front(){
        return dMem[start];
    }
};