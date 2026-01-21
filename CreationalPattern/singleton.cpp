#include <bits/stdc++.h>
using namespace std;


class MeyersSingleton {
private:
    MeyersSingleton() {}

public:
    static MeyersSingleton* getInstance() {
        static MeyersSingleton * instance = new MeyersSingleton();
        return instance;
    }
};

int main(){
    MeyersSingleton *meyersSingletonPtr = MeyersSingleton::getInstance();
    return 0;
}