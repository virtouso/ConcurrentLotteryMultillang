#pragma once
#include <string>
#include <vector>

#include "../models/user.h"

class SingleThread
{
private:
    std::vector<user> users_;
    std::vector<user> plain_users_;
   
    
public:
    std::vector<user> Winners;
    void ReadExcel(std::string path);
    void MakePlainUsers();
    void RunLottery(int winners_count);
};
