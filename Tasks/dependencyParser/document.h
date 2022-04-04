#ifndef _DOCUMENT_H_
#define _DOCUMENT_H_
#include <string>
#include <vector>
#include <iostream>
#include <filesystem>
class DocumentsGroup;

class Document
{
    std::string name;
    std::string pathDirectory;
    std::string extension;
    bool isLocatedInDirectory;

    public:
    Document(std::string fileName = "", std::string filePath = "", std::string fileExtension = "") : name(fileName), pathDirectory(filePath), extension(fileExtension)
    {
        isLocatedInDirectory = true;
    }
    inline std::string getName() const
    {
        return this->name;
    }
    inline std::string getExtension() const
    {
        return this->extension;
    }
    inline std::string getPathDirectory() const
    {
        return pathDirectory;
    }
    inline void setName(std::string name)
    {
        this->name = name;
    }
    inline void getExtension(std::string extension)
    {
        this->extension = extension;
    }
    inline void getPathDirectory(std::string pathDirectory)
    {
        this->pathDirectory = pathDirectory;
    }
};

class DocumentsGroup
{
    std::vector<Document> documents;

    inline int getSize() const
    {
        return documents.size();
    }

    public:
    DocumentsGroup();
    DocumentsGroup(std::vector<Document> value);
    std::vector<Document>* get();
    int getCountOfDocuments() const
    {
        return documents.size();
    }
    
    // рекурсивный поиск документов в определенной директории с определенным расширением
    static DocumentsGroup getInDirectory(std::string dir, std::string extension)
    {
        DocumentsGroup result;
        namespace fs = std::filesystem;

        try
        {
            for (fs::recursive_directory_iterator e(dir), end; e != end; ++e) 
            {
                if (!is_directory(e->path()))
                {
                    if (e->path().extension() == extension)
                    {
                        Document d(e->path().filename(), dir, extension);
                        result.documents.push_back(d);
                    }
                }
            }

        } catch (const std::exception& e) {
            std::cout << e.what() << "\n";
        }
        
        return result;

    }
    void print();
};

#endif