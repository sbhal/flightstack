#include "stackP.h"

stackP::stackP(void)
{
    top = nullptr;
    count = 0;
}

stackP::stackP(const stackP &toCopy)
{
    top = nullptr;
    count = 0;
    stackNode * copyNode = toCopy.top;
    while(copyNode) {
        push(copyNode->item);
        copyNode = copyNode->next;
    }
}
stackP::~stackP(void)
{
    while(top) {
        pop();
    }
    if (count != 0)
        cout <<"Count isn't zero after deleting all Node!"<<endl;
}

bool stackP::isEmpty(void) const
{
    return (count == 0 ? true : false);
}

void stackP::push(const StackItemType newTop)
{
	cout <<"Pushing into stach - "<<newTop<<endl;
    stackNode *newNode = new stackNode;
    newNode->item = newTop; //should do memcpy
    newNode->next = top;
    top = newNode;
    count++;
}
void stackP::pop(void)
{
    struct stackNode *pop = top;
    if(top != nullptr) {
        pop = top;
        top = top->next;
        count--;
        	cout <<"Popping out - "<<pop->item<<endl;
        delete pop;
    } else {
        cout <<"Error: Cannot pop since list is NULL"<<endl;
    }
}
StackItemType stackP::peek(void)
{
    if(top != nullptr) {
			cout <<"Peeking in- "<<top->item<<endl;
        return top->item;
    } else {
        cout <<"Cannot Peek since List is empty"<<endl;
        return top->item;
    }
}
int stackP::getCount(void)
{
    return count;
}
int stackP::empty(void)
{
    return (count);
}
int stackP::full(void)
{
    return 0;
}
