#include <iostream>
#include <thread>

using namespace std;

int t;

void asd(){
    cout<<"void"<<endl;
}

void poin(){
    // int f=*t;
    // int d=&f.str();
    // cout<<d<<endl;
}

class obj{
    public :
        void dr(int x){
            for(int i=0;i<x;i++){
                if(t<1){
                    cin>>t;
                    t=t+3;
                }
                //t++;
                //cout<<"asdf"<<endl;
                //cout<<t<<" ini di fungsi dr"<<endl;
            }
        }

        static void tr(){
            cout<<"static"<<endl;
        } 
};
class thread_obj {
public:
    void operator()(int x)
    {
        for (int i = 0; i < x; i++){
            //t--;
            cout << "Thread using function object as callable"<<endl;
            //cout<<t<<" ini di calss thread_obj"<<endl;
        }

    }
};

int main(){
    obj b;
    //t=24;
    thread cb(&obj::dr,&b,3);
    thread cb2(thread_obj(),3);

    cb.join();

    cb2.join();

    //poin();
    cout<<t<<endl;
    return 0;
}