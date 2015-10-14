#include <iostream>
#include <iomanip>
#include <stdlib.h>

using namespace std;

typedef char StackItemType;
class stackP
{
    public:
        stackP(void);
        stackP( const stackP &toCopy );
        ~stackP(void);
        bool isEmpty() const;
        void push(const StackItemType newTop);
        void pop();
        // peek() returns the contents of the top-most element
        StackItemType peek();
        int getCount();
        // If you need to keep track of the size of the stack,
        // use getCount()
        int empty();
        int full();
    private:
        struct stackNode {
            StackItemType item;
            stackNode *next;
        };
        stackNode *top;
        int count;
};
