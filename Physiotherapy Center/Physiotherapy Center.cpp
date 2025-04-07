
#include <iostream>
#include"Center.h"
using namespace std;

int main()
{
	Center center;
	string input, filename;
	while (true)
	{
		cout << "Current TimeStep: " << center.getTime() << "\n ";
		cout << "Press Q to stop " << endl;
		getline(cin, input);
		if (input == "Q" || input == "q")
			break;
		/*if (input == "S" || input == "s")
		{
			for (int i = 0; i < 9; i++)
			{
				center.IncTime();
			}
		}*/
		center.IncTime();
	}
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
