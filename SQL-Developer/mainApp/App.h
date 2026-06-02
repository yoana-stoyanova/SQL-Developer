#ifndef APP_H
#define APP_H

#include <string>
#include "../database/Database.h"

class App {
private:
    Database db;
    void executeCommand(const std::string& fullCommand);

public:
    App();
    void run();
    void save();
    void help() const;
};

#endif