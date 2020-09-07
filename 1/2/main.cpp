#include <iostream>
#include <fstream>
#include <errno.h>

using namespace std;

char* ReadString(istream *Input) {
	char* TempString = (char*)calloc(1, sizeof(char));
	char TempChar;
	for (int Index = 0; (TempChar = Input->get()) != '\n'; Index++) {
		char* TempFileName = (char*)realloc(TempString, ((Index + 2) * sizeof(char)));
		if (TempFileName != NULL) {
			TempString = TempFileName;
		}
		else {
			cout << "недостаточно памяти для работы приложения";
			Input->get();
			exit(0);
		}
		TempString[Index] = TempChar;
		TempString[Index + 1] = 0;
	}
	return TempString;
}

FILE* GetFile(const char* MSG, const char* Mode) {
	char* FileName;
	char RepeatInput = 'Y';
	FILE* TempFile = NULL;
	while (RepeatInput == 'Y')
	{
		cout << MSG << endl;

		FileName = ReadString(&cin);

		int Error = fopen_s(&TempFile, FileName, Mode);
		if (Error == EACCES) {
			cout << "Файл не доступен" << endl;
		}
		else {
			if (TempFile == NULL) {
				cout << "Файл не существует" << endl;
			}
			else {
				break;
			}
		}
		do {
			cout << "Повторить ввод? (Y - повторить, N - выйти)" << endl;
			RepeatInput = cin.get();
			if ((RepeatInput != 'Y') && (RepeatInput != 'N') && (RepeatInput != 'y') && (RepeatInput != 'n')) {

			}
		} while (true)
	}
	return TempFile;
}

int main(int ArgCount, const char* Args[]) {
	setlocale(LC_ALL, "Russian");
	FILE* Input = GetFile("Введите имя файла с данными", "rt");
	char* FileName = ReadString(&cin);
	cin.get();
}