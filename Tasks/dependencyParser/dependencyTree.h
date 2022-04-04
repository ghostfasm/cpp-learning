#ifndef _DEPENDENCYTREE_H_
#define _DEPENDENCYTREE_H_
#include <string>
#include <vector>
#include <fstream>
#include "dependencyParser.h"
#include "document.h"

struct Node
{
    DocumentsGroup file;
    Node* child = nullptr;

    Node(DocumentsGroup file)
    {
        this->file = file;
    }
};

class DependencyTree
{
    // Все заголовочные файлы из указанных катологов, где будет проверяться находится ли там .h файл или нет
    std::vector<DocumentsGroup>* headerFiles = nullptr;
    
    // .cpp файл (который является корнем дерева)
    Document * sourceFile = nullptr;

    // Корень дерева
    Node * root = nullptr;
    
    // Вектор документов (дерево зависимостей)
    void fill(Node * node);

    public:
    DependencyTree();
    DependencyTree(Document* sourceFile,  std::vector<DocumentsGroup>* includeFilesInDirectories);
    
    void addNode(DocumentsGroup value);
    void print(std::string histogramLevelDisplay = "");
    void print(Node * node, std::string histogramLevelDisplay);

    void start();

};

#endif 