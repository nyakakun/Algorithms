#include <iostream>
#include <fstream>

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

		FILE* TempFile = fopen(FileName, Mode);
		if (TempFile == NULL) {
			cout << "Файл не существует или не доступен" << endl;
		}
		else {
			break;
		}
		do {
			cout << "Повторить ввод? (Y - повторить, N - выйти)" << endl;
			RepeatInput = cin.get();
			if (RepeatInput == 'y'){RepeatInput = 'Y';}
		} while (!((RepeatInput == 'Y') or ((RepeatInput == 'N') or (RepeatInput == 'n'))));
	}
	return TempFile;
}

long int CalculateSum(FILE* InputData, FILE* OutputData)
{
	while(InputData)
	{

	}
}

int main(int ArgCount, const char* Args[]) {
	setlocale(LC_ALL, "Russian");
	FILE* Input = GetFile("Введите имя файла с данными", "rt");
	if (Input == NULL) exit(0);
	FILE* Output = GetFile("Введите имя выходного файла", "wt");
	if (Output == NULL) exit(0);
	CalculateSum(Input, Output);
}