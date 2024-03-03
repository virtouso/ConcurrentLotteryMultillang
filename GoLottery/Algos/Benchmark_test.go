package Algos

import (
	"GoLottery/Algos/MultiThread"
	"GoLottery/Algos/SingleThread"
	"fmt"
	"testing"
)

func init() {
	fmt.Println("start init")
}

func BenchmarkSingleThread(b *testing.B) {
	SingleThread.LoadUsersExcel("D://lottery.xlsx")
	SingleThread.MakePlainUsers()
	SingleThread.RunLottery()
}

func BenchmarkMultiThread(b *testing.B) {
	MultiThread.LoadUsersExcel("D://lottery.xlsx")
	MultiThread.MakePlainUsers()
	MultiThread.RunLottery()
}
