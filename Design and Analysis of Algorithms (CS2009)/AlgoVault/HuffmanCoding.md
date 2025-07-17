> # Huffman Coding

## Description
- Huffman Coding is a **lossless data compression algorithm**.
- Frequencies of characters are used to build a **binary tree**.
- The **least frequent characters** are deeper in the tree.
- Left edge represents `0`, right edge represents `1`.
- Traversing from root to leaf gives the **Huffman code** for each character.

## Steps
1. Count the frequency of each character.
2. Insert all characters into a **min heap** based on frequency.
3. Extract two nodes with the smallest frequency.
4. Merge them into a new internal node (frequency = sum of both).
5. Repeat until there is only **one node** left — the root.
6. Traverse the tree to assign binary codes to each character.

## Time Complexity
- **Building frequency map**: O(n)
- **Heap operations**: O(d log d), where `d` is number of distinct characters
- **Total**: O(n + d log d)

---

## C++ Implementation
```cpp
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

struct Node
{
    char symbol;
    int frequency;
    Node* left;
    Node* right;

    Node(char sym, int freq, Node* l = nullptr, Node* r = nullptr)
        : symbol(sym), frequency(freq), left(l), right(r)
    {
    }
};

class MinHeap
{
   private:
    vector<Node*> heap;

    void swap(int i, int j)
    {
        Node* temp = heap[i];
        heap[i] = heap[j];
        heap[j] = temp;
    }

    void heapifyUp(int index)
    {
        if (index == 0) return;

        int parent = (index - 1) / 2;
        if (heap[index]->frequency < heap[parent]->frequency)
        {
            swap(index, parent);
            heapifyUp(parent);
        }
    }

    void heapifyDown(int index)
    {
        int smallest = index;
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int size = heap.size();

        if (left < size && heap[left]->frequency < heap[smallest]->frequency)
            smallest = left;

        if (right < size && heap[right]->frequency < heap[smallest]->frequency)
            smallest = right;

        if (smallest != index)
        {
            swap(smallest, index);
            heapifyDown(smallest);
        }
    }

   public:
    MinHeap() {}

    void insert(Node* node)
    {
        heap.push_back(node);
        heapifyUp(heap.size() - 1);
    }

    Node* extractMin()
    {
        if (heap.empty()) return nullptr;

        Node* min = heap[0];
        heap[0] = heap.back();
        heap.pop_back();

        if (!heap.empty()) heapifyDown(0);

        return min;
    }

    int size() const { return heap.size(); }

    bool empty() const { return heap.empty(); }
};

Node* buildHuffmanTree(vector<pair<char, int>>& character_frequencies)
{
    MinHeap heap;

    for (pair<char, int> pair : character_frequencies)
        heap.insert(new Node(pair.first, pair.second));

    while (heap.size() > 1)
    {
        Node* left = heap.extractMin();
        Node* right = heap.extractMin();

        int sum_frequency = left->frequency + right->frequency;
        Node* merged = new Node('\0', sum_frequency, left, right);
        heap.insert(merged);
    }

    return heap.extractMin();
}

void generateCodes(Node* root, string code,
                   unordered_map<char, string>& huffman_codes)
{
    if (!root) return;

    if (!root->left && !root->right) huffman_codes[root->symbol] = code;

    generateCodes(root->left, code + "0", huffman_codes);
    generateCodes(root->right, code + "1", huffman_codes);
}

int main()
{
    vector<pair<char, int>> character_frequencies = {{'a', 5},
                                                     {'b', 9},
                                                     {'c', 12},
                                                     {'d', 13},
                                                     {'e', 16},
                                                     {'f', 45}};

    Node* root = buildHuffmanTree(character_frequencies);
    unordered_map<char, string> huffman_codes;
    generateCodes(root, "", huffman_codes);

    cout << "Huffman Codes:\n";
    for (auto& p : huffman_codes)
    {
        cout << p.first << ": " << p.second << "\n";
    }
}
```

---

## Example Tree Structure (ASCII Diagram)
```
          (*,100)
         /      \
     (*,55)    f:45
     /    \
  (*,25)  e:30
  /    \
 a:5   (*,20)
       /     \
    b:9     (*,11)
           /     \
        c:12    d:13
```
(Note: Characters on leaves, * represents internal merged nodes)

## Huffman Code Example Output
```
a: 1100
b: 1101
c: 100
d: 101
e: 111
f: 0
```

Characters with **higher frequency** have **shorter codes**, which is the key idea behind Huffman compression.

