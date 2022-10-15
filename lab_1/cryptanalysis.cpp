/*
	Code to run cryptanalysis for the following ciphers
		- Caesar's
		- Vigenere

	Author: Srikar
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>

using namespace std;


// dictionary of frequency distribution of characters for caesars cipher
static float freq_caesar[] = {
	0.08167, 0.01492, 0.02782, 0.04253, .12702, 0.02228,
	0.02015, 0.06094, 0.06996, 0.00153, 0.00772, 0.04025,
	0.02406, 0.06749, 0.07507, 0.01929, 0.00095, 0.05987,
	0.06327, 0.09056, 0.02758, 0.00978, 0.02360, 0.00150,
	0.01974, 0.00074
	};

int main(int argc, char **argv)
{
	// Check input from command line args
	// Check number of input paramenter
	if (argc != 2)
	{
		cout<<"Invalid number of arguments! Please go through README.md";
		return -1;
	}

	// Check for valid input
	for(int j = 0; j < string(argv[1]).length(); j++)
		if(!isdigit(argv[1][j]))
		{
			cout<<"Invalid arguments! Please go through README.md"; // Enter only numbers!
			return -1;
		}

	// End of command line arg checking
	
	int alg_choice = atoi(argv[1]);

	if(!(alg_choice == 0 || alg_choice == 1))
	{
		cout<<"Invalid choice for encryption algorithm! Please go through README.md";
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

	// Ze Function prototypes
	void caesar(string);
	void vigenere(string);
	string strToUpper(string);

	file_data =  strToUpper(file_data);

	switch(alg_choice)
	{
		case 0:
				caesar(file_data);
				break;

		case 1:
				vigenere(file_data);
				break;

		default:
				cout<<"How did you even come here?? This is fatal!!";
	}

	return 0;
}

string strToUpper(string the_string)
{
	// Iterating through all chars of the string
	for(int i = 0; i < the_string.length(); i++)
	{
		if(!isalpha(the_string[i]))
			continue;
		
		the_string[i] = (isupper(the_string[i])) ? the_string[i] : toupper(the_string[i]);
	}
	
	return the_string;
}

void caesar(string file_data)
{
	cout<<"Caesar broo!!"<<endl;

	// TODO: Find the most frequent alphabet in encrypted text
	// Subtract it from most frequent alphabet in english character, i.e., E in our case
	// Print the key and decrypt the text
}

void vigenere(string file_data)
{
	cout<<"Vigenere broo!"<<endl;
}