#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int main(int argc, char **argv)
{
	// Check input from command line args
	// Check number of input paramenter
	if (argc != 4)
	{
		cout<<"Invalid number of arguments! Please go through README.md";
		return -1;
	}

	// Check for valid input
	for(int i = 1; i < argc - 1; i++)
		for(int j = 0; j < string(argv[i]).length(); j++)
			if(!isdigit(argv[i][j]))
			{
				cout<<"Invalid arguments! Please go through README.md"; // Enter only numbers!
				return -1;
			}

	// End of command line arg checking
	
	int alg_choice = atoi(argv[1]);
	int do_encrypt = atoi(argv[2]);
	string KEY = argv[3];

	if(!(alg_choice >= 0 && alg_choice <= 3))
	{
		cout<<"Invalid choice for encryption algorithm! Please go through README.md";
		return -1;
	}
	
	if(!(do_encrypt == 0 || do_encrypt == 1))
	{
		cout<<"Invalid choice for encryption or decryption. Please go through README.md";
		return -1;
	}

	ifstream inFPtr("process.txt");	// Hardcoding ze name as per assignment requirements :)

	// Check if file exists first before reading it duh?
	if(!inFPtr.good())
	{
		cout<<"Unable to access/read 'process.txt'. Does the file exist in the right place?";
		return -1;
	}
	
	// String that will store the entire 
	string file_data;

	// For storing the entire file contents in a string for easy manipulation! String Stream seems to be the best way!
	ostringstream string_stream;
	string_stream << inFPtr.rdbuf();
	file_data = string_stream.str();

	// Close the input file
	inFPtr.close();

	cout<<file_data<<endl;

	switch(alg_choice)
	{
		case 1:
				cout<<"Do da Caesar Cipher!"<<endl;
				break;

		case 2:
				cout<<"Do da Vigenere Cipher!"<<endl;
				break;

		case 3:
				cout<<"Do da play fair Cipher!"<<endl;
				break;

		default:
				cout<<"How did you even come here?? This is fatal!!";
	}

	return 0;
}