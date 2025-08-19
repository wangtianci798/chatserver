#include "json.hpp"

using nlohmann::json;

#include <iostream>
#include <vector>
#include <map>
using namespace std;


void func1(){
    json js;
    js["msg_type"] = 2;
    js["from"] = "zhan san";
    js["to"] = "li si";
    js["msg"] = "hello, what are you doing now?";

    cout<<js <<endl;
}

int main(){
    func1();

    return 0;
}