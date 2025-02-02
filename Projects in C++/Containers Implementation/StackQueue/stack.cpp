#include <iostream>
#include <deque>

template <typename T>
class CustomStack {
private:
    std::deque<T> m_data;

public:
    void push(const T& value) {
        m_data.push_back(value);
    }

    void pop() {
        if (!m_data.empty()) {
            m_data.pop_back();
        } else {
            throw std::underflow_error("Stack is empty. Cannot pop.");
        }
    }

    T top() const {
        if (!m_data.empty()) {
            return m_data.back();
        } else {
            throw std::underflow_error("Stack is empty. Cannot access top.");
        }
    }

    bool empty() const {
        return m_data.empty();
    }

    size_t size() const {
        return m_data.size();
    }
};

int main() {
    CustomStack<int> stack;

    stack.push(10);
    stack.push(20);
    stack.push(30);

    std::cout << "Top element: " << stack.top() << "\n";

    stack.pop();
    std::cout << "Top element after pop: " << stack.top() << "\n";

    std::cout << "Stack size: " << stack.size() << "\n";

    return 0;
}
