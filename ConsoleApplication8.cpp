#include <iostream>
#include <Windows.h>
#include "globals.h"

using namespace std;

void CheckLimitedBet(float& bet, float botBalance)
{
	while (bet > botBalance)
	{
		cout << "Вы не можете поставить больше кредитов чем у Бота-соперника на счету!" << "\nВведите ставку ещё раз." << endl;
		cin >> bet;
	}
}

void CheckMaximumBet(float& bet)
{
	while (bet > 20)
	{
		cout << "Максимальная ставка 20 кредитов" << "\nВведите ставку ещё раз." << endl;
		cin >> bet;
	}
}

void CheckMaximumUserWishValue()
{
	cout << "[!] загадай любое число от 1 до 100" << endl;
	do
	{
		cout << "Введите число от 1 до 100" << endl;
		cin >> enteredUserValue;
	} while (enteredUserValue <= 0 || enteredUserValue >= 101);
}

void DifferenceBet()
{
	if (abs(enteredUserValue - casinoRandomValue) < abs(randomComputerValue - casinoRandomValue))
	{
		botBalance -= bet;
		bet *= 1.9f;
		userBalance += bet;
		cout << "\n[WIN] Поздравляем, вы победили!" << endl;
	}
	else
	{
		userBalance -= bet;
		bet *= 1.9f;
		botBalance += bet;
		cout << "\n[LOSE] К сожалению компьютер оказался ближе к ответу" << endl;
	}
}

void InformationAndInputBet()
{
	cout << "\n[!] Максимальная ставка 20" << endl;
	cout << "[!] На вашем счету " << userBalance << " кредитов" << "\n\nВведите вашу ставку.\nКомпьютер поставит точно такое же число кредитов что и вы!" << endl;

	cin >> bet;
}

void InformationBalance()
{
	cout << "\n[!] Вы ввели: " << enteredUserValue << endl << "Бот-соперник предугадал: " << randomComputerValue << endl << "Загадываемое число казино: " << casinoRandomValue << endl;
	cout << "\n[!] Ваш баланс: " << userBalance << "\n[!] Баланс бота: " << botBalance << endl;

	cout << "\n[!] Комиссия казино составила 10%" << endl;
}

void CasinoWishValue()
{
	casinoRandomValue = rand() % 100 + 1;

	cout << "\n[?] Компьютер загадывает число..." << endl;
	randomComputerValue = rand() % 100 + 1;
}

void CheckWinEndGame()
{
	if (userBalance == 0)
		cout << "[!] Вас обанкротили!" << endl;
	else if (botBalance == 0)
		cout << "[+] Вы обанкротили своего соперника" << endl;
}

int main()
{
	srand(time(NULL));

	setlocale(LC_ALL, "Russian");

	do
	{
		CheckMaximumUserWishValue();

		InformationAndInputBet();

		CheckLimitedBet(bet, botBalance);

		CheckMaximumBet(bet);

		CasinoWishValue();

		Sleep(1000);

		DifferenceBet();

		InformationBalance();

	} while (userBalance > 2 && botBalance > 2);

	CheckWinEndGame();
}
