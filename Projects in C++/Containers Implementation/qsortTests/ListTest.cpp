#include <iostream>
#include <stdexcept>
#include <list>
using namespace std;

template<typename T>
class Node {
private:
    const T m_data;
    Node* m_next;

public:
    explicit Node(const T& value) : m_data(value), m_next(nullptr) {}

    const T& get_data() const {
        return m_data;
    }

    Node* get_next() const {
        return m_next;
    }

    void set_next(Node* nextNode) {
        m_next = nextNode;
    }
    
    ~Node() = default;
};

template<typename T>
class LinkedList {
private:
    Node<T>* m_head;

    void clear() {
        while (!is_empty()) {
            pop_front();
        }
    }

    Node<T>* merge(Node<T>* left, Node<T>* right) {
        if (!left) return right;
        if (!right) return left;

        if (left->get_data() <= right->get_data()) {
            left->set_next(merge(left->get_next(), right));
            return left;
        } else {
            right->set_next(merge(left, right->get_next()));
            return right;
        }
    }

    Node<T>* mergeSort(Node<T>* head) {
        if (!head || !head->get_next()) return head;

        Node<T>* slow = head;
        Node<T>* fast = head;
        Node<T>* prev = nullptr;

        while (fast && fast->get_next()) {
            prev = slow;
            slow = slow->get_next();
            fast = fast->get_next()->get_next();
        }

        prev->set_next(nullptr);

        Node<T>* left = mergeSort(head);
        Node<T>* right = mergeSort(slow);

        return merge(left, right);
    }

public:
    void sort() {
        m_head = mergeSort(m_head);
    }

public:
    LinkedList() : m_head(nullptr) {}

    bool is_empty() const {
        return m_head == nullptr;
    }

    LinkedList(const LinkedList& other) : m_head(nullptr) {
        Node<T>* temp = other.m_head;
        while (temp) {
            push_back(temp->get_data());
            temp = temp->get_next();
        }
    }

    LinkedList(LinkedList&& other) noexcept : m_head(other.m_head) {
        other.m_head = nullptr;
    }

    LinkedList& operator=(const LinkedList& other) {
        if (this == &other) return *this;
        clear();
        Node<T>* temp = other.m_head;
        while (temp) {
            push_back(temp->get_data());
            temp = temp->get_next();
        }
        return *this;
    }

    LinkedList& operator=(LinkedList&& other) noexcept {
        if (this == &other) return *this;
        clear();
        m_head = other.m_head;
        other.m_head = nullptr;
        return *this;
    }

    void push_front(const T& value) {
        Node<T>* newNode = new Node<T>(value);
        newNode->set_next(m_head);
        m_head = newNode;
    }

    void push_back(const T& value) {
        Node<T>* newNode = new Node<T>(value);
        if (is_empty()) {
            m_head = newNode;
            return;
        }
        Node<T>* temp = m_head;
        while (temp->get_next()) {
            temp = temp->get_next();
        }
        temp->set_next(newNode);
    }

    void pop_front() {
        if (is_empty()) return;
        Node<T>* temp = m_head;
        m_head = m_head->get_next();
        delete temp;
    }

    void pop_back() {
        if (is_empty()) return;
        if (!m_head->get_next()) {
            delete m_head;
            m_head = nullptr;
            return;
        }
        Node<T>* temp = m_head;
        while (temp->get_next()->get_next()) {
            temp = temp->get_next();
        }
        delete temp->get_next();
        temp->set_next(nullptr);
    }

    void insert(int index, const T& value) {
        if (index == 0) {
            push_front(value);
            return;
        }
        Node<T>* temp = m_head;
        for (int i = 0; i < index - 1 && temp; i++) {
            temp = temp->get_next();
        }
        if (!temp) return;
        Node<T>* newNode = new Node<T>(value);
        newNode->set_next(temp->get_next());
        temp->set_next(newNode);
    }

    void delete_value(const T& value) {
        if (is_empty()) return;
        if (m_head->get_data() == value) {
            pop_front();
            return;
        }
        Node<T>* temp = m_head;
        while (temp->get_next() && temp->get_next()->get_data() != value) {
            temp = temp->get_next();
        }
        if (temp->get_next()) {
            Node<T>* toDelete = temp->get_next();
            temp->set_next(temp->get_next()->get_next());
            delete toDelete;
        }
    }

    int find(const T& value) const {
        Node<T>* temp = m_head;
        int index = 0;
        while (temp) {
            if (temp->get_data() == value) return index;
            temp = temp->get_next();
            index++;
        }
        return -1;
    }

    T top() const {
        if (!is_empty()) return m_head->get_data();
        throw runtime_error("List is empty");
    }

    T back() const {
        if (is_empty()) throw runtime_error("List is empty");
        Node<T>* temp = m_head;
        while (temp->get_next()) {
            temp = temp->get_next();
        }
        return temp->get_data();
    }

    T index(int idx) const {
        Node<T>* temp = m_head;
        for (int i = 0; i < idx && temp; i++) {
            temp = temp->get_next();
        }
        if (temp) return temp->get_data();
        throw out_of_range("Index out of range");
    }

    void splice(LinkedList& source, int start, int end, int dest) {
        if (start >= end || source.is_empty() || this == &source) return;

        Node<T>* prevStartNode = nullptr;
        Node<T>* startNode = source.m_head;
        Node<T>* endNode = source.m_head;
        Node<T>* temp = source.m_head;

        for (int i = 0; temp != nullptr && i <= end; ++i) {
            if (i == start - 1) prevStartNode = temp;
            if (i == start) startNode = temp;
            if (i == end) endNode = temp;
            temp = temp->get_next();
        }

        if (startNode == nullptr || endNode == nullptr) return;

        Node<T>* nextSegment = endNode->get_next();
        endNode->set_next(nullptr);

        if (prevStartNode) {
            prevStartNode->set_next(nextSegment);
        } else {
            source.m_head = nextSegment;
        }

        if (dest == 0) {
            endNode->set_next(this->m_head);
            this->m_head = startNode;
            return;
        }

        Node<T>* destNode = this->m_head;
        for (int i = 0; i < dest - 1 && destNode != nullptr; ++i) {
            destNode = destNode->get_next();
        }

        if (destNode == nullptr) return;

        endNode->set_next(destNode->get_next());
        destNode->set_next(startNode);
    }

    void printList() const {
        Node<T>* temp = m_head;
        while (temp) {
            cout << temp->get_data() << " -> ";
            temp = temp->get_next();
        }
        cout << "null" << endl;
    }

    ~LinkedList() {
        clear();
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

void testLinkedList() {
    cout << "\nTesting LinkedList:\n";
    LinkedList<TestType> list1;

    list1.push_back(TestType(1));
    list1.push_back(TestType(2));
    list1.push_back(TestType(3));
    cout << "After push_back(1, 2, 3): ";
    list1.printList();

    list1.push_front(TestType(0));
    cout << "After push_front(0): ";
    list1.printList();

    list1.pop_front();
    cout << "After pop_front: ";
    list1.printList();

    list1.pop_back();
    cout << "After pop_back: ";
    list1.printList();

    list1.insert(1, TestType(5));
    cout << "After insert(1, 5): ";
    list1.printList();

    list1.delete_value(TestType(5));
    cout << "After delete_value(5): ";
    list1.printList();
}

void testStdList() {
    cout << "\nTesting std::list:\n";
    list<TestType> stdList;

    stdList.push_back(TestType(1));
    stdList.push_back(TestType(2));
    stdList.push_back(TestType(3));
    cout << "After push_back(1, 2, 3): ";
    for (const auto& item : stdList) {
        cout << item.value << " -> ";
    }
    cout << "null\n";

    stdList.push_front(TestType(0));
    cout << "After push_front(0): ";
    for (const auto& item : stdList) {
        cout << item.value << " -> ";
    }
    cout << "null\n";

    stdList.pop_front();
    cout << "After pop_front: ";
    for (const auto& item : stdList) {
        cout << item.value << " -> ";
    }
    cout << "null\n";

    stdList.pop_back();
    cout << "After pop_back: ";
    for (const auto& item : stdList) {
        cout << item.value << " -> ";
    }
    cout << "null\n";

    auto it = stdList.begin();
    advance(it, 1);
    stdList.insert(it, TestType(5));
    cout << "After insert(1, 5): ";
    for (const auto& item : stdList) {
        cout << item.value << " -> ";
    }
    cout << "null\n";

    stdList.remove(TestType(5));
    cout << "After delete_value(5): ";
    for (const auto& item : stdList) {
        cout << item.value << " -> ";
    }
    cout << "null\n";
}

int main() {
    TestType::created = 0;
    TestType::destroyed = 0;

    testLinkedList();
    testStdList();

    cout << "\nTotal objects created: " << TestType::created << endl;
    cout << "Total objects destroyed: " << TestType::destroyed << endl;

    return 0;
}

