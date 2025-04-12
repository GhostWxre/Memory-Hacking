#include <iostream>
#include <Windows.h>

using namespace std;

int main()
{

	int varInt = 987654;
	string varString = "DefaultString";
	char arrchar[128] = "Long char array right here ->";

	int* ptr2int = &varInt;
	int** ptr2ptr = &ptr2int;
	int*** ptr2ptr2 = &ptr2ptr;

	do
	{
		cout << "PROCESS ID: " << dec << GetCurrentProcessId() << endl;
		cout << "varInt (0x" << hex << uppercase << (uintptr_t)ptr2int << ") = " << dec << varInt << endl;
		cout << "varString (0x" << hex << uppercase << (uintptr_t)&varString << ") = " << varString << endl;
		cout << "arrChar[128] (0x" << hex << (uintptr_t)&arrchar << ") = " << arrchar << endl;
		cout << endl;

		cout << "ptr2int (0x" << hex << uppercase << (uintptr_t)&ptr2int << ") = 0x" << ptr2int << endl;
		cout << "ptr2ptr (0x" << hex << uppercase << (uintptr_t)&ptr2ptr << ") = 0x" << ptr2ptr << endl;
		cout << "ptr2ptr2 (0x" << hex << uppercase << (uintptr_t)&ptr2ptr2 << ") = 0x" << ptr2ptr2 << endl;
		cout << endl << "Press Enter to print again..." << endl;
		cout << "---------------------------------------------------" << endl << endl;
		system("pause > nul");
	} while (true);

	return 0;
}
