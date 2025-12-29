#include <iostream>
#include <fstream>



std::string convertIdtoStr(int requestId, std::string str)
{
    //В зависимости от разрядности ID запроса добавить нули
    if ((requestId + 1) / 10 < 1) str.append("00" + std::to_string(++requestId));
    else if ((requestId + 1) / 100 < 1) str.append("0" + std::to_string(++requestId));
    else if ((requestId + 1) / 1000 < 1) str.append(std::to_string(++requestId));

    return str;
}

int main()
{
    /*std::ifstream ifs{ "book.txt" };
    if (!ifs) std::cout << "Error!";

    std::ofstream ofs{"book2.txt"};

    char tmp;
    while (ifs.get(tmp))
    {
        tmp = std::tolower(tmp);
        if (tmp < 'a' || tmp > 'z') tmp = ' ';
        ofs.put(tmp);
    }*/

    /*std::fstream ifs{"book2.txt"};

    std::string word;
    int numberOfFile{};

    std::ofstream files{"files"};

    while (true)
    {
        int i{};
        //std::cout << "./resources/" + convertIdtoStr(numberOfFile, "file") + ".txt";
        std::string nameOfFile{"./resources/" + convertIdtoStr(numberOfFile, "file") + ".txt"};
        std::ofstream ofs{nameOfFile};
        files << '"' << nameOfFile << '"' << ',' << '\n';
        while (++i <= 1000)
        {
            if (ifs >> word) ofs << word << ' ';
            else break;
        }

        if (ifs.eof()) break;

        ++numberOfFile;
    }*/


    std::ofstream ofs{"book6.txt"};

    int i{};
    std::string word;

    while (i < 3)
    {
        std::fstream ifs{"book4.txt"};

        while (getline(ifs, word))
        {
            ofs << word;
        }

        ++i;
    }


    return 0;
}
