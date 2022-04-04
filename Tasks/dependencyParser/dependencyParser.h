#ifndef _DEPENDENCY_PARSER_H_
#define _DEPENDENCY_PARSER_H_
#include <string>
#include <vector>
#include "document.h"

enum States
{
    noCommentLine = 0,
    multiLineComment
};

class DependencyParser
{
    unsigned short int currentState = States::noCommentLine;
    
    // Группа документов (состоящая из заголовочных файлов) полученная после парсинга файла с исходным кодом
    DocumentsGroup includeDocuments;
    
    // Документ, над которым происходит парсинг
    Document* currDocument;

    bool isCommentLine(std::string str);
    bool isIncludeLine(std::string str);

    void parse(std::string sourcePath);

    public:
    DependencyParser();
    DependencyParser(Document* file);


    inline DocumentsGroup getDocumentsGroup() const
    {
        return includeDocuments;
    }

    void printAllIncludes()
    {
        for(auto& e : *includeDocuments.get())
        {
            std::cout << e.getName() << std::endl;
        }
    }
};

#endif