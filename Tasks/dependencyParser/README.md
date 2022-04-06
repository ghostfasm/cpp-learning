## dependencyTree library



### Постановка задачи

Нужно написать анализатор файлов исходного кода на С++. Программа должна выводить дерево
зависимостей и частоты включений файлов. Если найдены включения несуществующих файлов, то
программа должна вывести пометку «(!)» после имени файла.
В директории с исходными кодами могут быть вложенные папки (то есть обход должен
производиться рекурсивно). Файлы имеют расширения &quot;.h&quot; и &quot;.cpp&quot;

## Идея реализации
Обработка ввода осуществляется с помощью библиотеки Boost и компонента ProgramOptions. С помощью удобной библиотеки получилось добиться идентичного шаблона обработки командной строки.

Реализация основной части описана в методе ```Analyzer::start(int argc, char* argv[])```. В случае запуска программ без передачи параметров - появляется подсказка. После окончания инициализации основных элементов (после выполнения метода ```Analyzer::init(int argc, char * argv[])```, в дело идет заполнение векторов с директориями. В статическом методе ```static DocumentsGroup getInDirectory(std::string dir, std::string extension)```
(использовались возможности C++17 и ``<filesystem.h>`` описан рекурсивный (в будущем планируется от него отказаться) отбор документов в директории (и поддерикториях), которые удовлетворя-
ют определенному расширению.

Для хранения документов и группы документов использовались соответствующие классы - ```Document``` и ```DocumentsGroup```.

Дерево зависимостей представляет собой N-Tree, где у родителя может быть несколько детей (один документ может зависеть от нескольких до-
кументов). Для упрощения каждый узел состоит из ```DocumentsGroup```, в котором может быть неопределенное заранее колличество документов. Рекур-
сивное создание дерева зависимостей описан в методе ```void DependencyTree::fill(Node * node).```

Вывод (метод ```void DependencyTree::print(std::string histogramLevelDisplay)```)
дерева зависимостей также использует рекурсию.

#### Важные реализации:
Парсинг отдельной строки текстового документа

```cpp
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
```
#### Рекурсивный поиск файлов в директории и поддиректориях
```cpp
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
```
#### Заполнение дерева зависимостей
```cpp
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
```

#### Вывод дерева зависимости в консольное приложение
```cpp
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
```
## Использование
### Ввод
```bash
./app /tests/1
```
### Вывод
```
main.cpp
..h1.h
....h4.h
......h5.h
..h2.h
....h4.h
......h5.h
..h3.h
....h4.h
......h5.h
s1.cpp
..h1.h
....h4.h
......h5.h
..h2.h
....h4.h
......h5.h
```
