#ifndef MYDELETER_H
#define MYDELETER_H

//КОСТЫЫЫЫЫЛЬ, deleter который ничего не удаляет
class MyDeleter
{
public:
    MyDeleter();
      void operator()(void *ptr);
      void setDelete(bool d);
    private:
      bool del;
};

#endif // MYDELETER_H
