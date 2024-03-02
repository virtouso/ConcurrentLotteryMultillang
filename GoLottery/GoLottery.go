package main

import "GoLottery/Algos"

func main() {
	println("just a test")
	Algos.LoadUsersExcel("D://lottery.xlsx")
	Algos.MakePlainUsers()
	result := Algos.RunLottery()

	for _, value := range result {

		println(value.PhoneNumber)

	}

}
