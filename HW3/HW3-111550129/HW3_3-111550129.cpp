#include <iostream>
#include <vector>
using namespace std;

class TreeNode {
    public:
    int key;
    int height; // Store the height of the subtree rooted at this node
    TreeNode* parent;
    vector<TreeNode*> children;

    TreeNode(int key) : key(key), height(-1), parent(nullptr) {}
};

class Tree {
    private:
    vector<TreeNode*> nodes;
    vector<vector<int>> adjList;

    void depthFirstSearch(int nodeKey, TreeNode* parentNode) {
        TreeNode* node = nodes[nodeKey];
        node->parent = parentNode;

        for (int childKey : adjList[nodeKey]) {
            if (!parentNode || childKey != parentNode->key) {
                TreeNode* childNode = nodes[childKey];
                node->children.push_back(childNode);
                depthFirstSearch(childKey, node);
            }
        }
    }

    int calculateHeight(TreeNode* node) {
        if (node->height != -1) {
            return node->height; // If height is already calculated, return it
        }

        if (node->children.empty()) {
            node->height = 0; // Leaf node
            return 0;
        }

        int maxHeight = 0;
        for (TreeNode* child : node->children) {
            int childHeight = calculateHeight(child);
            maxHeight = max(maxHeight, childHeight);
        }

        node->height = maxHeight + 1;
        return node->height;
    }

    public:
    Tree(int n) {
        nodes.resize(n + 1, nullptr);
        adjList.resize(n + 1);
        for (int i = 1; i <= n; ++i) {
            nodes[i] = new TreeNode(i);
        }
    }

    void addEdge(int u, int v) {
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    void buildAndPrintTree() {
        depthFirstSearch(1, nullptr);
        calculateHeight(nodes[1]); // Calculate heights starting from the root

        for (int i = 1; i < nodes.size(); i++) {
            int parentKey = nodes[i]->parent ? nodes[i]->parent->key : -1;
            cout << nodes[i]->height << " " << parentKey << endl;
        }
    }
};

int main() {
    ios::sync_with_stdio(false); // These two lines may help reduce I/O time
    cin.tie(0);

    int n;
    cin >> n;
    Tree tree(n);

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        tree.addEdge(u, v);
    }

    tree.buildAndPrintTree();
    return 0;
}
