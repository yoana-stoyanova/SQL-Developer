#ifndef APP_H
#define APP_H

#include <string>
#include "../database/Database.h"

class App {
private:
    Database db;
    std::string currFile;
    bool isFileOpened;

    std::string getNextArg(const std::string& cmd, int& pos);
    void executeCommand(const std::string& fullCommand);

public:
    App();
    void run();

    void openFile(const std::string& fileName);
    void closeFile();
    void save();
    void saveAs(const std::string& fileName);
    void help() const;
};

#endif