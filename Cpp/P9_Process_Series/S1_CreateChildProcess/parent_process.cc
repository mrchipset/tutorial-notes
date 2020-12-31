#include <iostream>
#include <cstdlib>

#include <Windows.h>
#include <tchar.h>

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
    // initialize the start up information struc
    ZeroMemory( &start_info, sizeof(start_info) );
    // set the size of the struct
    start_info.cb = sizeof(start_info);
    // Initialize the process information struct
    ZeroMemory(process_info, sizeof(process_info) );

    flag = CreateProcessW(
               NULL,           // nullptr defualt
               wCmdStr,        // command line
               NULL,           // default process attributes
               NULL,           // default thread attributes
               FALSE,          // no inherited
               0,              // default create flag
               NULL,           // default system environment varivable
               NULL,           // use the parent cwd
               &start_info,    // start info
               process_info );// process info
    delete[] wCmdStr;

    if ( !flag ) {
        // failure
        printf( "Error: (%d).n", GetLastError() );
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
    WaitForSingleObject(process_info.hProcess, INFINITE );    // wait for the subprocess finished
    CloseChildProcess(&process_info);
    return 0;
}

#define _WIN32_NON_JOIN_

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