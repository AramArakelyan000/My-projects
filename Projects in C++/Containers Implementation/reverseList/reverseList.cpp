#include <iostream>
#include <list>

void reverseList(std::list<int>& lst) {
    auto front = lst.begin();
    auto back = std::prev(lst.end());

    while (front != back && std::next(front) != back) {
        auto temp = *front;
        *front = *back;
        *back = temp;

        ++front;
        --back;    
    }
}

void printList(const std::list<int>& lst) {
    for (const auto& item : lst) {
        std::cout << item << " ";
    }
    std::cout << std::endl;
}

int main() {

    std::list<int> myList = {1, 2, 3, 4, 5};

    std::cout << "Original list: ";
    printList(myList);

    reverseList(myList);

    std::cout << "Reversed list: ";
    printList(myList);

    return 0;
}
