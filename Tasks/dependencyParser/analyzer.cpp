#include "analyzer.h"
#include <filesystem>

void Analyzer::start(int& argc, char* argv[])
{
    if (init(argc, argv))
    {
        std::cout << sourcePathDirectory << std::endl;

        namespace fs = std::filesystem;

        // Поиск всех файлов с расширением .cpp
        sourceFilesInDirectory = DocumentsGroup::getInDirectory(sourcePathDirectory, ".cpp");

        // Поиск всех заголовочных файлов .h <...> находящиеся в указанных директориях
        for (int i = 0; i < includePathesDirectories.size(); i++)
        {
            // Удаляем лишние пробелы из строки
            includePathesDirectories[i].erase(remove_if(includePathesDirectories[i].begin(), includePathesDirectories[i].end(), isspace), includePathesDirectories[i].end());

            includeFilesInDirectories.push_back(DocumentsGroup::getInDirectory(includePathesDirectories[i], ".h"));
        }

        // Создание дерева зависимостей
        for (auto e : *sourceFilesInDirectory.get())
        {
            DependencyTree tempTree(&e, &includeFilesInDirectories);
            dependencyTrees.push_back(tempTree);
            dependencyTrees.back().print();
        }
    }  
}

bool Analyzer::init(int & argc, char * argv[])
{
   if (argc == 1)
    {
        std::cout << "Use: " << argv[0] << " <sources path> [options]\n";
        std::cout << "Type --help for more information\n";

        return false;
    }
    
    sourcePathDirectory = std::string(argv[1]);
    namespace opt = boost::program_options;

    // Создаем опции, описывающие переменную, и даем ей текстовое описание
    opt::options_description desc("All options");

    // При добавлении опции, первый параметр - имя. Второй параметр - тип данных опции, заключенный в класс value<>. Третий параметр содержит описание этой опции
    desc.add_options()
        ("help", "produce help message")
        ("include-file,I", opt::value<std::vector<std::string>>(&includePathesDirectories), "path to search for source files")
    ;

    // Переменная для хранения аргументов нашей командной строки
    opt::variables_map vm;

    // Парсинг и сохранение аргументов
    opt::store(opt::parse_command_line(argc, argv, desc), vm);

    try
    {
        // Эта функция должна вызываться после парсинга и сохранения
        opt::notify(vm);
    }
    catch (const opt::required_option& e)
    {
        std::cout << "Error: " << e.what() << "\n";
    }

    if (vm.count("include-path"))
    {
        std::cout << "Include path are: " << vm["include-path"].as<std::string>() << "\n";
    }

    if (vm.count("help"))
    {
        std::cout << argv[0] << " <sources path> [options]" << "\n";
        std::cout << desc << "\n";
        return false;
    }

    return true;
}