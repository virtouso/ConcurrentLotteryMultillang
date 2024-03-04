#include "SingleThread.h"
#include <xlnt/xlnt.hpp>
#include <vector>
#include <random>
#include "../helpers/VectorHelpers.h"


void SingleThread::ReadExcel(std::string path)
{
    xlnt::workbook wb;
    wb.load(path);
    auto ws = wb.active_sheet();


    users_ = std::vector<user>();
    for (auto row : ws.rows(false))
    {
        try
        {
            std::string name;
            std::string number;
            int chance = 0;
            int counter = 0;
            for (auto cell : row)
            {
                if (counter == 0)
                {
                    name = cell.to_string();
                }
                else if (counter == 1)
                {
                    number = cell.to_string();
                }
                else if (counter == 2)
                {
                    chance = std::stoi(cell.to_string());
                }


                counter++;
            }
            user u = {name, number, chance};

            users_.emplace_back(u);
        }
        catch (_exception e)
        {
            std::cout << e.arg1;
        }
    }
}

void SingleThread::MakePlainUsers()
{
    plain_users_ = std::vector<user>();

    for (auto element : users_)
    {
        for (int i = 0; i < element.chance; i++)
        {
            plain_users_.emplace_back(element);
        }
    }
}

void SingleThread::RunLottery(int winners_count)
{
    Winners = std::vector<user>();
    std::random_device rd;
    std::mt19937 gen(rd());


    std::uniform_int_distribution<> dis(0, plain_users_.size());
    while (Winners.size() < winners_count)
    {
        int random_number = dis(gen);
        auto exist = propertyExists(Winners, &user::phone_number, plain_users_[random_number].phone_number);

        if (!exist)
        {
            Winners.emplace_back(plain_users_[random_number]);
        }
    }
}
