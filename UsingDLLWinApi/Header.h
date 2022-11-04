#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <Windows.h>
OVERLAPPED ovelapf;

struct person
{
	char* surname;
	char* name;
	char* patronomic;
	int age;
};

typedef struct person user;

__declspec(dllexport) int GetCountData();
__declspec(dllexport) user* ReadData(user* Users, int* kol);
__declspec(dllexport) void WriteData(user* Users, int kol);
__declspec(dllexport) user* Search(char* str, user* Users, int kol, int* kolSearch);
__declspec(dllexport) void middleAge(user* Users, int kol);


typedef int (_cdecl* MyFunctionCount)();
typedef user* (_cdecl* MyFunction)(user*, int*);
typedef void(_cdecl* MyFunctionWrite)(user*, int);
typedef user* (_cdecl* MyFunctionSearch)(char*, user*, int, int*);
typedef void(_cdecl* MyFunctionSrAge)(user*, int);