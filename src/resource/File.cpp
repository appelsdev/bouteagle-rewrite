#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdlib.h>
#include "system/ExceptionHandler.h"
#include "resource/File.h"

/*******************************************************************************
DESCRIPTION:
    Open a file for reading.
ARGUMENTS:
    filename - Path to file.
RETURNS:
    Pointer to the created FILEHANDLE struct.
*******************************************************************************/
FILEHANDLE* File_OpenRead(const char* filename) {
    try {
        // open file for reading
        HANDLE handle = CreateFile(
            filename,              // file path
            GENERIC_READ,          // open for reading
            0,                     // no sharing mode
            NULL,                  // default security
            OPEN_EXISTING,         // don't create file if it doesn't exist
            FILE_ATTRIBUTE_NORMAL, // normal file
            NULL                   // no template file
        );
        // check for file opening errors
        if (INVALID_HANDLE_VALUE == handle)
            throw IOException(
                std::string("Unable to open file '") + std::string(filename) +
                std::string("' for reading."));
        // allocate file handle struct
        FILEHANDLE* f = (FILEHANDLE*)malloc(sizeof(FILEHANDLE));
        f->handle = handle; // opened file handle
        return f;
    } catch (BoutEagleException& e) {
        ExceptionHandler::Handle(e);
    }
    return NULL;
}

/*******************************************************************************
DESCRIPTION:
    Reads a given amount of bytes from a file.
ARGUMENTS:
    file - Pointer to an opened file handle.
    buffer - Buffer where the read bytes will be put.
    size - Amount of bytes to read.
*******************************************************************************/
void File_Read(FILEHANDLE* file, void* buffer, int size) {
    try {
        // check if the given handle was valid
        if (!file)
            throw IOException("Invalid handle in File_Read.");
        // read bytes from open file handle
        DWORD bytesRead;
        BOOL status = ReadFile(
            file->handle, // file handle
            buffer,       // buffer to read the bytes to
            size,         // the amount of bytes to read
            &bytesRead,   // output ptr for the number of bytes read
            NULL          // not overlapped
        );
        // check for read errors
        if (FALSE == status)
            throw IOException("Failed to read from open file handle in File_Read.");
    } catch (BoutEagleException& e) {
        ExceptionHandler::Handle(e);
    }
}

/*******************************************************************************
DESCRIPTION:
    Close an open file handle.
ARGUMENTS:
    file - Pointer to the opened file handle to close. Please take note that the
           pointer will also be freed.
*******************************************************************************/
void File_Close(FILEHANDLE* file) {
    try {
        // check if the given handle was valid
        if (!file)
            throw IOException("Invalid handle in File_Close.");
        // close file struct's handle
        if (!CloseHandle(file->handle))
            throw IOException("Unable to close file handle.");
        // free struct
        free(file);
    } catch (BoutEagleException& e) {
        ExceptionHandler::Handle(e);
    }
}

/*******************************************************************************
DESCRIPTION:
    Get an open file's size.
ARGUMENTS:
    file - File handle.
RETURNS:
    Size of the file in bytes. Maximum returned size is 4,294,967,295 bytes.
*******************************************************************************/
unsigned long File_GetSize(FILEHANDLE* file) {
    try {
        // check if the given handle was valid
        if (!file)
            throw IOException("Invalid handle in File_GetSize.");
        // get file size
        return GetFileSize(file->handle, NULL);
    } catch (BoutEagleException& e) {
        ExceptionHandler::Handle(e);
        return NULL;
    }
}

/*******************************************************************************
DESCRIPTION:
    Read a file into a buffer or string.
ARGUMENTS:
    filename - File path.
    size - Out pointer to the file buffer's size. If NULL, the returned buffer
           will be a null-terminated string and thus, a size variable will not
           be needed.
RETURNS:
    Pointer to an allocated buffer (or string) containing the file's contents.
*******************************************************************************/
char* File_ReadIntoBuffer(const char* filename, unsigned long* size) {
    // open file
    FILEHANDLE* file = File_OpenRead(filename);
    // get the file's size and allocate the file buffer
    unsigned long fileSize = File_GetSize(file);
    char* buffer;
    if (!size) { // NULL check
        // allocate null-terminated string
        buffer = (char*)malloc(fileSize + 1);
        buffer[fileSize] = '\0';
    } else {
        // allocate buffer and set returned size
        buffer = (char*)malloc(fileSize);
        *size = fileSize;
    }
    // read the file contents
    File_Read(file, buffer, fileSize);
    // close file
    File_Close(file);
    return buffer;
}
