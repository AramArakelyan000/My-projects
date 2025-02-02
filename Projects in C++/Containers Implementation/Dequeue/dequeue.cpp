#include <iostream>
#include <list>

template <typename T>
class Dequeue {
private:
    std::list<T> container;

public:

    Dequeue() = default;

    Dequeue(std::initializer_list<T> init_list) : container(init_list) {}

    bool empty() const {
        return container.empty();
    }

    void push_back(const T& value) {
        container.push_back(value);
    }

    void push_front(const T& value) {
        container.push_front(value);
    }

    void pop_back() {
        if (!empty()) {
            container.pop_back();
        }
    }

    void pop_front() {
        if (!empty()) {
            container.pop_front();
        }
    }

    T& front() {
        return container.front();
    }

    T& back() {
        return container.back();
    }

    size_t size() const {
        return container.size();
    }
};

int main() {
    Dequeue<int> dq;

    dq.push_back(10);
    dq.push_back(20);
    dq.push_front(5);

    std::cout << "Front: " << dq.front() << std::endl; 
    std::cout << "Back: " << dq.back() << std::endl;   
    std::cout << "Size: " << dq.size() << std::endl;    

    dq.pop_front();
    std::cout << "Front after pop: " << dq.front() << std::endl; 

    dq.pop_back();
    std::cout << "Back after pop: " << dq.back() << std::endl; 

    return 0;
}
