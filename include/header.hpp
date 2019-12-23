// Copyright 2018 Your Name <your_email>

#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_
#include <iostream>
#include <boost/filesystem.hpp>
#include <vector>
#include <string>

#define DIRECTORY 3
#define COM_FILE 2

using boost::filesystem::path;

using std::cout;
using std::endl;
using std::vector;
using std::stoi;

using boost::filesystem::directory_iterator;

class analizator {
public:
    void print_first()
    {
        for (unsigned it = 0; it < broker_map.size(); ++it)
        {
            cout << broker_map[it][0] << " balance_" << broker_map[it][1] <<
                 "_" << broker_map[it][2];
            cout << endl;
        }
    }

    bool checkFile(const path file_n)
    {
        std::string fileName = file_n.c_str();

        if (fileName.find(".old") != fileName.npos){
            return false;
        }
        if (file_n.extension() != ".txt"){
            return 0;
        }

        if (!fileName.find(balance)) {
            return false;
        }
            if (fileName.find(spacer) == 7) {
                for (int i = 8; i < 16; i++) {
                    if (!checkNumber(fileName.at(i))) {
                        return false;
                    }
                }
                if (fileName.find(spacer, fileName.find(spacer) + 1) == 16) {
                    for (int i = 17; i < 25; i++) {
                        if (!checkNumber(fileName.at(i))) {
                            return false;
                        }
                    }
                    return true;
                }
            }
            return false;
    }

    void dataBase(path _path) {
        std::string __path = _path.filename().c_str();
        std::string __parent_name = _path.parent_path().filename().c_str();
        vector<std::string> tmp;
        tmp.push_back(__parent_name);
        tmp.push_back(__path.substr(8, 8));
        tmp.push_back(__path.substr(17, 8));
        broker_map.push_back(tmp);
    }

    void print_second()
    {
        for (unsigned i = 0; i < clear_map.size(); ++i)
            cout << "broker:" << clear_map[i][0] <<
                 " account:" << clear_map[i][1] <<
                 " files:" << clear_map[i][2] <<
                 " lastdate:" << clear_map[i][3]
                 << endl;
    }

    void create_clear()
    {
        for (unsigned it = 0; it < broker_map.size(); it++)
        {
            unsigned j = 0;
            int flag = 0;
            for (; j < clear_map.size(); ++j)
            {
                if ((broker_map[it][0] == clear_map[j][0]) &&
                    (broker_map[it][1] == clear_map[j][1])) {
                    flag = 1;
                    int tmp = stoi(clear_map[j][2]);
                    tmp++;
                    clear_map[j][2] = std::to_string(tmp);
                    if (stoi(broker_map[it][20]) > stoi(clear_map[j][3])) {
                        clear_map[j][3] = broker_map[it][2];
                    }
                }
            }
            if (flag == 0) {
                vector<std::string> tmp;
                tmp.push_back(broker_map[it][0]);
                tmp.push_back(broker_map[it][1]);
                tmp.push_back("1");
                tmp.push_back(broker_map[it][2]);
                clear_map.push_back(tmp);
            }
        }
    }

    void start(path currentDir)
    {
        getInfo(currentDir);
        print_first();

        create_clear();
        print_second();
    }


    void getInfo(path currentDir)
    {
        for (directory_iterator p(currentDir), end; p != end; p++) {
            if (p->status().type() == DIRECTORY) {
                getInfo(p->path());
            }
            if (p->status().type() == COM_FILE) {
                if (checkFile(p->path().filename()) == true)
                {
                    dataBase(p->path());
                }
            }
        }
    }

    int number_of(std::string broker, int64_t ttf)
    {
        for (unsigned i = 0; i < clear_map.size(); ++i){
            if ((clear_map[i][0] == broker) && (stoi(clear_map[i][1]) == ttf))
            {
                return std::stoi(clear_map[i][2]);
            }
        }
        return 0;
    }

    bool checkNumber(char str) {
        if ((str >= '0') && (str <= '9'))
        {
            return true;
        } else {
            return false;
        }
    }


    const char* balance = "balance";
    const char* spacer = "_";
    path parent_dir;
    vector<vector<std::string>> clear_map;
    vector<vector<std::string>> broker_map;
};
#endif // INCLUDE_HEADER_HPP_
