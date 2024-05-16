#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

class TreeNode {
private:
    bool type;  // true - "ИЛИ" вершина, false - "И" вершина
    std::string name;
    int mass = 0;
    int minMass = 0;
    int maxMass = 0;
    std::vector<TreeNode*> children;

public:
    TreeNode(bool nodeType, const std::string& nodeName, int nodeMass)
            : type(nodeType), name(nodeName), mass(nodeMass) {}

    // Метод для добавления потомка
    void addChild(TreeNode* child) {
        children.push_back(child);
    }

    void setMassChildren() {
        if (!this->children.empty()) {
            if (!this->type) {
                this->maxMass = this->children[0]->getMaxMass() + this->children[0]->getMass();
                this->minMass = this->children[0]->getMinMass() + this->children[0]->getMass();
            }
            for (int i = 0; i != this->children.size(); i++) {
                if (!this->type) {
                    if ((this->children[i]->getMaxMass() + this->children[i]->getMass()) > this->maxMass) {
                        this->maxMass = this->children[i]->getMaxMass() + this->children[i]->getMass();
                    }

                    if ((this->children[i]->getMinMass() + this->children[i]->getMass()) < this->minMass){
                        this->minMass = this->children[i]->getMinMass() + this->children[i]->getMass();
                    }
                } else {
                    this->maxMass = this->children[i]->getMaxMass() + this->children[i]->getMass() + this->maxMass;
                    this->minMass = this->children[i]->getMinMass() + this->children[i]->getMass() + this->minMass;
                }
            }
        }
    }

    int getMaxMass() {
        return this->maxMass;
    }

    int getMass() {
        return this->mass;
    }


    int getMinMass() {
        return this->minMass;
    }

    bool getType() {
        return this->type;
    }

    void writeParam() {
        std::cout << this->name << ' ' << this->mass << ' '  << this->minMass << ' '  << this->maxMass << std::endl;
    }

    std::vector<TreeNode*> getChildren() {
        return this->children;
    }
};

class Tree {
private:
    TreeNode* root;
    TreeNode* currentNode;
    int MinMass;
    int MaxMass = 18;
    int currentLevel = 0;
    std::vector<TreeNode*> prevNode;
public:
    Tree() : root(nullptr) {}

    TreeNode* getRoot() {
        return this->root;
    };

    int getMaxTreeMass() {
        return this->MaxMass;
    };

    void insert(bool nodeType, const std::string& nodeName, int nodeMass, int nodeLevel) {
        TreeNode* newNode = new TreeNode(nodeType, nodeName, nodeMass);

        if (root == nullptr) {
            root = newNode;
            currentNode = root;
            return;
        }

        if (nodeLevel - currentLevel == 1) {
            currentNode->addChild(newNode);
            return;
        }

        if (nodeLevel - currentLevel == 2) {
            std::vector<TreeNode*> child = currentNode->getChildren();

            if (child.empty()) {
                std::cerr << "Wrong tree in file" << std::endl;
            }

            prevNode.push_back(currentNode);
            currentNode = child.back();
            currentNode->addChild(newNode);
            currentLevel++;
            return;
        }

        if (nodeLevel - currentLevel < 1) {
            while (nodeLevel - currentLevel < 1) {
                currentNode = prevNode.back();
                prevNode.pop_back();
                currentLevel = currentLevel - 1;
            }
            currentNode->addChild(newNode);
            return;
        }
        std::cerr << "Wrong tree in file2"  << std::endl;

    }

    void Print(TreeNode* Tree, int l){
        std::vector<TreeNode*> children = Tree->getChildren();
        for (int i = 0; i != l; i++) {
            std::cout << ' ';
        }
        Tree->writeParam();
        if (!children.empty()) {
            for (int i = 0; i != children.size(); i++) {
                Print(children[i], l + 1);
            }
        }
    }

     void printAndDeleteTree(TreeNode* treeNode) {
        treeNode->writeParam();

        std::vector<TreeNode*> children = treeNode->getChildren();

        if (!children.empty()) {
            for (int i = 0; i != children.size(); i++) {
                if (children[i] != nullptr) {
                    printAndDeleteTree(children[i]);
                }
            }
        }
         treeNode = nullptr;
          delete treeNode;
    }

    void deleteTree(TreeNode* treeNode) {
        std::vector<TreeNode*> children = treeNode->getChildren();

        if (!children.empty()) {
            for (int i = 0; i != children.size(); i++) {
                if (children[i] != nullptr) {
                    printAndDeleteTree(children[i]);
                }
            }
        }
        treeNode = nullptr;
        delete treeNode;
    }

    void setMass(TreeNode* treeNode) {
        std::vector<TreeNode*> children = treeNode->getChildren();

        if (!children.empty()) {
            for (int i = 0; i != children.size(); i++) {
                setMass(children[i]);
            }
        }
        treeNode->setMassChildren();
    }

    void setMinMass(TreeNode* treeNode) {
        this->MinMass = treeNode->getMinMass() + treeNode->getMass();
    }

    void setMaxMass(int& Mass) {
        this->MaxMass = Mass;
    }

    void destroyNode(TreeNode* treeNode, int& maxMass) {
        if (treeNode->getMinMass() + treeNode->getMass() > maxMass) {
            printAndDeleteTree(treeNode);
            return;
        } else if (treeNode->getMaxMass() + treeNode->getMass() >= maxMass) {
            std::vector<TreeNode*> children = treeNode->getChildren();
            if (!children.empty()) {
                if (treeNode->getType()) {
                    for (int i = 0; i != children.size(); i++) {
                        int mass = maxMass - treeNode->getMinMass() + children[i]->getMass();
                        destroyNode(children[i], mass);
                    }
                } else {
                    for (int i = 0; i != children.size(); i++) {
                        int mass = maxMass - treeNode->getMass();
                        destroyNode(children[i], mass);
                    }
                }
            }
        }
    }

   void truncationNode() {
        destroyNode(this->root, this->MaxMass);
   }
};

void readTreeFromFile(const std::string& filename, Tree& tree) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Unable to open the file: " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        char c;
        int mass, level = 0;
        std::string name;
        iss >> name >> mass >> c;

        for (int i = 0; (i = name.find('.', i)) != std::string::npos; i++) {
            level++;
        }

        bool type = (c == '&'); // '&' for "И" (AND), '|' for "ИЛИ" (OR)
        tree.insert(type, name, mass, level);
    }

    file.close();
}

void truncationTree(Tree& tree) {
    tree.truncationNode();
}

void writeAndClearTree(Tree& tree) {
    tree.printAndDeleteTree(tree.getRoot());
}

void InitializateMass(Tree& tree) {
    tree.setMass(tree.getRoot());
    tree.setMinMass(tree.getRoot());
}

void sera(Tree& tree) {
    int mass = tree.getMaxTreeMass();
    tree.destroyNode(tree.getRoot(), mass);
}

int main() {
    Tree tree;

    // Читаем дерево из файла
    readTreeFromFile("wera.txt", tree);
    InitializateMass(tree);
    sera(tree);
    std::cout << '2' << std::endl;
    writeAndClearTree(tree);
    return 0;
};