#include "moduletests.h"

using namespace std;

void CompleteModuleTests() {
	
	ifstream input, result;
	string temp = "";
	string inputPaths[5] = { "A.txt", "B.txt", "C.txt", "D.txt", "E.txt" };
	string resultPaths[5] = { "A1.txt", "B1.txt", "C1.txt", "D1.txt", "E1.txt" };
	bool isTaskOkay = true;
	bool isFilesMissing = false;

	for (size_t k = 0; k < 5; k++) {
		vector <string> dialogues;
		int reqSubstringLength = 0;
		string inputText = "";
		string algorithmText = "";
		string resultText = "";
		char tmp = ' ';

		input.open(inputPaths[k]);
		if (!input.is_open()) {
			cout << "Ошибка при открытии файла " << inputPaths[k] << endl;
			isFilesMissing = true;
			continue;
		}

		while (input.get(tmp)) {
			inputText += tmp;
		}

		result.open(resultPaths[k]);
		temp = "";
		while (result.get(tmp)) {
			resultText += tmp;
		}
		resultText += '\0';

		ExtractDialogueLines(inputText, dialogues);
		for (size_t i = 0; i < dialogues.size(); i++) {
			algorithmText += dialogues[i];
		}


		if (algorithmText != resultText) {
			cout << "Не совпали строки из файлов " << inputPaths[k] << " и " << resultPaths[k] << endl;
			cout << algorithmText << endl << resultText << endl;
			isTaskOkay = false;
		}

		inputText = "";
		resultText = "";
		algorithmText = "";
		dialogues.clear();
		result.close();
		input.close();

	}

	if (isTaskOkay && !isFilesMissing) {
		cout << "Задание работает корректно." << endl;
	}
	if (isFilesMissing) {
		cout << "Невозможно выполнить тесты, отсутсвуют файлы с данными." << endl;
	}
}