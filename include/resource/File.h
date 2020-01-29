#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
typedef struct {
    HANDLE handle;
} FILEHANDLE;

FILEHANDLE* File_OpenRead(const char* filename);
void File_Read(FILEHANDLE* file, void* buffer, int size);
void File_Close(FILEHANDLE* file);
unsigned long File_GetSize(FILEHANDLE* file);
char* File_ReadIntoBuffer(const char* filename, unsigned long* size);
