#include <easylogging++.h>

#include <plh/Event/Mouse.h>

void Mouse::onScroll() 
{ 
    LOG(INFO) << "onScroll"; 
};