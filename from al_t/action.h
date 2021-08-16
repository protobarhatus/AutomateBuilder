#ifndef ACTION_H
#define ACTION_H
#include<memory>
#include<vector>
class ActionElement;
class Action
{
public:
    Action();

private:
    std::vector<std::shared_ptr<ActionElement>> action_elements;
};

#endif // ACTION_H
