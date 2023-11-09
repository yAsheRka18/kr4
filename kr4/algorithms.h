#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <limits>
#include <io.h>
#include <regex>

using namespace std;

int CheckInt();
string ReadStringWithoutWhitespace();
bool File_Exists(string FileName);
bool Only_Read(string FileName);
bool IsValidFilename(const string& filename);
string getFilename(const string path);
bool IsReservedFileName(string FileName);
void GetMultistringText(string& text);

void ExtractDialogueLines(const string& text, vector<string>& dialogues);
void CompleteControlWork(string& text);
void SaveDIntoFile(string text, vector<string>& dialogues);