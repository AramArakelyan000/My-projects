#include <iostream>
#include <vector>
#include <chrono>
#include <iostream>
#include <stdexcept>
#include <chrono>

template <typename T>
class Vector {
private:
    T* m_data;
    size_t m_size;    
    size_t m_capacity; 

    void resize(size_t new_capacity) {
        T* new_data = new T[new_capacity];
        for (size_t i = 0; i < m_size; i++) {
            new_data[i] = m_data[i];
        }
        delete[] m_data;
        m_data = new_data;
        m_capacity = new_capacity;
    }

public:
    Vector() : m_data(nullptr), m_size(0), m_capacity(0) {}

    ~Vector() {
        delete[] m_data;
    }

    Vector(const Vector& other) : m_size(other.m_size), m_capacity(other.m_capacity) {
        m_data = new T[m_capacity];
        for (size_t i = 0; i < m_size; i++) {
            m_data[i] = other.m_data[i];
        }
    }

    Vector(Vector&& other) noexcept : m_data(other.m_data), m_size(other.m_size), m_capacity(other.m_capacity) {
        other.m_data = nullptr;
        other.m_size = 0;
        other.m_capacity = 0;
    }

    Vector& operator=(const Vector& other) {
        if (this != &other) {
            delete[] m_data;
            m_size = other.m_size;
            m_capacity = other.m_capacity;
            m_data = new T[m_capacity];
            for (size_t i = 0; i < m_size; i++) {
                m_data[i] = other.m_data[i];
            }
        }
        return *this;
    }

    Vector& operator=(Vector&& other) noexcept {
        if (this != &other) {
            delete[] m_data;
            m_data = other.m_data;
            m_size = other.m_size;
            m_capacity = other.m_capacity;
            other.m_data = nullptr;
            other.m_size = 0;
            other.m_capacity = 0;
        }
        return *this;
    }

    void push_back(const T& value) {
        if (m_size == m_capacity) {
            resize(m_capacity == 0 ? 1 : m_capacity * 2);
        }
        m_data[m_size++] = value;
    }

    void push_front(const T& value) {
        insert(0, value);
    }

    void pop_back() {
        if (m_size == 0) throw std::out_of_range("Vector is empty");
        m_data[m_size - 1].~T();
        m_size--;
    }

    void pop_front() {
        deleteAt(0);
    }

    void insert(size_t index, const T& value) {
        if (index > m_size) throw std::out_of_range("Index out of range");
        if (m_size == m_capacity) {
            resize(m_capacity == 0 ? 1 : m_capacity * 2);
        }

        for (size_t i = m_size; i > index; i--) {
            m_data[i] = m_data[i - 1];
        }
        m_data[index] = value;
        m_size++;
    }

    void deleteAt(size_t index) {
        if (index >= m_size) throw std::out_of_range("Index out of range");
    
        m_data[index].~T();
        for (size_t i = index; i < m_size - 1; i++) {
            m_data[i] = m_data[i + 1];
        }
        m_size--;
    }

    int find(const T& value) const {
        for (size_t i = 0; i < m_size; i++) {
            if (m_data[i] == value) return i;
        }
        return -1;
    }

    T& top() {
        if (m_size == 0) throw std::out_of_range("Vector is empty");
        return m_data[0];
    }

    T& back() {
        if (m_size == 0) throw std::out_of_range("Vector is empty");
        return m_data[m_size - 1];
    }

    T& operator[](size_t index) {
        if (index >= m_size) throw std::out_of_range("Index out of range");
        return m_data[index];
    }

    const T& operator[](size_t index) const {
        if (index >= m_size) throw std::out_of_range("Index out of range");
        return m_data[index];
    }

    void splice(Vector& source, size_t start, size_t count, size_t dest) {

        if (start >= source.m_size || start + count > source.m_size) {
            throw std::out_of_range("Invalid range for source splice");
        }
        if (dest > m_size) {
            throw std::out_of_range("Invalid destination index for splice");
        }

        while (m_size + count > m_capacity) {
            resize(m_capacity == 0 ? 1 : m_capacity * 2);
        }

        for (size_t i = m_size; i > dest; i--) {
            m_data[i + count - 1] = m_data[i - 1];
        }

        for (size_t i = 0; i < count; i++) {
            m_data[dest + i] = source.m_data[start + i];
        }

        for (size_t i = start + count; i < source.m_size; i++) {
            source.m_data[i - count] = source.m_data[i];
        }
        source.m_size -= count;

        m_size += count;
    }

    size_t getSize() const {
        return m_size;
    }

    size_t getCapacity() const {
        return m_capacity;
    }
};

int main() {
    Vector<int> vec1;
    vec1.push_back(1);
    vec1.push_back(2);
    vec1.push_back(3);
    vec1.push_back(4);

    Vector<int> vec2;
    vec2.push_back(10);
    vec2.push_back(20);
    vec2.push_back(30);

    std::cout << "Initial contents of vec1: ";
    for (size_t i = 0; i < vec1.getSize(); i++) {
        std::cout << vec1[i] << " ";
    }
    std::cout << "\nInitial contents of vec2: ";
    for (size_t i = 0; i < vec2.getSize(); i++) {
        std::cout << vec2[i] << " ";
    }
    std::cout << std::endl;

    vec1.push_front(0);
    std::cout << "vec1 after push_front(0): ";
    for (size_t i = 0; i < vec1.getSize(); i++) {
        std::cout << vec1[i] << " ";
    }
    std::cout << std::endl;

    vec1.insert(2, 99);
    std::cout << "vec1 after insert(2, 99): ";
    for (size_t i = 0; i < vec1.getSize(); i++) {
        std::cout << vec1[i] << " ";
    }
    std::cout << std::endl;

    vec1.deleteAt(2);
    std::cout << "vec1 after deleteAt(2): ";
    for (size_t i = 0; i < vec1.getSize(); i++) {
        std::cout << vec1[i] << " ";
    }
    std::cout << std::endl;

    vec1.pop_back();
    std::cout << "vec1 after pop_back(): ";
    for (size_t i = 0; i < vec1.getSize(); i++) {
        std::cout << vec1[i] << " ";
    }
    std::cout << std::endl;

    vec1.pop_front();
    std::cout << "vec1 after pop_front(): ";
    for (size_t i = 0; i < vec1.getSize(); i++) {
        std::cout << vec1[i] << " ";
    }
    std::cout << std::endl;

    int index = vec1.find(2);
    std::cout << "Index of element '2' in vec1: " << index << std::endl;

    std::cout << "Top element of vec1: " << vec1.top() << std::endl;
    std::cout << "Back element of vec1: " << vec1.back() << std::endl;
 
    std::cout << "Contents of vec1 before splice: ";
    for (size_t i = 0; i < vec1.getSize(); i++) {
        std::cout << vec1[i] << " ";
    }
    std::cout << "\nContents of vec2 before splice: ";
    for (size_t i = 0; i < vec2.getSize(); i++) {
        std::cout << vec2[i] << " ";
    }
    std::cout << std::endl;

    vec2.splice(vec1, 1, 2, 1);

    std::cout << "Contents of vec1 after splice: ";
    for (size_t i = 0; i < vec1.getSize(); i++) {
        std::cout << vec1[i] << " ";
    }
    std::cout << "\nContents of vec2 after splice: ";
    for (size_t i = 0; i < vec2.getSize(); i++) {
        std::cout << vec2[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}


struct T {
    int value;
    T(int v) : value(v) {}
    bool operator==(const T& other) const { return value == other.value; }
};

template <typename Func>
long long measure_time(Func func) {
    auto start = std::chrono::high_resolution_clock::now();
    func();
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
}

void performance_test(size_t n) {
    Vector<T> my_vector;
    std::vector<T> std_vector;

    for (size_t i = 0; i < n; ++i) {
        my_vector.push_back(T(i));
        std_vector.push_back(T(i));
    }

    auto my_push_time = measure_time([&]() {
        for (size_t i = 0; i < n; ++i) {
            my_vector.push_back(T(i));
        }
    });

    auto std_push_time = measure_time([&]() {
        for (size_t i = 0; i < n; ++i) {
            std_vector.push_back(T(i));
        }
    });

    auto my_pop_time = measure_time([&]() {
        for (size_t i = 0; i < n; ++i) {
            my_vector.pop_back();
        }
    });

    auto std_pop_time = measure_time([&]() {
        for (size_t i = 0; i < n; ++i) {
            std_vector.pop_back();
        }
    });

    for (size_t i = 0; i < n; ++i) {
        my_vector.push_back(T(i));
        std_vector.push_back(T(i));
    }

    auto my_find_time = measure_time([&]() {
        for (size_t i = 0; i < n; ++i) {
            my_vector.find(T(i));
        }
    });

    auto std_find_time = measure_time([&]() {
        for (size_t i = 0; i < n; ++i) {
            auto it = std::find(std_vector.begin(), std_vector.end(), T(i));
        }
    });

    auto my_delete_time = measure_time([&]() {
        for (size_t i = 0; i < n / 2; ++i) {
            my_vector.deleteAt(0);
        }
    });

    auto std_delete_time = measure_time([&]() {
        for (size_t i = 0; i < n / 2; ++i) {
            std_vector.erase(std_vector.begin());
        }
    });

    std::cout << "Performance results (microseconds):" << std::endl;
    std::cout << "Push back: My Vector = " << my_push_time << ", std::vector = " << std_push_time << std::endl;
    std::cout << "Pop back: My Vector = " << my_pop_time << ", std::vector = " << std_pop_time << std::endl;
    std::cout << "Find: My Vector = " << my_find_time << ", std::vector = " << std_find_time << std::endl;
    std::cout << "Delete: My Vector = " << my_delete_time << ", std::vector = " << std_delete_time << std::endl;
}

int main() {
    size_t n = 10000;
    performance_test(n);
    return 0;
}
