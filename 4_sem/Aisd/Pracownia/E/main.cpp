#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

struct Node {
    int key;
    int height;
    Node *left;
    Node *right;
};
Node *search(Node *T, int x_key) {
    if (x_key == T->key)
        return T;

    else if (x_key < T->key)
        return search(T->left, x_key);

    else
        return search(T->right, x_key);
}

void printInOrder(Node *T) {
    if (T == nullptr)
        return;

    printInOrder(T->left);
    std::cout << T->key << " ";
    printInOrder(T->right);
}
// test
Node *createNode(int key) {
    Node *node = new Node();
    node->key = key;
    node->height = 0;
    node->left = nullptr;
    node->right = nullptr;
    return node;
}

Node *createExampleTree() {
    Node *root = createNode(10);

    root->left = createNode(5);
    root->right = createNode(15);

    root->left->left = createNode(2);
    root->left->right = createNode(7);

    root->right->left = createNode(12);
    root->right->right = createNode(20);

    return root;
}

void updateHeight(Node *T) {
    int h_TR = (T->right == nullptr) ? 0 : T->right->height,
        h_TL = (T->left == nullptr) ? 0 : T->left->height;

    T->height = std::max(h_TL, h_TR) + 1;
}

int getBalance(Node *T) {
    return (T->right == nullptr ? 0 : T->right->height) - (T->left == nullptr ? 0 : T->left->height);
}

Node *leftRotation(Node *T) {

    Node *child = T->left, *tmp = child->right;
    child->right = T;
    T->left = tmp;

    T->height = std::max((T->left == nullptr) ? 0 : T->left->height,
                         (T->right == nullptr) ? 0 : T->right->height) +
                1;
    child->height = std::max((child->left == nullptr) ? 0 : child->left->height,
                             (child->right == nullptr) ? 0 : child->right->height) +
                    1;

    return child;
}

Node *rightRotation(Node *T) {
    Node *child = T->right, *tmp = child->left;
    child->left = T;
    T->right = tmp;

    T->height = std::max((T->left == nullptr) ? 0 : T->left->height,
                         (T->right == nullptr) ? 0 : T->right->height) +
                1;
    child->height = std::max((child->left == nullptr) ? 0 : child->left->height,
                             (child->right == nullptr) ? 0 : child->right->height) +
                    1;

    return child;
}

Node *rotation(Node *T, int bf) {

    // updateHeight(T);

    // Left Left Case
    if (bf > 1 && getBalance(T->left) >= 0)
        return rightRotation(T);

    // Left Right Case
    if (bf > 1 && getBalance(T->left) < 0) {
        T->left = leftRotation(T->left);
        return rightRotation(T);
    }

    // Right Right Case
    if (bf < -1 && getBalance(T->right) <= 0)
        return leftRotation(T);

    // Right Left Case
    if (bf < -1 && getBalance(T->right) > 0) {
        T->right = rightRotation(T->right);
        return leftRotation(T);
    }

    return T;
}

Node *insert_pom(Node *T, int x_key) {
    if (T == nullptr)
        return createNode(x_key);

    if (x_key < T->key) {
        T->left = insert_pom(T->left, x_key);
    } else {
        T->right = insert_pom(T->right, x_key);
    }
    int h_TR = (T->right == nullptr) ? 0 : T->right->height,
        h_TL = (T->left == nullptr) ? 0 : T->left->height;

    T->height = std::max(h_TL, h_TR) + 1;

    int bf = h_TR - h_TL;
    if (bf < -1 || bf > 1)
        T = rotation(T, bf);

    std::cout << "Klucz" << T->key << " wysokość " << T->height << std::endl;
    return T;
}
void insert(Node *&T, int x_key) {
    T = insert_pom(T, x_key);
}

Node *delete_pom(Node *T, int x_key, bool &deleted) {
    if (T == nullptr)
        return T;

    if (x_key < T->key) {
        T->left = delete_pom(T->left, x_key, deleted);
    } else if (x_key > T->key) {
        T->right = delete_pom(T->right, x_key, deleted);
    } else {
        if (T->left == nullptr) {
            Node *tmp = T->right;
            delete T;
            return tmp;
        } else if (T->right == nullptr) {
            Node *tmp = T->left;
            delete T;
            return tmp;
        } else {
            Node *tmp = T->right;
            while (tmp->left != nullptr)
                tmp = tmp->left;

            T->key = tmp->key;
            T->right = delete_pom(T->right, tmp->key, deleted);
        }
    }

    int h_TR = (T->right == nullptr) ? 0 : T->right->height,
        h_TL = (T->left == nullptr) ? 0 : T->left->height;

    T->height = std::max(h_TL, h_TR) + 1;

    int bf = h_TR - h_TL;
    if (bf < -1 || bf > 1)
        T = rotation(T, bf);

    return T;
}

void deleteNode(Node *&T, int x_key) {
    bool deleted = false;
    T = delete_pom(T, x_key, deleted);
}
struct two {
    int key;
    int level;
};

void levelOrderTraversal(Node *root, std::vector<two> &vec) {
    if (root == nullptr)
        return;

    std::queue<Node *> q;
    q.push(root);

    while (!q.empty()) {
        int levelSize = q.size(); // liczba węzłów na aktualnym poziomie
        two tmp;
        // Przetwarzanie aktualnego poziomu
        for (int i = 0; i < levelSize; ++i) {
            Node *node = q.front();
            q.pop();
            tmp.key = node->key;
            tmp.level = node->height;
            vec.push_back(tmp);

            if (node->left != nullptr)
                q.push(node->left);
            if (node->right != nullptr)
                q.push(node->right);
        }
    }
}
bool compare(two a, two b) {
    return (a.level > b.level) ? true : false;
}

void printByKey(std::vector<two> vec) {
    std::sort(vec.begin(), vec.end(), compare); // Use iterators instead of the vector itself
    std::cout << vec[0].level << ": ";
    for (auto i = 0; i < vec.size() - 1; i++) {
        std::cout << vec[i].key << " ";
        if (vec[i].level != vec[i + 1].level) {
            std::cout << std::endl;
            std::cout << vec[i + 1].level << ": ";
        }
    }
    std::cout << vec[vec.size() - 1].key << std::endl;
}

void upperBound(Node *T, int x_key) {
    if (T == nullptr)
        return;

    if (T->key == x_key) {
        std::cout << T->key << std::endl;
        return;
    }

    if (T->key < x_key) {
        if (T->right == nullptr) {
            std::cout << T->key << std::endl;
            return;
        } else {
            upperBound(T->right, x_key);
        }
    } else {
        if (T->left == nullptr) {
            std::cout << T->key << std::endl;
            return;
        } else {
            upperBound(T->left, x_key);
        }
    }
}

void lowerBound(Node *T, int x_key) {
    if (T == nullptr)
        return;

    if (T->key == x_key) {
        std::cout << T->key << std::endl;
        return;
    }

    if (T->key < x_key) {
        if (T->right == nullptr) {
            std::cout << T->key << std::endl;
            return;
        } else {
            lowerBound(T->right, x_key);
        }
    } else {
        if (T->left == nullptr) {
            std::cout << T->key << std::endl;
            return;
        } else {
            lowerBound(T->left, x_key);
        }
    }
}
int main() {
    std::vector<two> vec;
    Node *T = createNode(10);
    insert(T, 5);
    insert(T, 20);
    insert(T, 21);
    levelOrderTraversal(T, vec);
    printByKey(vec);
    std::cout << std::endl;
    insert(T, 22);
    insert(T, 15);
    deleteNode(T, 22);
    // insert(T, 2);
    //    insert(T, 7);
    //    insert(T, 1);

    std::cout << "klucz kurwa" << std::endl;
    std::cout << T->key << std::endl;

    // printInOrder(T);
    vec.clear();
    levelOrderTraversal(T, vec);
    printByKey(vec);

    std::cout << std::endl;
    // printInOrder(T);
    return 0;
}