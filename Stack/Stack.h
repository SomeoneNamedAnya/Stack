class Stack {

public:
    Stack();
    ~Stack();

    Stack(const Stack&);
    Stack(const Stack&&);

    Stack& operator=(const Stack& other);
    Stack& operator=(Stack&& other);

    void pop();
    void push(int);
    int top();

private:
    int size;
    int * head;
};
