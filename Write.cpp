#include <iostream>
#include <Windows.h>

using namespace std;

int main()
{
	// Initalised Variables
	int task = 0;
	DWORD procId = 0;
	long long lpBuffer = 0;
	long long lpBuffer2 = 0;
	uintptr_t memAddr = 0x0;
	string lpBuffer3 = "";
	char lpBuffer4[128] = "";

	while (task != 1 && task != 2)
	{
		cout << "Is this task reading or writing?" << endl << "1. Reading" << endl << "2. Writing" << endl;
		cin >> task;

		if(task != 1 && task != 2)
			cout << "Invalid argument given." << endl << endl;
	}

	
	cout << endl << "Part 1:" << endl;

	// Prompt for Process ID
	cout << "Enter Process ID: "; cin >> procId;

	// Opening/attaching to process attempt
	HANDLE hProcess = OpenProcess((task != 1) ? PROCESS_VM_WRITE | PROCESS_VM_OPERATION : PROCESS_VM_READ, false, procId);

	if (hProcess == NULL)
	{
		cout << "Error code: " << dec << GetLastError() << endl;
		return 1;
	}

	// If successful attachment.
	cout << "OpenProcess successful" << endl << endl;

	// READING
	
	if (task == 1)
	{
		// Prompts for base address. Do not include 0x in the beginning when inputting.
		cout << "Part 2:" << endl;
		cout << "Enter Base Address for varInt: 0x"; cin >> hex >> memAddr;

		// Reading a value from memory address from process
		if (ReadProcessMemory(hProcess, (LPCVOID)memAddr, &lpBuffer, sizeof(int), 0))
		{
			cout << "varInt: " << lpBuffer << endl << endl; // Should be 123456
			system("pause > nul");
		}
		else
		{
			cout << "Error code: " << dec << GetLastError() << endl;
			system("pause > nul");
			return 1;
		}


		cout << "Part 3:" << endl;
		cout << "Enter Base Address for ptr2int: 0x"; cin >> hex >> memAddr;

		// Reading another value from another base address from process
		if (ReadProcessMemory(hProcess, (LPCVOID)memAddr, &lpBuffer, 8, 0))
		{
			cout << "ptr2int: " << hex << uppercase << lpBuffer << endl << endl; // Should be the first given address.
			memAddr = lpBuffer;
			if (ReadProcessMemory(hProcess, (LPCVOID)lpBuffer, &lpBuffer2, sizeof(int), 0))
			{
				cout << "varInt: " << dec << lpBuffer2 << endl << endl; // 123456
			}
			else
			{
				cout << "Error code 2: " << dec << GetLastError() << endl;
				system("pause > nul");
				return 1;
			}
			system("pause > nul");
		}
		else
		{
			cout << "Error code: " << dec << GetLastError() << endl;
			system("pause > nul");
			return 1;
		}


		cout << "Part 4:" << endl;
		cout << "Enter Base Address for varString: 0x"; cin >> hex >> memAddr;

		if (ReadProcessMemory(hProcess, (LPCVOID)memAddr, &lpBuffer3, sizeof(string), 0))
		{
			cout << "varString: " << lpBuffer3 << endl << endl; // Should be "DefaultString"
			system("pause > nul");
		}
		else
		{
			cout << "Error code: " << dec << GetLastError() << endl;
			system("pause > nul");
			return 1;
		}


		cout << "Part 5:" << endl;
		cout << "Enter Base Address for arrChar: 0x"; cin >> hex >> memAddr;

		if (ReadProcessMemory(hProcess, (LPCVOID)memAddr, &lpBuffer4, 128, 0))
		{
			cout << "arrChar: " << lpBuffer4 << endl << endl; // Should be "Long char array right here ->"
			system("pause > nul");
		}
		else
		{
			cout << "Error code: " << dec << GetLastError() << endl;
			system("pause > nul");
			return 1;
		}


		cout << "Part 6:" << endl;
		cout << "Input a random address. 0 for example"; cin >> hex >> memAddr;

		if (!ReadProcessMemory(hProcess, (LPCVOID)memAddr, &lpBuffer4, 128, 0))
		{
			cout << "Error code: " << dec << GetLastError() << endl;
			system("pause > nul");
		}


		cout << "Task Complete!";
		return 0;
	}
	else
	{
	    cout << "Part 1:" << endl;
	    cout << "Enter Base Address for varInt: 0x"; cin >> hex >> memAddr;
	    cout << "Input data that will be overwritten: "; cin >> dec >> lpBuffer;

	    // Overwriting existing data in nmemAddr
    	if (WriteProcessMemory(hProcess, (LPVOID)memAddr, &lpBuffer, sizeof(int), 0))
	    {
		    cout << "Overwritten successfully" << endl;
		    system("pause > nul");
	    }
	    else
	    {
		    cout << "Error code: " << dec << GetLastError() << endl;
		    system("pause > nul");
		    return 1;
	    }

		cout << "Part 2:" << endl;
		cout << "Enter Base Address for varString: 0x"; cin >> hex >> memAddr;
		cout << "Input data that will be overwritten: "; cin >> lpBuffer3;

		// Overwriting existing data in nmemAddr
		if (WriteProcessMemory(hProcess, (LPVOID)memAddr, &lpBuffer3, sizeof(string), 0))
		{
			cout << "Overwritten successfully" << endl;
			system("pause > nul");
		}
		else
		{
			cout << "Error code: " << dec << GetLastError() << endl;
			system("pause > nul");
			return 1;
		}

		cout << "Part 3:" << endl;
		cout << "Enter Base Address for arrChar: 0x"; cin >> hex >> memAddr;
		cout << "Input data that will be overwritten: "; cin >> lpBuffer4;

		// Overwriting existing data in nmemAddr
		if (WriteProcessMemory(hProcess, (LPVOID)memAddr, &lpBuffer4, sizeof(lpBuffer4), 0))
		{
			cout << "Overwritten successfully" << endl;
			system("pause > nul");
		}
		else
		{
			cout << "Error code: " << dec << GetLastError() << endl;
			system("pause > nul");
			return 1;
		}
    }

	// Detaching from process to avoid leak
	CloseHandle(hProcess);
}
