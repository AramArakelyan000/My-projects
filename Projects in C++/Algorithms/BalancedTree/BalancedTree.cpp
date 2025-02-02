#include <iostream>
#include <vector>
#include <queue>
using namespace std;

template <typename T>
struct Node {
    T* data;
    Node* left; 
    Node* right;

    Node(T value) : data(new T(value)), left(nullptr), right(nullptr) {}
};

template <typename T>
Node<T>* buildBalancedTree(vector<T>& data, int start, int end) {
    if (start > end) return nullptr;

    int mid = (start + end) / 2;
    Node<T>* node = new Node<T>(data[mid]);

    node->left = buildBalancedTree(data, start, mid - 1);
    node->right = buildBalancedTree(data, mid + 1, end);

    return node;
}

template <typename T>
int calculateDepth(Node<T>* root) {
    if (!root) return 0;
    return 1 + max(calculateDepth(root->left), calculateDepth(root->right));
}

template <typename T>
void preOrder(Node<T>* root) {
    if (root) {
        cout << *(root->data) << " ";
        preOrder(root->left);
        preOrder(root->right);
    }
}

template <typename T>
void inOrder(Node<T>* root) {
    if (root) {
        inOrder(root->left);
        cout << *(root->data) << " ";
        inOrder(root->right);
    }
}

template <typename T>
void postOrder(Node<T>* root) {
    if (root) {
        postOrder(root->left);
        postOrder(root->right);
        cout << *(root->data) << " ";
    }
}

template <typename T>
void levelOrder(Node<T>* root) {
    if (!root) return;

    queue<Node<T>*> q;
    q.push(root);

    while (!q.empty()) {
        Node<T>* current = q.front();
        q.pop();

        cout << *(current->data) << " ";

        if (current->left) q.push(current->left);
        if (current->right) q.push(current->right);
    }
}

template <typename T>
void deleteTree(Node<T>* root) {
    if (root) {
        deleteTree(root->left);
        deleteTree(root->right);
        delete root->data;
        delete root;
    }
}

int main() {
    vector<int> data = {1, 2, 3, 4, 5, 6, 7};

    Node<int>* root = buildBalancedTree(data, 0, data.size() - 1);

    int depth = calculateDepth(root);
    cout << "Depth of the tree: " << depth << endl;

    cout << "root -> left subtree -> right subtree: ";
    preOrder(root);
    cout << endl;

    cout << "left subtree -> root -> right subtree: ";
    inOrder(root);
    cout << endl;

    cout << "left subtree -> right subtree -> root: ";
    postOrder(root);
    cout << endl;

    cout << "Level-order traversal: ";
    levelOrder(root);
    cout << endl;

    deleteTree(root);

    return 0;
}
