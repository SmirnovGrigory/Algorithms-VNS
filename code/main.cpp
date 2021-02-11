#include <iostream>

#include "Factory.h"

signed main() {
    auto f = new Factory("simple-test");
    string s("1 345 123 33");
    auto a = Factory::split(s);
    for (auto x :a){
        cout << x << endl;
    }
    return 0;
}
