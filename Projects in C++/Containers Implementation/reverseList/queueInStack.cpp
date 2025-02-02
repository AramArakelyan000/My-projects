#include <iostream>
#include <stack>
#include <stdexcept>

template <typename T>
class QueueUsingStacks {
private:
    std::stack<T> stack1;
    std::stack<T> stack2;

public:

    void enqueue(const T& value) {
        stack1.push(value);
    }

    T dequeue() {
        if (stack2.empty()) {
            while (!stack1.empty()) {
                stack2.push(stack1.top());
                stack1.pop();
            }
        }

        if (stack2.empty()) {
            throw std::underflow_error("Queue is empty");
        }

        T value = stack2.top();
        stack2.pop();
        return value;
    }

    bool isEmpty() const {
        return stack1.empty() && stack2.empty();
    }

    size_t size() const {
        return stack1.size() + stack2.size();
    }
};

int main() {
    QueueUsingStacks<int> queue;

    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);

    std::cout << "Dequeued: " << queue.dequeue() << std::endl;
    std::cout << "Dequeued: " << queue.dequeue() << std::endl;

    queue.enqueue(4);
    queue.enqueue(5);

    std::cout << "Dequeued: " << queue.dequeue() << std::endl;
    std::cout << "Dequeued: " << queue.dequeue() << std::endl;
    std::cout << "Dequeued: " << queue.dequeue() << std::endl;

    try {
        queue.dequeue();
    } catch (const std::underflow_error& e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
