/*
		Лабораторная: 1
		Задание: 2
		Выполнил: Мусин Виктор ПС-22
		Имя файла с входными данными вводится после запуска программы
		Структура входного файла: любой набор символов, все числа считываются как положительные
		Имя файла с выходными данными вводится так же после запуска, после ввода имени файла с входными данными
		Структура выходного файла: "Сумма всех чисел во входном файле: " + [число]
		Если во входных данных нет ни одного числа, то сумма равна 0
*/
#include <iostream>
#include <fstream>

using namespace std;

int StringLength(char* String){
	int Index = 0;
	for(; String[Index] != 0; Index++){}
	return Index;
}

char* StringAppend(char* String, char Char){
	char* TempString = (char*)realloc(String, ((StringLength(String) + 2) * sizeof(char)));
	if (TempString != NULL) {
		return TempString;
	}
}

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
			delete TempString;
			return NULL;
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

		TempFile = fopen(FileName, Mode);
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

short CharToDigit(char Digit)
{
	switch (Digit)
	{
	case '0':
		return 0;
	case '1':
		return 1;
	case '2':
		return 2;
	case '3':
		return 3;
	case '4':
		return 4;
	case '5':
		return 5;
	case '6':
		return 6;
	case '7':
		return 7;
	case '8':
		return 8;
	case '9':
		return 9;
	default:
		return -3;
	}
}

char DigitToChar(short Digit)
{
	switch (Digit)
	{
	case 0:
		return '0';
	case 1:
		return '1';
	case 2:
		return '2';
	case 3:
		return '3';
	case 4:
		return '4';
	case 5:
		return '5';
	case 6:
		return '6';
	case 7:
		return '7';
	case 8:
		return '8';
	case 9:
		return '9';
	default:
		return 'A';
	}
}

char* NumToString(long long Number)
{
	long long TempNum = Number;
	int LengthString = 1;
	char* StringNum = (char*)calloc(LengthString, sizeof(char));

	StringNum[0] = 0;

	if(TempNum < 0){

	}
	do
	{
		char TempChar = DigitToChar(TempNum % 10);
		TempNum = TempNum / 10;
		LengthString++;
		char* TempFileName = (char*)realloc(StringNum, ((LengthString) * sizeof(char)));
		
		if (TempFileName != NULL) {
			StringNum = TempFileName;
		}
		else {
			cout << "недостаточно памяти для работы приложения";
			cin.get();
			delete StringNum;
			return "-1";
		}

		for(int Index = LengthString - 2; Index >= 0; Index--)
		{
			StringNum[Index + 1] = StringNum[Index];
		}
		StringNum[0] = TempChar;
	} while (TempNum > 0);
	return StringNum;
}

short ReadDigit(FILE* InputData)
{
	if (!feof(InputData)){
		char Digit = getc(InputData);
		if(Digit == '-'){return -1;}
		if(Digit == '\n'){return -2;}
		return CharToDigit(Digit);
	}
	return -100;
}

long long ReadNum(FILE* InputData)
{
	const long long OverflowNum = INT64_MAX / 10;

	bool IsNegative = false;
	long long Number = 0;
	bool FindDigit = false;
	
	while(!feof(InputData)){
		short Digit = ReadDigit(InputData);
		if(Digit != -2){
			if(Digit >= 0)
			{
				FindDigit = true;
				Number = Number * 10 + Digit;
				if(OverflowNum <= Number) return (IsNegative ? -Number : Number);
			}
			else if(FindDigit) return (IsNegative ? -Number : Number);
			else if(Digit == -1) 
			{
				if (!IsNegative) IsNegative = true;
			}
			else IsNegative = false;
		}
	}
	if(FindDigit) return Number;
	else return 0;
}

long long CalculateSum(FILE* InputData)
{
	long long TempNum = 0;
	long long Sum = 0;

	while(!feof(InputData))
	{
		TempNum = ReadNum(InputData);
		Sum += TempNum;
		cout << TempNum << endl;
	}
	return Sum;
}

int main(int ArgCount, const char* Args[]) {

	setlocale(LC_ALL, "Russian");

	FILE* Input = GetFile("Введите имя файла с данными", "rt");
	if(Input == NULL) exit(0);

	FILE* Output = GetFile("Введите имя выходного файла", "wt");
	if(Output == NULL) exit(0);

	fputs("Сумма всех чисел во входном файле: ", Output);
	char* Result = NumToString(CalculateSum(Input));
	if (Result != "-1")
	{
		fputs(Result, Output);
	}

	fclose(Input);
	fclose(Output);
}