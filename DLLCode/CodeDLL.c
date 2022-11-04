#include "..\UsingDLLWinApi\Header.h"

BOOL WINAPI DllMain(
	HINSTANCE hinstDLL,  // handle to DLL module
	DWORD dwReason,     // reason for calling function
	LPVOID ipReserved)  // reserved
{
	BOOL ballWentWell = TRUE;
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		// Initialize once for each new process.
		// Return FALSE to fail DLL load.
		break;

	case DLL_THREAD_ATTACH:
		// Do thread-specific initialization.
		break;

	case DLL_THREAD_DETACH:
		// Do thread-specific cleanup.
		break;

	case DLL_PROCESS_DETACH:
		break;
	}

	if (ballWentWell)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

int GetCountData()
{
	HANDLE fileStart;
	fileStart = CreateFile(L"..\\Users.csv",    // открываемый файл
		GENERIC_READ,          // открываем для чтения
		FILE_SHARE_READ,       // для совместного чтения
		NULL,                  // защита по умолчанию
		OPEN_EXISTING,         // только существующий файл
		FILE_ATTRIBUTE_NORMAL, // обычный файл
		NULL);                 // атрибутов шаблона нет
	if (fileStart == INVALID_HANDLE_VALUE)
	{
		MessageBox(NULL, L"При открытие файла возникла ошибка!", L"Окно программы", MB_OK);
		return 0;
	}
	DWORD d;
	char* str = calloc(100000, 1);
	ReadFile(fileStart, str, 100000, &d, NULL);
	CloseHandle(fileStart);
	int kol = 0;
	int i = 0;
	while (i != 100000)
	{
		if (str[i] == '\n')
		{
			kol++;
		}
		i++;
	}
	return kol;
}

user* ReadData(user* Users, int* kol) // Чтение данных
{
	HANDLE fileStart;
	fileStart = CreateFile(L"..\\Users.csv",    // открываемый файл
		GENERIC_READ,          // открываем для чтения
		FILE_SHARE_READ,       // для совместного чтения
		NULL,                  // защита по умолчанию
		OPEN_EXISTING,         // только существующий файл
		FILE_ATTRIBUTE_NORMAL, // обычный файл
		NULL);                 // атрибутов шаблона нет
	if (fileStart == INVALID_HANDLE_VALUE)
	{
		MessageBox(NULL, L"При открытие файла возникла ошибка!", L"Окно программы", MB_OK);
		return Users;
	}
	DWORD d;
	char* str = calloc(100000, 1);
	ReadFile(fileStart, str, 100000, &d, NULL);
	CloseHandle(fileStart);
	preopStrok(str, Users, kol);
	return Users;
}

int preopStrok(char *str, user* Users, int* kol)
{
	int i = 0;
	int k = 0;
	char* stroka = calloc(100, 1);
	int p = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '"')
		{
			i++;
		}
		else
		{
			while (str[i] != ';')
			{
				stroka[p] = str[i];
				p++;
				i++;
			}
			i++;
			Users[k].surname = calloc(p+1, sizeof(char));
			strncpy(Users[k].surname, stroka, p);
			free(stroka);
			stroka = calloc(100, 1);
			p = 0;
			while (str[i] != ';')
			{
				stroka[p] = str[i];
				p++;
				i++;
			}
			i++;
			Users[k].name = calloc(p + 1, sizeof(char));
			strncpy(Users[k].name, stroka, p);
			free(stroka);
			stroka = calloc(100, 1);
			p = 0;
			while (str[i] != ';')
			{
				stroka[p] = str[i];
				p++;
				i++;
			}
			i++;
			Users[k].patronomic = calloc(p + 1, sizeof(char));
			strncpy(Users[k].patronomic, stroka, p);
			free(stroka);
			stroka = calloc(100, 1);
			p = 0;
			while (str[i] != '\"')
			{
				stroka[p] = str[i];
				p++;
				i++;
			}
			i++;
			Users[k].age = atoi(stroka);
			free(stroka);
			stroka = calloc(100, 1);
			p = 0;
			i += 2;
			k++;
		}
	}
	*kol = k;
}

void WriteData(user* Users, int kol) // Запись данных в .CSV файл
{
	HANDLE fileResult = CreateFile(L"..\\Result.csv",    // создаваемый файл
		GENERIC_WRITE,         // открывается для записи
		FILE_SHARE_WRITE,      // совместно не используется
		NULL,                  // защита по умолчанию
		CREATE_ALWAYS,         // переписывает существующий
		FILE_ATTRIBUTE_HIDDEN,  // асинхронный ввод/вывод I/O
		NULL);                 // атрибутов шаблона нет
	int i = 0;
	DWORD d;
	char* str;
	while (i != kol)
	{
		str = calloc(100, sizeof(char));
		sprintf(str, "%s;", Users[i].surname);
		WriteFile(fileResult, str, strlen(str), &d, NULL);
		free(str);
		str = calloc(100, sizeof(char));
		sprintf(str, "%s;", Users[i].name);
		WriteFile(fileResult, str, strlen(str), &d, NULL);
		free(str);
		str = calloc(100, sizeof(char));
		sprintf(str, "%s;", Users[i].patronomic);
		WriteFile(fileResult, str, strlen(str), &d, NULL);
		free(str);
		str = calloc(100, sizeof(char));
		sprintf(str, "%d\n", Users[i].age);
		WriteFile(fileResult, str, strlen(str), &d, NULL);
		i++;
	}
	CloseHandle(fileResult);
}

user* Search(char* str, user* Users, int kol, int *kolSearch)
{
	int i = 0;
	int p = 0;
	user* UsersSearch = calloc(SearchCount(str, Users, kol), sizeof(user));
	while (i != kol)
	{
		if (strstr(Users[i].surname, str) != NULL)
		{
			UsersSearch[p].surname = Users[i].surname;
			UsersSearch[p].name = Users[i].name;
			UsersSearch[p].patronomic = Users[i].patronomic;
			UsersSearch[p].age = Users[i].age;
			p++;
		}
		i++;
	}
	*kolSearch = p;
	return UsersSearch;
}

int SearchCount(char* str, user* Users, int kol)
{
	int i = 0;
	int p = 0;
	while (i != kol)
	{
		if (strstr(Users[i].surname, str) != NULL)
		{
			p++;
		}
		i++;
	}
	return p;
}

void middleAge(user* Users, int kol) // Подсчет среднего возраста
{
	int i = 0;
	int summa = 0;
	while (i != kol)
	{
		summa += Users[i].age;
		i++;
	}
	double srAge = (double)summa / (double)kol;
	HANDLE fileResult;
	fileResult = CreateFile(L"..\\Result.csv",    // открываемый файл
		GENERIC_WRITE,          
		FILE_SHARE_WRITE,      
		NULL,               
		OPEN_EXISTING,        
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	if (fileResult == INVALID_HANDLE_VALUE)
	{
		MessageBox(NULL, L"При открытие файла возникла ошибка!", L"Окно программы", MB_OK);
	}
	DWORD d;
	
	char* strNew = calloc(100000, sizeof(char));
	sprintf(strNew, "Средний возраст: %f", srAge);
	ovelapf.Offset = 0xFFFFFFFF;
	ovelapf.OffsetHigh = 0xFFFFFFFF;
	WriteFile(fileResult, strNew, strlen(strNew), &d, &ovelapf);
	CloseHandle(fileResult);
}