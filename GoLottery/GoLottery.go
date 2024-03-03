package main

import (
	"GoLottery/Algos/MultiThread"
)

func main() {
	println("just a test")
	MultiThread.LoadUsersExcel("D://lottery.xlsx")
	MultiThread.MakePlainUsers()
	result := MultiThread.RunLottery()

	for _, value := range result {

		println(value.PhoneNumber)

	}

}
