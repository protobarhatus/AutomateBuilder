#include "mydeleter.h"

MyDeleter::MyDeleter(): del(true) {}
void MyDeleter::operator()(void *ptr)
{
   if (del)
     delete ptr;
}
void MyDeleter::setDelete(bool d)
{
  del = d;
}
