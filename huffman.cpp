// #include <iostream>
// #include <cstring>

// using namespace std;

// struct MinNode {
//     char data;
//     unsigned freq;
//     MinNode *left, *right;

//     MinNode(char data, unsigned freq) {
//         left = right = nullptr;
//         this->data = data;
//         this->freq = freq;
//     }
// };

// struct MinHeap {
//     int size;
//     int capacity;
//     MinNode** arr;

//     MinHeap(int capacity) {
//         this->size = 0;
//         this->capacity = capacity;
//         this->arr = new MinNode*[capacity];
//     }

//     ~MinHeap() {
//         delete[] arr;
//     }

//     void swapNodes(MinNode** a, MinNode** b) {
//         MinNode* t = *a;
//         *a = *b;
//         *b = t;
//     }

//     void minHeapify(int idx) {
//         int smallest = idx;
//         int left = 2 * idx + 1;
//         int right = 2 * idx + 2;

//         if (left < size && arr[left]->freq < arr[smallest]->freq)
//             smallest = left;
//         if (right < size && arr[right]->freq < arr[smallest]->freq)
//             smallest = right;

//         if (smallest != idx) {
//             swapNodes(&arr[smallest], &arr[idx]);
//             minHeapify(smallest);
//         }
//     }

//     MinNode* extractMin() {
//         if (size <= 0) return nullptr;
//         if (size == 1) {
//             size--;
//             return arr[0];
//         }
//         MinNode* root = arr[0];
//         arr[0] = arr[size - 1];
//         size--;
//         minHeapify(0);
//         return root;
//     }

//     void insert(MinNode* node) {
//         size++;
//         int i = size - 1;
//         arr[i] = node;
//         while (i != 0 && arr[(i - 1) / 2]->freq > arr[i]->freq) {
//             swapNodes(&arr[i], &arr[(i - 1) / 2]);
//             i = (i - 1) / 2;
//         }
//     }
// };


// struct CodeInfo {
//     char data;
//     char code[50];
//     int length;
// };


// void generateCodes(MinNode* root, char arr[], int top, CodeInfo codeTable[], int& tableSize) {
//     if (root->left) {
//         arr[top] = '0';
//         generateCodes(root->left, arr, top + 1, codeTable, tableSize);
//     }

//     if (root->right) {
//         arr[top] = '1';
//         generateCodes(root->right, arr, top + 1, codeTable, tableSize);
//     }

 
//     if (!root->left && !root->right) {
//         codeTable[tableSize].data = root->data;
//         codeTable[tableSize].length = top;
//         for (int i = 0; i < top; i++) {
//             codeTable[tableSize].code[i] = arr[i];
//         }
//         codeTable[tableSize].code[top] = '\0';
//         tableSize++;
//     }
// }

// int main() {
//     const char* text = "aabbbbabbbbcccdddeeecccceedeee";
//     int textLength = strlen(text);

//     cout << "Text: " << text << "\n\n";


//     int freq[256] = {0};
//     for (int i = 0; i < textLength; i++) {
//         freq[(unsigned char)text[i]]++;
//     }

//     int uniqueCount = 0;
//     for (int i = 0; i < 256; i++) {
//         if (freq[i] > 0) uniqueCount++;
//     }

//     MinHeap minHeap(uniqueCount);
//     for (int i = 0; i < 256; i++) {
//         if (freq[i] > 0) {
//             minHeap.insert(new MinNode((char)i, freq[i]));
//         }
//     }

//     while (minHeap.size > 1) {
//         MinNode* left = minHeap.extractMin();
//         MinNode* right = minHeap.extractMin();

//         MinNode* topNode = new MinNode('$', left->freq + right->freq);
//         topNode->left = left;
//         topNode->right = right;

//         minHeap.insert(topNode);
//     }

//     MinNode* root = minHeap.extractMin();

//     char tempArr[100];
//     CodeInfo codeTable[256];
//     int tableSize = 0;
//     generateCodes(root, tempArr, 0, codeTable, tableSize);

//     cout << "Huffman Codes:\n";
//     for (int i = 0; i < tableSize; i++) {
//         cout << "'" << codeTable[i].data << "' : " << codeTable[i].code << "\n";
//     }

//     int asciiBits = textLength * 8;
//     int huffmanBits = 0;

//     for (int i = 0; i < textLength; i++) {
//         char ch = text[i];
//         for (int j = 0; j < tableSize; j++) {
//             if (codeTable[j].data == ch) {
//                 huffmanBits += codeTable[j].length;
//                 break;
//             }
//         }
//     }

//     int spaceSaved = asciiBits - huffmanBits;

//     cout << "\n--- Bit Count Comparison ---\n";
//     cout << "Without Huffman (Standard ASCII): " << asciiBits << " bits\n";
//     cout << "With Huffman (Compressed):  " << huffmanBits << " bits\n";
//     cout << "Total Space Saved:  " << spaceSaved << " bits\n";

//     return 0;
// }






#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>
using namespace std;

// Struct to represent Huffman tree node
struct Node {
    int data;   // frequency
    int index;  // smallest original index in subtree
    Node *left, *right;

    // Leaf node
    Node(int d, int i) {
        data = d;
        index = i;
        left = right = nullptr;
    }

    // Internal node
    Node(Node* l, Node* r) {
        data = l->data + r->data;
        index = min(l->index, r->index); // important for tie-break
        left = l;
        right = r;
    }
};

// Custom min heap for Node struct
struct Compare {
    bool operator() (Node* a, Node* b) {
        // smaller freq first
        if (a->data != b->data)
            return a->data > b->data;  
        // when freq are equal
        return a->index > b->index;    
    }
};

// Function to traverse tree in preorder
// manner and push the Huffman representation
// of each character.
void preOrder(Node* root, vector<string> &ans, string curr) {
    if (root == nullptr) return;

    // Leaf node represents a character.
    if (root->left == nullptr && root->right == nullptr) {
        // single character case
        if (curr == "") curr = "0"; 
        ans.push_back(curr);
        return;
    }

    preOrder(root->left, ans, curr + '0');
    preOrder(root->right, ans, curr + '1');
}

vector<string> huffmanCodes(string &s, vector<int> freq) {
    int n = s.length();
    
    // Min heap for Node struct.
    priority_queue<Node*, vector<Node*>, Compare> pq;
    for (int i = 0; i < n; i++) {
        // include index
        Node* tmp = new Node(freq[i], i); 
        pq.push(tmp);
    }

    // single character
    if (n == 1)
        return {"0"};

    // Construct Huffman tree.
    while (pq.size() >= 2) {
        // Left node
        Node* l = pq.top();
        pq.pop();
        
        // Right node
        Node* r = pq.top();
        pq.pop();
            
        // internal node with freq + index   
        Node* newNode = new Node(l, r); 
        pq.push(newNode);
    }

    Node* root = pq.top();
    vector<string> ans;
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