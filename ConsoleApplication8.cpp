#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include "globals.h"

using namespace std;

enum BotDifficulty { MEDIUM, HIGH }; // Уровни сложности бота

BotDifficulty botDifficulty = MEDIUM; // По умолчанию устанавливаем средний уровень сложности

void CheckLimitedBet(float& bet, float botBalance)
{
	while (bet > botBalance)
	{
		cout << "Вы не можете поставить больше кредитов, чем у бота-соперника на счету!" << "\nВведите ставку ещё раз: ";
		cin >> bet;
	}
}

void CheckMaximumBet(float& bet)
{
	while (bet > 20)
	{
		cout << "Максимальная ставка 20 кредитов. Введите ставку ещё раз: ";
		cin >> bet;
	}
}

void CheckMaximumUserWishValue()
{
	cout << "[!] Загадайте любое число от 1 до 100" << endl;
	do
	{
		cout << "Введите число от 1 до 100: ";
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
		cout << "\n[LOSE] К сожалению, компьютер оказался ближе к ответу." << endl;
	}
}

void InformationAndInputBet()
{
	cout << "\n[!] Максимальная ставка 20" << endl;
	cout << "[!] На вашем счету " << userBalance << " кредитов." << "\n\nВведите вашу ставку. Компьютер поставит точно такое же число кредитов, что и вы: ";
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

	if (botDifficulty == MEDIUM) {
		randomComputerValue = rand() % 100 + 1;
	}
	else if (botDifficulty == HIGH) {
		// Алгоритм бота высокого уровня сложности
		if (abs(enteredUserValue - casinoRandomValue) <= 20) {
			randomComputerValue = enteredUserValue;
		}
		else {
			randomComputerValue = rand() % 100 + 1;
		}
	}
}

void CheckWinEndGame()
{
	if (userBalance <= 0)
		cout << "[!] Вас обанкротили!" << endl;
	else if (botBalance <= 0)
		cout << "[+] Вы обанкротили своего соперника" << endl;
}

void ShowDifficultyMenu()
{
	cout << "Выберите уровень сложности бота:" << endl;
	cout << "1. Средний" << endl;
	cout << "2. Высокий" << endl;
	cout << "Введите номер уровня сложности: ";
	int choice;
	cin >> choice;

	if (choice == 1)
	{
		botDifficulty = MEDIUM;
		cout << "\n[+] Уровень сложности бота: Средний" << endl;
	}
	else if (choice == 2)
	{
		botDifficulty = HIGH;
		cout << "\n[+] Уровень сложности бота: Высокий" << endl;
	}
	else
	{
		cout << "\n[!] Некорректный выбор. Уровень сложности бота останется средним." << endl;
	}
}

int main()
{
	srand(time(NULL));

	setlocale(LC_ALL, "Russian");

	ShowDifficultyMenu();

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

	return 0;
}
