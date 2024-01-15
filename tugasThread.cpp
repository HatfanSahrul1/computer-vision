#include <iostream>
#include <thread>

using namespace std;

int a,b;
static bool isDone=true;

void hello(){
    while(isDone){
        cout<<"Hello World"<<endl;
    }
}

void jumlah(){
    cin>>a;
    cin>>b;

    isDone=false;
    
}

int main(){
    //isDone=false;
    // hello();
    thread p1(hello);
    thread p2(jumlah);


    p1.join();
    p2.join();
    
    cout<<a+b<<endl;
    return 0;
}