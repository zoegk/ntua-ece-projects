#include <iostream>
#include <climits>

using namespace std;

class btree {
public:
    btree();
    int height();
    void insert(int x);
    int search(int x);
    int min();
    int max();
    void inorder();
    void preorder();
    void postorder();

private:
    struct node {
        int data;
        node *left;
        node *right;
    };
    node *root;

    int getHeight(node *root);
    void insert(node *&root, int x);
    int search(node *root, int x, int level);
    int minValue(node *root);
    int maxValue(node *root);
    void inorderTraversal(node *root);
    void preorderTraversal(node *root);
    void postorderTraversal(node *root);
};

btree::btree() {
    root = nullptr;
}

int btree::height() {
    return getHeight(root);
}

int btree::getHeight(node *root) {
    if (root == nullptr)
        return 0;
    else {
        int leftHeight = getHeight(root->left);
        int rightHeight = getHeight(root->right);

        return (leftHeight > rightHeight) ? (leftHeight + 1) : (rightHeight + 1);
    }
}

void btree::insert(int x) {
    insert(root, x);
}

void btree::insert(node *&root, int x) {
    if (root == nullptr) {
        root = new node;
        root->data = x;
        root->left = root->right = nullptr;
    } else {
        if (x < root->data)
            insert(root->left, x);
        else if (x > root->data)
            insert(root->right, x);
    }
}

int btree::search(int x) {
    return search(root, x, 1);
}

int btree::search(node *root, int x, int level) {
    if (root == nullptr)
        return 0;

    if (root->data == x)
        return level;

    if (x < root->data)
        return search(root->left, x, level + 1);
    else
        return search(root->right, x, level + 1);
}

int btree::min() {
    return minValue(root);
}

int btree::minValue(node *root) {
    node *current = root;
    while (current->left != nullptr)
        current = current->left;
    return current->data;
}

int btree::max() {
    return maxValue(root);
}

int btree::maxValue(node *root) {
    node *current = root;
    while (current->right != nullptr)
        current = current->right;
    return current->data;
}

void btree::inorder() {
    inorderTraversal(root);
}

void btree::inorderTraversal(node *root) {
    if (root == nullptr)
        return;
    inorderTraversal(root->left);
    cout << root->data << " ";
    inorderTraversal(root->right);
}

void btree::preorder() {
    preorderTraversal(root);
}

void btree::preorderTraversal(node *root) {
    if (root == nullptr)
        return;
    cout << root->data << " ";
    preorderTraversal(root->left);
    preorderTraversal(root->right);
}

void btree::postorder() {
    postorderTraversal(root);
}

void btree::postorderTraversal(node *root) {
    if (root == nullptr)
        return;
    postorderTraversal(root->left);
    postorderTraversal(root->right);
    cout << root->data << " ";
}

int main() {
    btree myTree;
    int N, M;
    cin >> N;

    for (int i = 0; i < N; i++) {
        int num;
        cin >> num;
        myTree.insert(num);
    }

    cin >> M;
    int searches[M];
    for (int i = 0; i < M; i++)
        cin >> searches[i];

    cout << myTree.height() << endl;

    cout << myTree.min() << " " << myTree.max() << endl;

    for (int i = 0; i < M-1; i++)
        cout << myTree.search(searches[i]) << " ";
    
    cout << myTree.search(searches[M-1]) << endl;

    myTree.inorder();
    cout << "end" << endl;

    myTree.preorder();
    cout << "end" << endl;

    myTree.postorder();
    cout << "end" << endl;

    return 0;
}
