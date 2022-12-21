#include "a.h"

A* A::getInstance(){
    if(_pInstance == NULL){
        _pInstance = new A();
    }
    return _pInstance;
}

A* A::_pInstance = NULL;

A::A(){
    _name = "I am singleton";
}

void A::print(){
    cout << _name << endl;
}