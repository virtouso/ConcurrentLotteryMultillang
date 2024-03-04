#include "MultiThread.h"
#include <xlnt/xlnt.hpp>
#include <vector>
#include <random>
#include <algorithm>
#include <execution>

#include "../helpers/VectorHelpers.h"

void MultiThread::ReadExcel(std::string path)
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

void MultiThread::MakePlainUsers()
{
    plain_users_ = std::vector<user>();
    std::mutex mtx;
    std::for_each(std::execution::par, users_.begin(), users_.end(), [&](user& user_data)
    {
        for (int i = 0; i < user_data.chance; ++i)
        {
            mtx.lock();
            plain_users_.emplace_back(user_data);
            mtx.unlock();
        }
    });
}

void MultiThread::RunLottery(int winners_count)
{
    Winners = std::vector<user>();
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> dis(0, plain_users_.size() - 1);
    std::mutex mtx;

  
    std::vector<std::thread> threads;

    for (int i = 0; i < winners_count; ++i)
    {
    
        threads.emplace_back([&]
        {
            int random_number;
            bool exist = false;

            
            do
            {
                random_number = dis(gen);

                std::lock_guard<std::mutex> lock(mtx);
                exist = propertyExists(Winners, &user::phone_number, plain_users_[random_number].phone_number);

                if (!exist)
                {
                    Winners.emplace_back(plain_users_[random_number]);
                }
            } while (exist);
        });
    }


    for (auto& thread : threads)
    {
        thread.join();
    }
}
