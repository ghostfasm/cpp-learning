#include "dependencyParser.h"
#include <fstream>

DependencyParser::DependencyParser(Document* file)
{
    std::string tempS = file->getPathDirectory() + "/" + file->getName();
    std::ifstream in(tempS);
    std::string str;
    currDocument = file;
    while (std::getline(in, str))
    {
        parse(str);
    }

    in.close();
}

void DependencyParser::parse(std::string line)
{
    std::string strNew;
    unsigned first;
    unsigned last;
    size_t found;
    if (!isCommentLine(line) && isIncludeLine(line))
    {
        found = line.find("<");

        if (found == std::string::npos)
        {
            // Необходимо добавить единичку чтобы не отображать лишний символ
            first = line.find('"') + 1;
            last = line.find_last_of('"');
        }
        else
        {
            first = line.find("<") + 1;
            last = line.find(">");
        }

         strNew = line.substr(first,last-first);

        if (!strNew.empty())
        {
            Document tempDoc(strNew, currDocument->getPathDirectory());
            includeDocuments.get()->push_back(tempDoc);
        }
        else
        {
            std::cout << "Parsing error" << std::endl;
        }
    }
}

bool DependencyParser::isIncludeLine(std::string str)
{
    return str.find("#include") != std::string::npos ? true : false;
}

bool DependencyParser::isCommentLine(std::string str)
{
    if (currentState == States::noCommentLine)
    {
        if (str.find("//") != std::string::npos)
        {
            return true;
        }
        else if (str.find("/*") != std::string::npos)
        {
            currentState = States::multiLineComment;
            return true;
        }
    }
    else
    {
        if (str.find("*/") != std::string::npos)
        {
            currentState = States::noCommentLine;
            return true;
        }

        if (currentState != States::noCommentLine)
        {
            return true;
        }
    }

    return false;
}
