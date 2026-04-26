#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <string>

class FileHandler {
public:
    static void saveTransactionHistory(const std::string& log);
};

#endif