#include <iostream>
#include <thread>

using namespace std;

class obj{
    public :
        void dr(int x){
            for(int i=0;i<x;i++){
                cout<<"asdf"<<endl;
            }
        } 
};
class thread_obj {
public:
    void operator()(int x)
    {
        for (int i = 0; i < x; i++)
            cout << "Thread using function"
                    " object as callable\n";
    }
};

int main(){
    obj b;
    thread cb(&obj::dr,&b,3);
    thread cb2(thread_obj(),3);

    cb.join();
    
    cb2.join();

    return 0;
}