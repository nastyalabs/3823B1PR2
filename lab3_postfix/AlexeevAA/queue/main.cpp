#include<iostream>
#include "queue.h"
#include "priority_queue.h"
#include "queue_with_stack.h"
int main(){
    /*
    Queue<int> q(3);
    q.push(7);
    q.push(6);
    q.push(2);
    std::cout << q.front();
    q.pop();
    q.pop();
    std::cout << q.front();
    q.push(1);
    q.push(0);
    while(!q.empty()){
        std::cout << q.front();
        q.pop();
    }
    */
   
    PriorityQueue<int> a(3);
    a.push(pair<int,int>(34,5));
    a.push(pair<int,int>(2,3));
    a.push(pair<int,int>(23,6));
    std::cout << a.front().first << a.front().second << " ";
    a.pop();
    a.pop();
    a.push(pair<int,int>(67,2));
    std::cout << a.front().first << a.front().second<< " ";
    a.pop();
    a.push(pair<int,int>(67,1));
    a.push(pair<int,int>(7,2));
    while(!a.empty()){
        std::cout << a.front().first << a.front().second<< " ";
        a.pop();
    }
    
   /*
   QueueStack<int> a;
   a.push(5);
   a.push(3);
   std::cout << a.front();
   a.pop();
   std::cout << a.front();
   */

}