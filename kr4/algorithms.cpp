#include "algorithms.h"

using namespace std;

enum SaveListMenu {
	Save = 1,
	ContinueWithoutSaving = 2
};

enum SaveMethod {
	RewriteFile = 1,
	WriteToTheEndOfTheFile = 2,
	SelectAnotherFile = 3
};

enum CreatingAFile {
	CreateFile = 1,
	ContunueWithoutCreatingFile = 2
};

int CheckInt() {
	int tmp = 0;
	cin >> tmp;
	while (cin.fail()) {
		cout << "Введено некорректное значение, попробуйте еще раз: ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize> ::max(), '\n');
		cin >> tmp;
	}
	cin.ignore(numeric_limits<streamsize> ::max(), '\n');
	return tmp;
}

string ReadStringWithoutWhitespace() {
	string input;
	while (true) {
		getline(cin, input);
		istringstream iss(input);
		if (iss >> input && !isspace(input[0])) {
			return input;
		}
		else {
			cout << "Ошибка: входные данные не должны содержать пробелов. Повторите попытку ввода." << endl;
		}
	}
}

bool File_Exists(string FileName) {
	const char* path = FileName.c_str();
	if (!_access(path, 0)) {
		return true;
	}
	else {
		return false;
	}
}

bool Only_Read(string FileName) {
	const char* path = FileName.c_str();
	if (_access(path, 2)) {
		return true;
	}
	else
		return false;
}

bool IsValidFilename(const string& filename) {
	static const regex pattern("^[a-zA-Z0-9_\\-\\.]+$");
	return regex_match(filename, pattern);
}

string getFilename(const string path) {
	size_t pos = path.find_last_of("\\"); // Ищем последний символ '/' или '\'
	if (pos != string::npos) { // Если символ найден
		return path.substr(pos + 1); // Возвращаем имя файла после найденного символа
	}
	return path; // Если символ не найден, возвращаем исходный путь
}

bool IsReservedFileName(string FileName) {
	const int QuantityOfReservedNames = 22;
	string ReservedNames[QuantityOfReservedNames] = { "con", "prn" , "aux" , "nul" , "com1" , "com2" , "com3" , "com4" , "com5" , "com6" , "com7" , "com8" , "com9" ,
	"lpt1", "lpt2", "lpt3", "lpt4", "lpt5", "lpt6", "lpt7", "lpt8", "lpt9" };

	size_t pos = FileName.find_first_of(".");
	if (pos != string::npos) {
		FileName = FileName.substr(0, pos);
	}

	for (int i = 0; i < QuantityOfReservedNames; i++) {
		if (_stricmp(FileName.c_str(), ReservedNames[i].c_str()) == 0) {
			return true;
		}
	}
	return false;
}

void GetMultistringText(string& text) {
	char temp = ' ';
	int emptyEntersInARow = 0;
	while (emptyEntersInARow < 2) {
		temp = static_cast <char> (getchar());
		if (temp == '\n') {
			emptyEntersInARow++;
			if (emptyEntersInARow == 2) break;
			text += temp;
		}
		else {
			emptyEntersInARow = 0;
			text += temp;
		}
		temp = ' ';
	}
}

void ExtractDialogueLines(const string & text, vector<string>& dialogues) {
	
	string temp;
	bool isTextOkay = true;
	for (size_t i = 0; i < text.size(); i++) {
		if (i == 0 and (text[i] == '—' or text[i] == '-')) {
			for (size_t k = i + 1; k < text.size(); k++) {
				if (text[k] != (text[i] == '—' or text[i] == '-')) {
					break;
				}
				else {
					i = k;
					isTextOkay = false;
				}
			}
			for (size_t j = i + 1; j <= text.size(); j++) {
				if (text[j] == '\n' or j == text.size()) {
					if (text[j - 1] == '.' or text[j - 1] == '?' or text[j - 1] == '!') {
						for (size_t k = i; k <= j; k++) temp += text[k];
						if (i > 0) i = j - 2;
						dialogues.push_back(temp);
						temp = "";
						break;
					}
				}
			}
		} else
		if (text[i] == '\n') {
			if ((text[i + 1] == '—' or text[i+1] == '-') and i + 1 < text.size()) {
				for (size_t k = i + 1; k < text.size(); k++) {
					if (text[k] != (text[i] == '—' or text[i] == '-')) {
						break;
					}
					else {
						i = k;
						isTextOkay = false;
					}
				}
				for (size_t j = i+1; j <= text.size(); j++) {
					if (text[j] == '\n' or j == text.size()) {
						if (text[j - 1] == '.' or text[j - 1] == '?' or text[j - 1] == '!') {
							for (size_t k = i+1; k <= j; k++) temp += text[k];
							if (i > 0) i = j - 2;
							dialogues.push_back(temp);
							temp = "";
							break;
						}
					}
				}
			}
		}
	}

	if (!isTextOkay) cout << "Текст имеет неверный формат, желательно исправить! :)" << endl;

}


void SaveDIntoFile(string text, vector<string>& dialogues) {
	string FileName;
	ofstream file;
	int SaveChoise = 0;
	int SaveMethod = 0;
	int FileMethod = 0;
	int SaveData = 0;
	do {
		cout << "1 - Сохранить список в файл." << endl << "2 - Продолжить без сохранения." << endl << "> ";
		SaveChoise = CheckInt();
		switch (SaveChoise) {
		case Save:
			while (true) {
				cout << "Выберите данные для сохранения:" << endl << "1 - Сохранить результат выполнения программы." << endl << "2 - Сохранить исходные данные." << endl << "> ";
				SaveData = CheckInt();
				while (SaveData != 1 && SaveData != 2) {
					cout << "Такого пункта меню нету, попробуйте ввести другое число." << endl << "> ";
					SaveData = CheckInt();
				}
				if (SaveData == 1) {
					cout << "Введите путь к начальному файлу для сохранения диалога без указания формата (кол-во созданных файлов будет зависеть от кол-ва диалогов, к начальному файлу добавится номер) :" << endl << "> ";
					FileName = ReadStringWithoutWhitespace();
					string temp = FileName;
					for (size_t i = 0; i < dialogues.size(); i++) {
						FileName = temp + to_string(i + 1) + ".txt";
						if (File_Exists(FileName)) {
							do {
								cout << "Файл уже существует. Выберите режим ввода: " << endl << "1 - Перезаписать файл" << endl << "2 - Записать в конец файла" << endl << "> ";
								SaveMethod = CheckInt();
								switch (SaveMethod) {
								case RewriteFile:
									file.open(FileName, ios::trunc);
									file << dialogues[i];
									file.close();
									break;
								case WriteToTheEndOfTheFile:
									file.open(FileName, ios::app);
									file << '\n';
									file << dialogues[i];
									file.close();
									break;
								default:
									cout << "Такого пункта нет в меню, попробуйте еще раз" << endl;
									break;
								}
							} while (SaveMethod != RewriteFile && SaveMethod != WriteToTheEndOfTheFile && SaveMethod != SelectAnotherFile);
						}
						if (!File_Exists(FileName)) {
							do {
								cout << "Файла по данному пути не найдено, хотите создать его?" << endl
									<< "1 - Создать файл." << endl << "2 - Продолжить без сохранения." << endl << "> ";
								FileMethod = CheckInt();
								switch (FileMethod) {
								case CreateFile:
									file.open(FileName);
									file << dialogues[i];
									file.close();
									break;
								case ContunueWithoutCreatingFile:
									break;
								default:
									cout << "Такого пункта нет в меню, попробуйте еще раз" << endl;
									break;
								}
							} while (FileMethod != CreateFile && FileMethod != ContunueWithoutCreatingFile);
						} else if (Only_Read(FileName)) {
							cout << "Ошибка доступа к файлу. Файл доступен только для чтения." << endl;
							break;
						}
					}
					break;
				}
				if (SaveData == 2) {
					cout << "Введите путь к файлу для сохранения:" << endl << "> ";
					FileName = ReadStringWithoutWhitespace();
					while (IsReservedFileName(getFilename(FileName)) || !IsValidFilename(getFilename(FileName))) {
						cout << "Недопустимое название файла. Попробуйте еще раз." << endl << "> ";
						FileName = ReadStringWithoutWhitespace();
					}
					if (File_Exists(FileName)) {
						do {
							cout << "Файл уже существует. Выберите режим ввода: " << endl << "1 - Перезаписать файл" << endl << "2 - Записать в конец файла" << endl << "3 - Выбрать другой файл" << endl << "> ";
							SaveMethod = CheckInt();
							switch (SaveMethod) {
							case RewriteFile:
								file.open(FileName, ios::trunc);
								break;
							case WriteToTheEndOfTheFile:
								file.open(FileName, ios::app);
								file << '\n';
								break;
							case SelectAnotherFile:
								break;
							default:
								cout << "Такого пункта нет в меню, попробуйте еще раз" << endl;
								break;
							}
						} while (SaveMethod != RewriteFile && SaveMethod != WriteToTheEndOfTheFile && SaveMethod != SelectAnotherFile);
					}
					if (SaveMethod == RewriteFile || SaveMethod == WriteToTheEndOfTheFile || !File_Exists(FileName)) {
						break;
					}
					if (!File_Exists(FileName)) {
						do {
							cout << "Файла по данному пути не найдено, хотите создать его?" << endl
								<< "1 - Создать файл." << endl << "2 - Продолжить без сохранения." << endl << "> ";
							FileMethod = CheckInt();
							switch (FileMethod) {
							case CreateFile:
								file.open(FileName);
								break;
							case ContunueWithoutCreatingFile:
								break;
							default:
								cout << "Такого пункта нет в меню, попробуйте еще раз" << endl;
								break;
							}
						} while (FileMethod != CreateFile && FileMethod != ContunueWithoutCreatingFile);
					}
					else if (Only_Read(FileName)) {
						cout << "Ошибка доступа к файлу. Файл доступен только для чтения." << endl;
						break;
					}
					if ((SaveMethod == RewriteFile || SaveMethod == WriteToTheEndOfTheFile || FileMethod == CreateFile) && SaveData == 2) {
						file << text;
					}
					file.close();
					break;
				}
			}
		case ContinueWithoutSaving:
			break;
		default:
			cout << "Такого пункта нет в меню, попробуйте еще раз" << endl;
			break;
			}
		} 
	while (SaveChoise != Save && SaveChoise != ContinueWithoutSaving);
}

void CompleteControlWork(string& text) {
	vector<string> dialogues;
	ExtractDialogueLines(text, dialogues);
	cout << "Исходный текст:" << endl;
	cout << text;
	cout << endl << endl << "Диалоги:" << endl;
	for (int i = 0; i < dialogues.size(); i++) {
		cout << dialogues[i];
	}
	cout << endl << endl;
	SaveDIntoFile(text, dialogues);
	dialogues.clear();
}