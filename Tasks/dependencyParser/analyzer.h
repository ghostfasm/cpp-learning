#ifndef _ANALYZER_H_
#define _ANALYZER_H_
#include <boost/program_options.hpp>
#include <iostream>
#include <string>
#include <vector>
#include "document.h"
#include "dependencyTree.h"

class Analyzer
{
	// Инициализация всех полей класса
	bool init(int & argc, char** argv);

	// Пути к заголовочным файлам .h <...>
	std::vector<std::string> includePathesDirectories;

	// Путь к папке с исходными файлами .cpp
	std::string sourcePathDirectory;

	// Содержит все доступные исходные файлы .cpp
	DocumentsGroup sourceFilesInDirectory;

	// Cодержит все доступные заголовочные файлы .h
	std::vector<DocumentsGroup> includeFilesInDirectories;

	// Вектор деревьев
	std::vector<DependencyTree> dependencyTrees;
    public:
    Analyzer(){}

	void start(int& argc, char** argv);

};

#endif