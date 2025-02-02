#include <iostream>
#include <deque>

template <typename T>
class CustomQueue {
private:
    std::deque<T> m_data;

public:
    void enqueue(const T& value) {
        m_data.push_back(value);
    }

    void dequeue() {
        if (!m_data.empty()) {
            m_data.pop_front();
        } else {
            throw std::underflow_error("Queue is empty. Cannot dequeue.");
        }
    }

    T front() const {
        if (!m_data.empty()) {
            return m_data.front();
        } else {
            throw std::underflow_error("Queue is empty. Cannot access front.");
        }
    }

    T back() const {
        if (!m_data.empty()) {
            return m_data.back();
        } else {
            throw std::underflow_error("Queue is empty. Cannot access back.");
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
    CustomQueue<int> queue;

    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);

    std::cout << "Front element: " << queue.front() << "\n";
    std::cout << "Back element: " << queue.back() << "\n";

    queue.dequeue();
    std::cout << "Front element after dequeue: " << queue.front() << "\n";

    std::cout << "Queue size: " << queue.size() << "\n";

    return 0;
}
