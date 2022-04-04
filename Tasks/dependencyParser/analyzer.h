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
	// ������������� ���� ����� ������
	bool init(int & argc, char** argv);

	// ���� � ������������ ������ .h <...>
	std::vector<std::string> includePathesDirectories;

	// ���� � ����� � ��������� ������� .cpp
	std::string sourcePathDirectory;

	// �������� ��� ��������� �������� ����� .cpp
	DocumentsGroup sourceFilesInDirectory;

	// C������� ��� ��������� ������������ ����� .h
	std::vector<DocumentsGroup> includeFilesInDirectories;

	// ������ ��������
	std::vector<DependencyTree> dependencyTrees;
    public:
    Analyzer(){}

	void start(int& argc, char** argv);

};

#endif