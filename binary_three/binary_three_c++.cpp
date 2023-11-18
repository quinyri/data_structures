#include <iostream>
using namespace std;

struct tree_element {
    int value;
    struct tree_element* left;
    struct tree_element* right;
    int height;
};

tree_element* create_tree_element(int i);
void insert_into_tree(tree_element*& root, tree_element* elem);
void print_tree(tree_element* cur_elem);
tree_element* search_tree(tree_element* root, int key);
tree_element* delete_from_tree(tree_element* root, int key);
void deallocate_tree(tree_element* root);

int max(int a, int b) {
    return (a > b) ? a : b;
}

int height(tree_element* node) {
    if (node == NULL)
        return 0;
    return node->height;
}

int getBalance(tree_element* node) {
    if (node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}

tree_element* rightRotate(tree_element* y) {
    tree_element* x = y->left;
    tree_element* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

tree_element* leftRotate(tree_element* x) {
    tree_element* y = x->right;
    tree_element* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

void insert_into_tree(tree_element*& root, tree_element* elem) {
    if (root == NULL) {
        root = elem;
        return;
    }

    if (elem->value < root->value) {
        insert_into_tree(root->left, elem);
    } else {
        insert_into_tree(root->right, elem);
    }

    root->height = 1 + max(height(root->left), height(root->right));

    int balance = getBalance(root);

    if (balance > 1 && elem->value < root->left->value)
        root = rightRotate(root);

    if (balance < -1 && elem->value > root->right->value)
        root = leftRotate(root);

    if (balance > 1 && elem->value > root->left->value) {
        root->left = leftRotate(root->left);
        root = rightRotate(root);
    }

    if (balance < -1 && elem->value < root->right->value) {
        root->right = rightRotate(root->right);
        root = leftRotate(root);
    }
}

tree_element* create_tree_element(int i) {
    tree_element* elem = new tree_element;
    elem->value = i;
    elem->left = NULL;
    elem->right = NULL;
    elem->height = 1;
    return elem;
}

void print_tree(tree_element* cur_elem) {
    if (cur_elem == NULL) {
        return;
    }

    if (cur_elem->left != NULL) {
        print_tree(cur_elem->left);
    }

    cout << "Value = " << cur_elem->value << " Height = " << cur_elem->height << endl;

    if (cur_elem->right != NULL) {
        print_tree(cur_elem->right);
    }
}

tree_element* search_tree(tree_element* root, int key) {
    if (root == NULL || root->value == key)
        return root;

    if (key < root->value)
        return search_tree(root->left, key);

    return search_tree(root->right, key);
}

tree_element* minValueNode(tree_element* node) {
    tree_element* current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}

tree_element* delete_from_tree(tree_element* root, int key) {
    if (root == NULL)
        return root;

    if (key < root->value)
        root->left = delete_from_tree(root->left, key);
    else if (key > root->value)
        root->right = delete_from_tree(root->right, key);
    else {
        if (root->left == NULL) {
            tree_element* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == NULL) {
            tree_element* temp = root->left;
            delete root;
            return temp;
        }

        tree_element* temp = minValueNode(root->right);
        root->value = temp->value;
        root->right = delete_from_tree(root->right, temp->value);
    }

    if (root == NULL)
        return root;

    root->height = 1 + max(height(root->left), height(root->right));

    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

void deallocate_tree(tree_element* root) {
    if (root != nullptr) {
        deallocate_tree(root->left);
        deallocate_tree(root->right);
        delete root;
    }
}

int main() {
    int a[7] = {-3, 1, -5, 42, 2, -6, 8};
    tree_element* root = create_tree_element(a[0]);

    for (int i = 1; i < 7; i++) {
        tree_element* el = create_tree_element(a[i]);
        insert_into_tree(root, el);
    }

    if (root != nullptr) {
        cout << "Original Tree:" << endl;
        print_tree(root);
    } else {
        cout << "Tree is empty." << endl;
    }

    int search_key = 2;
    tree_element* search_result = search_tree(root, search_key);
    if (search_result)
        cout << "Node with value " << search_key << " found in the tree." << endl;
    else
        cout << "Node with value " << search_key << " not found in the tree." << endl;

    int delete_key = -5;
    root = delete_from_tree(root, delete_key);
    cout << "Tree after deleting node with value " << delete_key << ":" << endl;
    print_tree(root);

    deallocate_tree(root);

    return 0;
}
