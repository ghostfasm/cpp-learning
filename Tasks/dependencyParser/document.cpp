#include "document.h"

void DocumentsGroup::print()
{
    for(auto& e : documents)
    {
        std::cout <<  e.getName() << std::endl;
    }  
}

std::vector<Document>* DocumentsGroup::get()
{
    return &documents;
}

 DocumentsGroup::DocumentsGroup()
 {

 }

 DocumentsGroup::DocumentsGroup(std::vector<Document> value) : documents(value)
 {
     
 }