#include<algorithm>
using std::pair;

template<class T>
class PriorityQueue{
    pair<T, int>* dMem;
    int start = 0;
    int end = 0;
    int size;

private:
    void sorted(){
        std::sort(dMem + start, dMem + (start + end), [](pair<T,int>& a,pair<T,int>& b){
            return a.second < b.second;
        });
    }
public:
    PriorityQueue(int _size = 1):size(_size)
    {
        if(size < 0){
            throw "is negative";
        }
        dMem = new pair<T,int>[size];
    }
    ~PriorityQueue()
    {
        delete[] dMem;
    }
    
    bool empty()
    {
        return (start == end);
    }
    void push(pair<T,int> value)
    {
        if (end == size)
        {
            pair<T,int>* alt = new pair<T,int>[size];
            std::copy(dMem, dMem + size, alt);

            delete[] dMem;

            size *= 2;
            dMem = new pair<T,int>[size];
            std::copy(alt + start , alt + (start + end), dMem);
            delete[] alt;
            end -= start;
            start = 0;
        }
        dMem[end] = value;
        end++;
        sorted();

    }
    void pop(){
        if(!empty()){
            start++;
        }
        else throw "is empty";
    }
    pair<T,int> front(){
        return dMem[start];
    }

};