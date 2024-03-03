package MultiThread

import (
	"GoLottery/Models"
	"fmt"
	"github.com/tealeg/xlsx"
	"log"
	"math/rand"
	"strconv"
	"time"
)

var users []Models.User
var plainUsers []Models.User

func LoadUsersExcel(dir string) {

	xlFile, err := xlsx.OpenFile(dir)
	if err != nil {
		log.Fatalf("Error opening file: %v", err)
	}

	users = make([]Models.User, 0, len(xlFile.Sheets[0].Rows))

	for _, sheet := range xlFile.Sheets {
		fmt.Printf("Sheet Name: %s\n", sheet.Name)

		for _, row := range sheet.Rows {

			go func() {

				counter := 0
				name := ""
				number := ""
				var chance int64 = 0
				for _, cell := range row.Cells {

					value, err := cell.FormattedValue()
					if err != nil {
						log.Printf("Error getting value from cell: %v", err)
						continue
					}

					if counter == 0 {
						name = value
					} else if counter == 1 {
						number = value
					} else {
						chance, _ = strconv.ParseInt(value, 10, 64)
					}

					counter++

				}

				users = append(users, Models.User{
					Name:        name,
					PhoneNumber: number,
					Chance:      chance,
				})

			}()

		}
	}
}

func MakePlainUsers() {

	plainUsers = make([]Models.User, 0, len(users))
	for _, value := range users {

		var i int64 = 0
		for i = 0; i < value.Chance; i++ {
			plainUsers = append(plainUsers, value)
		}

	}
}

func RunLottery() []Models.User {

	var count int = 1000
	winners := make([]Models.User, 0, count)

	rand.Seed(time.Now().UnixNano())

	for len(winners) < count {

		go func() {
			random := rand.Intn(len(plainUsers))

			if !containsNumber(winners, plainUsers[random].PhoneNumber) {
				winners = append(winners, plainUsers[random])
			}
		}()
	}

	return winners
}

func containsNumber(people []Models.User, number string) bool {
	for _, p := range people {
		
		if p.PhoneNumber == number {
			return true
		}
	}
	return false
}
