#include <Windows.h>
#include "Header.h"
#define PATH L"..\\Debug\\DLLCode.dll"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HINSTANCE hMyDLL;
	if ((hMyDLL = LoadLibrary(PATH)) == NULL) return 1;
	MyFunctionCount myFynCount = (MyFunctionCount)GetProcAddress(hMyDLL, "GetCountData");
	user* Users = calloc(myFynCount(), sizeof(user));
	int kol = 0;
	MyFunction myFun = (MyFunction)GetProcAddress(hMyDLL, "ReadData");
	Users = myFun(Users, &kol);
	MyFunctionSearch myFunSearch = (MyFunctionSearch)GetProcAddress(hMyDLL, "Search");
	int kolvan = 0;
	Users = myFunSearch("Иванов", Users, kol, &kolvan);
	MyFunctionWrite myFunWrite = (MyFunctionWrite)GetProcAddress(hMyDLL, "WriteData");
	myFunWrite(Users, kolvan);
	MyFunctionSrAge myFunSrAge = (MyFunctionSrAge)GetProcAddress(hMyDLL, "middleAge");
	myFunSrAge(Users, kolvan);
	FreeLibrary(hMyDLL);
	return 0;
}