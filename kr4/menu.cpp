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
	cout << "����� ���� 425 ������." << endl << "����������� ������ �4. ������� 4." << endl;
	cout << "������ ������� ����� ������." << endl;
	cout << "------------------------------------------------------------------------------------------------------" << endl;
	cout << "�������:" << endl;
	cout << "�������� � �������� ������ ��� ������� (������������ � ����� ������ ������� �����)."
		<< endl << "��������� ������� � ��������� ��������� ������." << endl
		<< "������������ ������� ���������� ��������, ������������� � ������������� �������." << endl;
	cout << "------------------------------------------------------------------------------------------------------" << endl;
	cout << "�������� ������ ����� ����:" << endl << "1 - ������ ������ ���������." << endl << "2 - ��������� ��������� �����." << endl
		<< "3 - ��������� ������ ���������" << endl << "> ";
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
		cout << "�������� ������ ����� ������:" << endl << "1 - ���� ������ �� �����." << endl << "2 - ���� ������ �� �������." << endl << "3 - ����� � ������� ���� ���������." << endl << "> ";
		UserChoise1 = CheckInt();
		text = "";
		switch (UserChoise1) {
		case FromTheFile:
			cout << "������� ���� �����:" << endl << "> ";
			path = ReadStringWithoutWhitespace();
			while (!File_Exists(path)) {
				cout << "������ ��� �������� �����! ���������� ������ ���� �����." << endl << "> ";
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
			cout << "������� ����� � ����������. ��� ��������� ����� ������� ������ Enter" << endl;
			GetMultistringText(text);
			CompleteControlWork(text);
			UserChoise1 = ReturnMenu;
			break;
		case ReturnMenu:
			break;
		default:
			cout << "������ ������ ��� � ����, ���������� ��� ���" << endl;
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
			cout << "������ ������ ��� � ����, ���������� ��� ���" << endl;
			break;
		}
		if (UserChoise != StopProgramm)	system("pause");
	} while (UserChoise != StopProgramm);

}