#include <iostream>
#include <cstdlib>

#include <Windows.h>
#include <tchar.h>


HANDLE g_hStdInWr;
HANDLE g_hStdInRd;
HANDLE g_hStdOutWr;
HANDLE g_hStdOutRd;


DWORD WriteToChild(const char buff[], const DWORD numberOfBytesToWrite)
{
    bool bSuccess = false;
    DWORD dwWritten;
    bSuccess = WriteFile(g_hStdInWr, buff, numberOfBytesToWrite, &dwWritten, nullptr);
    if (!bSuccess) {
        std::cerr << "Write to Child Failed." << std::endl;
    }
    return dwWritten;
}

DWORD ReadFromChild(char buff[], DWORD dwBufferSize)
{
    bool bSuccess = false;
    DWORD dwReadChild;
    bSuccess = ReadFile(g_hStdOutRd, buff, dwBufferSize, &dwReadChild, nullptr);
    if (!bSuccess) {
        std::cerr << "Read from Child Failed." << std::endl;
    }
    buff[dwReadChild] = '\0';
    return dwReadChild;
}

/**
 * @brief Create a Child Process
 *
 * @param cmd_str the command line string
 * @param process_info the pointer to the process info struct
 * @return true create the process successfully.
 * @return false catch a problem.
 */
bool CreateChildProcess(char* cmd_str, PROCESS_INFORMATION* process_info)
{
    STARTUPINFOW start_info;
    BOOL flag;
    wchar_t* wCmdStr = new wchar_t[strlen(cmd_str) + 1];
    size_t len;
    mbstowcs_s(&len, wCmdStr, strlen(cmd_str) + 1, cmd_str, strlen(cmd_str) + 1);
    // create the std pipe.
    SECURITY_ATTRIBUTES saAttr;
    saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
    saAttr.bInheritHandle = true;
    saAttr.lpSecurityDescriptor = nullptr;

    if (!CreatePipe(&g_hStdInRd, &g_hStdInWr, &saAttr, 0)
            || !CreatePipe(&g_hStdOutRd, &g_hStdOutWr, &saAttr, 0)) {
        std::cerr << "Create Stdio pipe error" << std::endl;
        std::cerr << "Error code:" << GetLastError() << std::endl;
        return false;
    }

    // set the handle attribute
    if (!SetHandleInformation(g_hStdOutRd, HANDLE_FLAG_INHERIT, 0) ||
            !SetHandleInformation(g_hStdInWr, HANDLE_FLAG_INHERIT, 0)) {
        std::cerr << "Set the handle information failed." << std::endl;
        return false;
    }


    // initialize the start up information struc
    ZeroMemory( &start_info, sizeof(start_info) );
    // set the size of the struct
    start_info.cb = sizeof(start_info);
    start_info.dwFlags |= STARTF_USESTDHANDLES;
    start_info.hStdInput = g_hStdInRd;
    start_info.hStdOutput = g_hStdOutWr;
    start_info.hStdError = g_hStdOutWr;
    // Initialize the process information struct
    ZeroMemory(process_info, sizeof(process_info) );

    flag = CreateProcessW(
               NULL,           // nullptr defualt
               wCmdStr,        // command line
               NULL,           // default process attributes
               NULL,           // default thread attributes
               true,          // no inherited
               0,              // default create flag
               NULL,           // default system environment varivable
               NULL,           // use the parent cwd
               &start_info,    // start info
               process_info );// process info
    delete[] wCmdStr;

    if ( !flag ) {
        // failure
        printf( "Error: (%d).n", GetLastError() );
        CloseHandle(g_hStdInRd);
        CloseHandle(g_hStdOutWr);
        return false;
    }
    return true;
}

/**
 * @brief Close the handle of child process
 *
 * @param process_info the pointer to process information
 * @return true
 */
bool CloseChildProcess(PROCESS_INFORMATION* process_info)
{
    // close the handles of process and thread.
    CloseHandle( process_info->hProcess );
    CloseHandle( process_info->hThread );
    CloseHandle(g_hStdInRd);
    CloseHandle(g_hStdOutWr);
    return true;
}

int main_system()
{
    std::system("test.exe");
    return 0;
}

int main_win32_non_join()
{
    PROCESS_INFORMATION process_info;
    CreateChildProcess("test.exe", &process_info);
    Sleep(1000);
    TerminateProcess(process_info.hProcess, 0);
    CloseChildProcess(&process_info);
    return 0;
}

int main_win32_join()
{
    PROCESS_INFORMATION process_info;
    CreateChildProcess("test.exe", &process_info);
    char write[] = "From Parent Process\n";
    char readBuff[128];
    const DWORD buff_size = 128;
    std::cout << "Bytes wrote to child:\t" << WriteToChild(write, strlen(write)) << std::endl;
    // ReadFromChild(readBuff, 16);
    // std::cout << "readBuff:" << readBuff << std::endl;
    WaitForSingleObject(process_info.hProcess, INFINITE);    // wait for the subprocess finished
    std::cout << "Byte read from child:\t" << ReadFromChild(readBuff, buff_size) << std::endl;
    std::cout << "readBuff:" << readBuff << std::endl;
    CloseChildProcess(&process_info);
    return 0;
}

// #define _WIN32_NON_JOIN_

int main()
{
    std::cout << "Current Process Id (parent_process): " <<  GetCurrentProcessId() << std::endl;
#ifdef _SYSTEM_METHOD_
    return main_system();
#else
#ifdef _WIN32_NON_JOIN_
    return main_win32_non_join();
#else
    return main_win32_join();
#endif
#endif
}