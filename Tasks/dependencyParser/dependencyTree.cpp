#include "dependencyTree.h"
#include <fstream>
#include <sstream>
#include <string>

DependencyTree::DependencyTree(Document* sourceFile,  std::vector<DocumentsGroup>* includeFilesInDirectories)
{

    this->sourceFile = sourceFile;
    headerFiles = includeFilesInDirectories;

    if (root == nullptr)
    {
        DocumentsGroup temp;
        temp.get()->push_back(*sourceFile);
        root = new Node(temp);
    }

    fill(root);
}

void DependencyTree::fill(Node * node)
 {
     for (auto e : *node->file.get())
     {
        DependencyParser dp(&e);
        if (dp.getDocumentsGroup().getCountOfDocuments() == 0)
            continue;
        
        node->child = new Node(dp.getDocumentsGroup());
        fill(node->child);
     }
 }

void DependencyTree::print(std::string histogramLevelDisplay)
{
     for (auto e : *root->file.get())
     {
        std::cout << histogramLevelDisplay << e.getName() << std::endl;
        if (root->child == nullptr)
            continue;

        print(root->child, histogramLevelDisplay + "..");
     }
}

void DependencyTree::print(Node * node, std::string histogramLevelDisplay = "")
{
     for (auto e : *node->file.get())
     {
        std::cout << histogramLevelDisplay << e.getName() << std::endl;
        if (node->child == nullptr)
            continue;
        print(node->child, histogramLevelDisplay + "..");
     }
}
