#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>
using namespace std;

struct Node {
    int data;
    int index;
    Node *left, *right;

    Node(int d, int i) {
        data = d;
        index = i;
        left = right = nullptr;
    }

    Node(Node* l, Node* r) {
        data = l->data + r->data;
        index = min(l->index, r->index);
        left = l;
        right = r;
    }
};

struct Compare {
    bool operator()(Node* a, Node* b) {
     
        if (a->data != b->data)
            return a->data > b->data;

        return a->index > b->index;
    }
};

void preOrder(Node* root, vector<string> &ans, string curr) {
    if (root == nullptr)
        return;

    if (root->left == nullptr && root->right == nullptr) {
        if (curr == "")
            curr = "0";

        ans[root->index] = curr;
        return;
    }

    preOrder(root->left, ans, curr + '0');

    preOrder(root->right, ans, curr + '1');
}

vector<string> huffmanCodes(string &s, vector<int> freq) {
    int n = s.length();

    priority_queue<Node*, vector<Node*>, Compare> pq;

    for (int i = 0; i < n; i++) {
        Node* tmp = new Node(freq[i], i);
        pq.push(tmp);
    }

    if (n == 1)
        return {"0"};

    while (pq.size() >= 2) {

        Node* l = pq.top();
        pq.pop();

        Node* r = pq.top();
        pq.pop();

        Node* newNode = new Node(l, r);
  
        pq.push(newNode);
    }

    Node* root = pq.top();

    vector<string> ans(n);

    preOrder(root, ans, "");

    return ans;
}

int main() {
    string s = "abcdef";

    vector<int> freq = {5, 9, 12, 13, 16, 45};

    vector<string> ans = huffmanCodes(s, freq);

    for (int i = 0; i < ans.size(); i++) {
        cout << s[i] << ": " << ans[i] << "\n";
    }

    return 0;
}