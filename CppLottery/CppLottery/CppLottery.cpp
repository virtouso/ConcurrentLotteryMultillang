#include <iostream>


#include "algos/MultiThread.h"
#include "algos/SingleThread.h"


void Single()
{
    auto single = SingleThread();
    single.ReadExcel("D://lottery.xlsx");
    single.MakePlainUsers();
    single.RunLottery(200);
}



void Multi()
{
    auto single = MultiThread();
    single.ReadExcel("D://lottery.xlsx");
    single.MakePlainUsers();
    single.RunLottery(200);
}


int main(int argc, char* argv[])
{
    
    return 0;
}
