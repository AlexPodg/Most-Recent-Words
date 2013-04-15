#include <QCoreApplication>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>

using std::string;
int main(int argc, char *argv[])
{
    typedef std::pair<std::string, int> StringPair;
    typedef std::vector<StringPair> StringArr;
    QCoreApplication a(argc, argv);
    std::ifstream file;
    file.open("phrase.txt");
    if (!file.is_open())
    {
        std::cerr << "Can't open file";
        return 0;
    }
    string sPhrase;
    std::getline(file, sPhrase);
    if (!sPhrase.empty())
    {
        //main algo
        string Delimiters(" ,;?!.");
        StringArr aFoundWords;
        size_t pos(0);
        size_t prevpos(0);

        pos = sPhrase.find_first_of(Delimiters, prevpos);
        string sWord (sPhrase.substr(prevpos, pos-prevpos));
        prevpos = pos+1;
        aFoundWords.push_back(StringPair(sWord, 1));
        do {
            pos = sPhrase.find_first_of(Delimiters, prevpos);
            sWord.clear();
            sWord = sPhrase.substr(prevpos, pos-prevpos);
            prevpos = pos+1;
            bool notfound(true);
            // Can't use iterators because vector is modified inside the cycle
            for (int i = 0; i<aFoundWords.size() && notfound; i++)
            {
                string Tempstring(aFoundWords[i].first);
                if (Tempstring == sWord){
                    (aFoundWords[i].second)++;
                    notfound = false;
                }
            }
            if (notfound)
                aFoundWords.push_back(StringPair(sWord, 1));
        }while(pos!=sPhrase.size()-1);
        StringArr::iterator it;
        for (it=aFoundWords.begin(); it!=aFoundWords.end(); it++)
            std::cout << (*it).first << " " << (*it).second << std::endl;
    }
    else
    {
        std::cerr << "String is empty";
        return 0;
    }

    return a.exec();
}

