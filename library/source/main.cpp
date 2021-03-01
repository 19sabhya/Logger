#include<iostream>
#include<Logger.hpp>
using namespace std;

int main(){
    try{

        Logger l{"table.txt",enable = true,level=3};

        l(TRACE)<<"hello "<<"world "<<20<<true<<lend;
        l(DEBUG)<<"hello DEBUG"<<lend;
        
        l.If(enable == true ,  ERROR) << "If conditions check"<<lend;

        l.If(level > 2,ERROR) << "Level Checking"<<lend;
        l.If(enable == true && level > 2,ERROR) << "Logger and Level Checking"<<lend;

        l.If(true,ERROR)<<"General check"<<lend;

        l.If(enable == true && false,ERROR)<<"check"<<lend;

    }
    catch(string s){
        cout<<s<<endl;
    }
    return 0;
}