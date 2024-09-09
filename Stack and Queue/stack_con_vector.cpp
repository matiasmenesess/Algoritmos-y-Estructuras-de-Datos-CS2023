#include <iostream>
#include <vector>
using namespace std;

template<typename T>
class Stack{

    vector<T> Stack_;
    int size;

public:

    Stack(int size){
        this->size = size;
    }

    void push(int val) {
        if(Stack_.size() != size)
        Stack_.push_back(val);
    }

    void pop() {
        Stack_.pop_back();
    }

    bool isempty(){
        if(Stack_.size()==0){
            return true;
        }
    }

    bool isfull(){
        if(Stack_.size()==size){
            return true;
        }
    }

    T top(){
        return Stack_.back();
    }

};

int main() {



    return 0;
}
