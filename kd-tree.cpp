#include<bits/stdc++.h>

using namespace std;
#define MAX_DIM 2

struct node {
    vector<int> x;
    node *left = nullptr, *right = nullptr;

    node(vector<int> y) {
        x = y;
    }
};

int dist(node *a, node *b) {
    int dim = MAX_DIM;
    int tot = 0;
    while (dim--) {
        int val = a->x[dim] - b->x[dim];
        tot += val * val;
    }
    return tot;
}

int idx;

bool cmp(const node &a, const node &b) {
    return a.x[idx] < b.x[idx];
}

int _median(node *arr, int l, int r, int dim) {
    idx = dim;
    sort(arr + l, arr + r + 1, cmp);
    int mid = (l + r) / 2;
    for (int i = mid; i > l; i--) {
        if (arr[i - 1].x[dim] == arr[i].x[dim]) {
            mid = i - 1;
        } else {
            break;
        }
    }
    return mid;
}

node *make_tree(node *arr, int l, int r, int i) {
    if (r < l)
        return nullptr;
    if (l == r) {
        return &arr[l];
    }
    int idx = _median(arr, l, r, i);
    node *new_node = &arr[idx];
    new_node->left = make_tree(arr, l, idx - 1, (i + 1) % MAX_DIM);
    new_node->right = make_tree(arr, idx + 1, r, (i + 1) % MAX_DIM);
    return new_node;
}

node *insert(node *root, node *given, int depth) {
    if (root == nullptr)
        return given;
    if (given->x[depth] < root->x[depth])
        root->left = insert(root->left, given, (depth + 1) % MAX_DIM);
    else
        root->right = insert(root->right, given, (depth + 1) % MAX_DIM);
    return root;
}

bool search(node *root, node *given, int dep) {
    if (root == nullptr)
        return false;
    if (root->x == given->x)
        return true;
    if (root->x[dep] > given->x[dep])
        return search(root->left, given, (dep + 1) % MAX_DIM);
    return search(root->right, given, (dep + 1) % MAX_DIM);
}

node *min_node(int dim, node *x, node *y = nullptr, node *z = nullptr) {
    node *res = x;
    if (y != nullptr && y->x[dim] < res->x[dim]) {
        res = y;
    }
    if (z != nullptr && z->x[dim] < res->x[dim]) {
        res = z;
    }
    return res;
}

node *find_min(node *root, int dep, int dim) {
    if (root == nullptr)
        return nullptr;
    if (dep == dim) {
        return min_node(dim, root, find_min(root->left, (dep + 1) % MAX_DIM, dim));
    } else {
        return min_node(dim, root, find_min(root->left, (dep + 1) % MAX_DIM, dim),
                        find_min(root->right, (dep + 1) % MAX_DIM, dim));
    }
}

node *_delete(node *root, node *given, int depth) {
    if (root == nullptr)
        return nullptr;
    if (root->x == given->x) {
        if (root->right != nullptr) {
            node *_min = find_min(root->right, depth, depth);
            root->x = _min->x;
            root->right = _delete(root->right, _min, (depth + 1) % MAX_DIM);
        } else if (root->left != nullptr) {
            node *_min = find_min(root->left, depth, depth);
            root->x = _min->x;
            root->right = _delete(root->left, _min, (depth + 1) % MAX_DIM);
        } else {
            delete root;
            return nullptr;
        }
        return root;
    }
    if (given->x[depth] < root->x[depth])
        root->left = _delete(root->left, given, (depth + 1) % MAX_DIM);
    else
        root->right = _delete(root->right, given, (depth + 1) % MAX_DIM);
    return root;
}

node *nn(node *root, node *given, int i, node *best, int *_dist) {
    if (root == nullptr) {
        return best;
    }
    int d = dist(root, given);
    bool left = root->x[i] > given->x[i];
    int best_possible_dist = (root->x[i] - given->x[i]) * (root->x[i] - given->x[i]);
    if (best == nullptr || d < *_dist) {
        best = root;
        *_dist = d;
    }
    i = (i + 1) % MAX_DIM;
    best = nn(left ? root->left : root->right, given, i, best, _dist);
    if (best_possible_dist >= *_dist) return best;
    best = nn(left ? root->right : root->left, given, i, best, _dist);
    return best;
}


int main(void) {
    node sample[] = {
            {{10, 3}},
            {{5,  4}},
            {{9,  6}},
            {{4,  7}},
            {{8,  10}},
            {{7,  20}}
    };
    node testNode = {{9, 1}};
    node *root, *found = nullptr;
    int _dist = INT_MAX;

    root = make_tree(sample, 0, (sizeof(sample) / sizeof(sample[1])) - 1, 0);

    found = nn(root, &testNode, 0, found, &_dist);
    cout << found->x[0] << " " << found->x[1] << " at dist " << _dist << endl;
    node given({10, 3});
    cout << search(root, &given, 0);
    insert(root, &given, 0);
    cout << search(root, &given, 0);
    cout << find_min(root, 0, 0)->x[0] << endl;
    cout << find_min(root, 0, 1)->x[1] << endl;
    _delete(root, &given, 0);
    cout << search(root, &given, 0);
    cout << find_min(root, 0, 0)->x[0] << endl;
    cout << find_min(root, 0, 1)->x[1] << endl;
    return 0;
}