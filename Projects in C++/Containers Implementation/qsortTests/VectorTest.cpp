#include <iostream>
#include <stdexcept>
#include <vector>
using namespace std;

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

struct TestType {
    int value;
    static int created;
    static int destroyed;

    TestType(int val) : value(val) {
        ++created;
        cout << "Constructor called for value: " << value << endl;
    }

    TestType(const TestType& other) : value(other.value) {
        ++created;
        cout << "Copy constructor called for value: " << value << endl;
    }

    TestType& operator=(const TestType& other) {
        value = other.value;
        cout << "Copy assignment called for value: " << value << endl;
        return *this;
    }

    ~TestType() {
        ++destroyed;
        cout << "Destructor called for value: " << value << endl;
    }

    bool operator<=(const TestType& other) const {
        return value <= other.value;
    }

    bool operator==(const TestType& other) const {
        return value == other.value;
    }
};

struct TestType {
    int value;
    static int created;
    static int destroyed;

    TestType(int val) : value(val) {
        ++created;
        cout << "Constructor called for value: " << value << endl;
    }

    TestType(const TestType& other) : value(other.value) {
        ++created;
        cout << "Copy constructor called for value: " << value << endl;
    }

    TestType& operator=(const TestType& other) {
        value = other.value;
        cout << "Copy assignment called for value: " << value << endl;
        return *this;
    }

    ~TestType() {
        ++destroyed;
        cout << "Destructor called for value: " << value << endl;
    }

    bool operator<=(const TestType& other) const {
        return value <= other.value;
    }

    bool operator==(const TestType& other) const {
        return value == other.value;
    }
};

int TestType::created = 0;
int TestType::destroyed = 0;

void testVector() {
    cout << "\nTesting Custom Vector:\n";
    Vector<TestType> customVector;

    customVector.push_back(TestType(1));
    customVector.push_back(TestType(2));
    customVector.push_back(TestType(3));
    cout << "After push_back(1, 2, 3): ";
    for (size_t i = 0; i < customVector.getSize(); i++) {
        cout << customVector[i].value << " -> ";
    }
    cout << "null\n";

    customVector.push_front(TestType(0));
    cout << "After push_front(0): ";
    for (size_t i = 0; i < customVector.getSize(); i++) {
        cout << customVector[i].value << " -> ";
    }
    cout << "null\n";

    customVector.pop_front();
    cout << "After pop_front: ";
    for (size_t i = 0; i < customVector.getSize(); i++) {
        cout << customVector[i].value << " -> ";
    }
    cout << "null\n";

    customVector.pop_back();
    cout << "After pop_back: ";
    for (size_t i = 0; i < customVector.getSize(); i++) {
        cout << customVector[i].value << " -> ";
    }
    cout << "null\n";

    customVector.insert(1, TestType(5));
    cout << "After insert(1, 5): ";
    for (size_t i = 0; i < customVector.getSize(); i++) {
        cout << customVector[i].value << " -> ";
    }
    cout << "null\n";

    customVector.deleteAt(1);
    cout << "After deleteAt(1): ";
    for (size_t i = 0; i < customVector.getSize(); i++) {
        cout << customVector[i].value << " -> ";
    }
    cout << "null\n";
}

void testStdVector() {
    cout << "\nTesting std::vector:\n";
    std::vector<TestType> stdVector;

    stdVector.push_back(TestType(1));
    stdVector.push_back(TestType(2));
    stdVector.push_back(TestType(3));
    cout << "After push_back(1, 2, 3): ";
    for (const auto& item : stdVector) {
        cout << item.value << " -> ";
    }
    cout << "null\n";

    stdVector.insert(stdVector.begin(), TestType(0));
    cout << "After push_front(0): ";
    for (const auto& item : stdVector) {
        cout << item.value << " -> ";
    }
    cout << "null\n";

    stdVector.erase(stdVector.begin());
    cout << "After pop_front: ";
    for (const auto& item : stdVector) {
        cout << item.value << " -> ";
    }
    cout << "null\n";

    stdVector.pop_back();
    cout << "After pop_back: ";
    for (const auto& item : stdVector) {
        cout << item.value << " -> ";
    }
    cout << "null\n";

    stdVector.insert(stdVector.begin() + 1, TestType(5));
    cout << "After insert(1, 5): ";
    for (const auto& item : stdVector) {
        cout << item.value << " -> ";
    }
    cout << "null\n";

    stdVector.erase(stdVector.begin() + 1);
    cout << "After deleteAt(1): ";
    for (const auto& item : stdVector) {
        cout << item.value << " -> ";
    }
    cout << "null\n";
}

int main() {
    TestType::created = 0;
    TestType::destroyed = 0;

    testVector();
    testStdVector();

    cout << "\nTotal objects created: " << TestType::created << endl;
    cout << "Total objects destroyed: " << TestType::destroyed << endl;

    return 0;
}
