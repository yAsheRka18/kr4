#include "menu.h"
#include "algorithms.h"
#include "moduletests.h"

using namespace std;

enum PrintMenu {
	StartProgramm = 1,
	StartModuleTests = 2,
	StopProgramm = 3
};

enum InputMethod {
	FromTheFile = 1,
	FromTheConsole = 2,
	ReturnMenu = 3
};

void Print_menu() {
	system("cls");
	cout << "Роева Алёна 425 группа." << endl << "Контрольная работа №4. Вариант 4." << endl;
	cout << "Классы потоков ввода вывода." << endl;
	cout << "------------------------------------------------------------------------------------------------------" << endl;
	cout << "Задание:" << endl;
	cout << "Выделить в заданном тексте все диалоги (начинающиеся с новой строки символа «тире»)."
		<< endl << "Сохранить диалоги в отдельных текстовых файлах." << endl
		<< "Использовать правила построения диалогов, применяющиеся в русскоязычных текстах." << endl;
	cout << "------------------------------------------------------------------------------------------------------" << endl;
	cout << "Выберите нужный пункт меню:" << endl << "1 - Начать работу программы." << endl << "2 - Выполнить модульные тесты." << endl
		<< "3 - Завершить работу программы" << endl << "> ";
}

void InputMethodMenu() {
	string text;
	char tmp = ' ';
	string temp;
	string path;
	int input = 0;
	ifstream file;
	int UserChoise1 = 0;
	int UserChoise2 = 0;
	do {
		system("cls");
		cout << "Выберите способ ввода данных:" << endl << "1 - Ввод текста из файла." << endl << "2 - Ввод текста из консоли." << endl << "3 - Выход в главное меню программы." << endl << "> ";
		UserChoise1 = CheckInt();
		text = "";
		switch (UserChoise1) {
		case FromTheFile:
			cout << "Введите путь файла:" << endl << "> ";
			path = ReadStringWithoutWhitespace();
			while (!File_Exists(path)) {
				cout << "Ошибка при открытии файла! Попробуйте ввести путь снова." << endl << "> ";
				path = ReadStringWithoutWhitespace();
			}
			file.open(path);
			while (file.get(tmp)) {
				text += tmp;
			}
			file.clear();
			file.close();
			CompleteControlWork(text);
			UserChoise1 = ReturnMenu;
			break;
		case FromTheConsole:
			cout << "Введите текст с клавиатуры. Для окончания ввода нажмите дважды Enter" << endl;
			GetMultistringText(text);
			CompleteControlWork(text);
			UserChoise1 = ReturnMenu;
			break;
		case ReturnMenu:
			break;
		default:
			cout << "Такого пункта нет в меню, попробуйте еще раз" << endl;
			break;
		}
		if (UserChoise1 != ReturnMenu) system("pause");
	} while (UserChoise1 != ReturnMenu);
}

void MainMenu() {

	setlocale(LC_ALL, "RU");

	int UserChoise = 0;
	do {
		system("cls");
		Print_menu();
		UserChoise = CheckInt();
		switch (UserChoise) {
		case StartProgramm:
			InputMethodMenu();
			break;
		case StartModuleTests:
			CompleteModuleTests();
			break;
		case StopProgramm:
			break;
		default:
			cout << "Такого пункта нет в меню, попробуйте еще раз" << endl;
			break;
		}
		if (UserChoise != StopProgramm)	system("pause");
	} while (UserChoise != StopProgramm);

}