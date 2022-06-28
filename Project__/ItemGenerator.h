#pragma once

#include <Windows.h>

const int IG_OK = 0;
const int IG_GEN = 1;


const LPCWSTR ITEM_GENERATOR_CLASSNAME = L"ItemGenWindowClass";
const LPCWSTR ITEM_GENERATOR_NAME = L"Item Generator";

const int IG_WIDTH = 660;
const int IG_HEIGHT = 800;

typedef struct {
	HWND hOut, hOk, hGen;

	HWND hIdEdit, hCountEdit;

	int (*callback)(char *, int);
} ItemGenerator;


void createItemGeneratorWindow(WNDCLASSEX &, HWND&, HINSTANCE &, int, int (*)(char*, int));

void addItemGeneratorControls(HWND, ItemGenerator*);

LRESULT CALLBACK ItemGeneratorWindowProc(HWND, UINT, WPARAM, LPARAM);

extern bool itemGeneratorCreatedBefore;
