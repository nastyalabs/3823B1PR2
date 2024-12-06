#include<stack>

template<class T>
class QueueStack{
    std::stack<T> in;
    std::stack<T> out;
public:
    QueueStack(){}
    ~QueueStack(){}

    void push(T a){
        in.push(a);
    }
    void pop(){
        if(out.empty()){
            if(!in.empty()){
                while(!in.empty()){
                    out.push(in.top());
                    in.pop();
                }
            }
            else throw "empty queue";
            out.pop();
        }
        out.pop();
    }
    T front(){
        if(out.empty()){
            if(!in.empty()){
                while(!in.empty()){
                    out.push(in.top());
                    in.pop();
                }
            }
            else throw "empty queue";
            return out.top();
        }
        return out.top();
    }
};