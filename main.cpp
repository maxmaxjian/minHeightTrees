#include <iostream>
#include <vector>
#include <memory>
#include <functional>

using namespace std;

class Treenode {
  public:
    int val;
    vector<shared_ptr<Treenode>> children;

    Treenode(int a_val) : val(a_val) {}

    void print() {
        cout << "val = " << val;
        if (!children.empty()) {
            cout << ",\t children = ";
            for (auto ptr : children)
                cout << ptr->val << " ";
            cout << endl;
            for (auto child : children)
                child->print();
        }
        else
            cout << ",\t children = null" << endl;
    }
    
};

class solution {
  public:
    vector<int> findMinHeightTrees(int n, const vector<pair<int,int>> & edges) {
        vector<shared_ptr<Treenode>> trees;
        for (int i = 0; i < n; ++i) {
            auto root = buildTreeRooted(i, edges);
            trees.push_back(root);
        }

        int idx = 0;
        for (int i = idx+1; i < n; i++)
            if (height(trees[i]) < height(trees[idx]))
                idx = i;

        // cout << "One of the minimum height trees is:\n";
        // trees[idx]->print();

        vector<int> rtn;
        for (size_t i = 0; i < trees.size(); i++)
            if (height(trees[i]) == height(trees[idx])) {
                cout << "One of the minimum height trees is:\n";
                trees[i]->print();
                rtn.push_back(trees[i]->val);
            }

        return rtn;
    }

  private:
    shared_ptr<Treenode> buildTreeRooted(int root_val, const vector<pair<int,int>> & edges) {
        auto copy = edges;
        auto root = make_shared<Treenode>(root_val);
        if (!edges.empty()) {
            vector<size_t> toRemove;
            for (size_t i = 0; i < edges.size(); i++) {
                if (edges[i].first == root_val || edges[i].second == root_val)
                    toRemove.push_back(i);
            }

            if (!toRemove.empty()) {
                for (int i = toRemove.size()-1; i >= 0; i--)
                    copy.erase(copy.begin()+toRemove[i]);

                for (size_t i = 0; i < toRemove.size(); i++) {
                    int child_val = root->val == edges[toRemove[i]].first ? edges[toRemove[i]].second : edges[toRemove[i]].first;
                    root->children.push_back(buildTreeRooted(child_val, copy));
                }
            }
        }
        return root;
    }

    
    int height(const shared_ptr<Treenode> & root) {
        int h = 0;
        if (root != nullptr) {
            if (root->children.empty())
                h = 0;
            else {
                vector<int> hts;
                for (size_t i = 0; i < root->children.size(); i++)
                    hts.push_back(height(root->children[i]));
                size_t idx = 0;
                for (size_t i = idx+1; i < hts.size(); i++)
                    if (hts[i] > hts[idx])
                        idx = i;
                h = hts[idx]+1;
            }
            
        }
        return h;
    }
};


int main() {
    int n = 4;
    vector<pair<int,int>> edges;
    edges.push_back(make_pair(1,0));
    edges.push_back(make_pair(1,2));
    edges.push_back(make_pair(1,3));

    // int n = 6;
    // vector<pair<int,int>> edges;
    // edges.push_back(make_pair(0,3));
    // edges.push_back(make_pair(1,3));
    // edges.push_back(make_pair(2,3));
    // edges.push_back(make_pair(4,3));
    // edges.push_back(make_pair(5,4));

    solution soln;
    auto rootVals = soln.findMinHeightTrees(n, edges);

    cout << "All the roots of trees with minimum height are:" << endl;
    for (auto i : rootVals)
        cout << i << " ";
    cout << endl;

    return 0;
}
