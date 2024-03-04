#include <iostream>

#include "algos/MultiThread.h"
#include "algos/SingleThread.h"

int main(int argc, char* argv[])
{
    auto single = MultiThread();
    single.ReadExcel("D://lottery.xlsx");
    single.MakePlainUsers();
    single.RunLottery(200);
    std::cout << single.Winners.size();
    return 0;
}
