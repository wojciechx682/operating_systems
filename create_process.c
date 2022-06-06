#include <windows.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <sys/types.h>

int input_argument;

int main(int argc, char* argv[])
{
    int count = argc;

    if (count != 2)
    {
        fprintf(stderr, "\nNalezy podac dokladnie jeden argument! \n");
        return 1;
    }
	
    input_argument = atoi(argv[1]);

	if(input_argument == 0)
    {
        fprintf(stderr,"\nPodaj liczbe naturalna! \n");        
        return 2;
    }	
		
	if(!(input_argument > 0 && input_argument < 14))
    {
        fprintf(stderr,"\nPodaj liczbe z przedzialu <1, .. ,13> !\n");        
        return 3;
    }	

    if (input_argument == 1 || input_argument == 2)
    {        
        return 1;
    }

    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));    
    ZeroMemory(&pi, sizeof(pi));
	
	si.cb = sizeof(si);
	
	STARTUPINFO si1;
    PROCESS_INFORMATION pi1;

    ZeroMemory(&si1, sizeof(si1));    
    ZeroMemory(&pi1, sizeof(pi1));
	
	si1.cb = sizeof(si1);
	
    int new_arg_1 = input_argument-1;  //argument wywołania 1 dziecka
    int new_arg_2 = input_argument-2;  //argument wywołania 2 dziecka
    char cmd_line[200];
    char cmd_line1[200];
    sprintf(cmd_line, "%s %d", argv[0], new_arg_1);
    sprintf(cmd_line1, "%s %d", argv[0], new_arg_2);


    // Start the child process. 
    if (!CreateProcessA(NULL,   // No module name (use command line)
						cmd_line,        // Command line
						NULL,           // Process handle not inheritable
						NULL,           // Thread handle not inheritable
						FALSE,          // Set handle inheritance to FALSE
						0,              // No creation flags
						NULL,           // Use parent's environment block
						NULL,           // Use parent's starting directory 
						&si,            // Pointer to STARTUPINFO structure
						&pi)           // Pointer to PROCESS_INFORMATION structure
        )
    {
        printf("CreateProcess failed (%d).\n", GetLastError());
        return 0;
    }
	
	if (!CreateProcessA(NULL,           // No module name (use command line)
						cmd_line1,      // Command line
						NULL,           // Process handle not inheritable
						NULL,           // Thread handle not inheritable
						FALSE,          // Set handle inheritance to FALSE
						0,              // No creation flags
						NULL,           // Use parent's environment block
						NULL,           // Use parent's starting directory 
						&si1,           // Pointer to STARTUPINFO structure
						&pi1)           // Pointer to PROCESS_INFORMATION structure
        )
    {
        printf("CreateProcess failed (%d).\n", GetLastError());
        return 0;
    }
	
	DWORD pid = GetCurrentProcessId();		
	DWORD ret_code;
	DWORD ret_code1;
	DWORD sum_code;	
	
    // Wait until child process exits.
    WaitForSingleObject(pi.hProcess, INFINITE);
    GetExitCodeProcess(pi.hProcess, &ret_code);
	
	WaitForSingleObject(pi1.hProcess, INFINITE);    
    GetExitCodeProcess(pi1.hProcess, &ret_code1);

	/*printf("PID = %d     ", pid);
	printf("PID = %d     ", pi.dwProcessId);
	printf("Child argument = %d     ", new_arg_1);
    printf("Retcode from child = %d     \n\n", ret_code);*/	
	
	printf("%d   %d    %d    %d\n", pid, pi.dwProcessId, new_arg_1, ret_code);
	//printf("     %d", pi.dwProcessId);
	//printf("     %d", new_arg_1);
    //printf("     %d\n", ret_code);
	
	printf("%d   %d    %d    %d\n", pid, pi1.dwProcessId, new_arg_2, ret_code1);
	//printf("%d     ", pii.dwProcessId);
	//printf("%d     ", new_arg_2);
    //printf("%d     \n", ret_codee);
	
	sum_code = ret_code + ret_code1;
	
	printf("%d                 %d\n\n", pid, sum_code);
	//printf("       ");
	//printf("       ");
    //printf("       %d\n", sum_code);	

    // Close process and thread handles. 
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
	
	CloseHandle(pi1.hProcess);
    CloseHandle(pi1.hThread);
	
	return sum_code;  //rodzic ma zwracac sumę powrotów kodów obu dzieci
    
}

// Uruchomienie programu: Ctrl + F5 lub menu Debugowanie > Uruchom bez debugowania
// Debugowanie programu: F5 lub menu Debugowanie > Rozpocznij debugowanie

// Porady dotyczące rozpoczynania pracy:
//   1. Użyj okna Eksploratora rozwiązań, aby dodać pliki i zarządzać nimi
//   2. Użyj okna programu Team Explorer, aby nawiązać połączenie z kontrolą źródła
//   3. Użyj okna Dane wyjściowe, aby sprawdzić dane wyjściowe kompilacji i inne komunikaty
//   4. Użyj okna Lista błędów, aby zobaczyć błędy
//   5. Wybierz pozycję Projekt > Dodaj nowy element, aby utworzyć nowe pliki kodu, lub wybierz pozycję Projekt > Dodaj istniejący element, aby dodać istniejące pliku kodu do projektu
//   6. Aby w przyszłości ponownie otworzyć ten projekt, przejdź do pozycji Plik > Otwórz > Projekt i wybierz plik sln
