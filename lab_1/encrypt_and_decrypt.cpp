#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include <algorithm>

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

	// Ze Function prototypes
	void caesar(string, int, string);
	void vigenere(string, int, string);
	string strToUpper(string);

	file_data =  strToUpper(file_data);

	switch(alg_choice)
	{
		case 1:
				caesar(file_data, do_encrypt, KEY);
				break;

		case 2:
				vigenere(file_data, do_encrypt, KEY);
				break;

		case 3:
				cout<<"Do da play fair Cipher!"<<endl;
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

void caesar(string file_data, int do_encrypt, string KEY)
{
	// Iterating through all chars of the key
	for(int i = 0; i < KEY.length(); i++)
		// Making sure we get a numeric key for Caesar's cipher
		if(!isdigit(KEY[i]))
		{
			cout<<"Invalid key entered for Caesar's Cipher! Please go through README.md";
			exit(-1);
		}

	// Converting KEY from char to string
	int KEY_VAL = stoi(KEY);

	// Encryption
	if(do_encrypt)
	{
		cout<<"Encrypted text:"<<endl;

		// Iterating through all characters in the file.
		for(int i = 0; i < file_data.length(); i++)
		{
			// Check if character is an alphabet, print it directly if it isn't
			if(!isalpha(file_data[i]))
			{
				cout<<file_data[i];
				continue;
			}

			// Adding the key for the encryption
			char encpt_out = file_data[i] + (KEY_VAL % 26);

			// Rollover incase of value overflow
			while(encpt_out > 90)
				encpt_out -= 26;
			
			cout<<encpt_out;
		}
	}
	
	// Decryption
	else
	{
		cout<<"Decrypted text:"<<endl;

		// Iterating through all characters in the file.
		for(int i = 0; i < file_data.length(); i++)
		{
			// Check if character is an alphabet, print it directly if it isn't
			if(!isalpha(file_data[i]))
			{
				cout<<file_data[i];
				continue;
			}

			// Adding the key for the encryption
			char encpt_out = file_data[i] - (KEY_VAL % 26);

			// Rollover incase of value overflow
			while(encpt_out < 65)
				encpt_out += 26;
			
			cout<<encpt_out;
		}
	}
}

void vigenere(string file_data, int do_encrypt, string KEY)
{
	// Check for sus characters in KEY
	for(int i = 0; i < KEY.length(); i++)
		if(!isalpha(KEY[i]))
		{
			cout<<"Invalid key entered for Vigenère Cipher! Please go through README.md";
			exit(-1);
		}

	KEY = strToUpper(KEY);
	int key_track = 0;

	// Encryption
	if(do_encrypt)
	{
		cout<<"Encrypted text:"<<endl;

		// Iterating through all characters in the file.
		for(int i = 0; i < file_data.length(); i++)
		{
			// Check if character is an alphabet, print it directly if it isn't
			if(!isalpha(file_data[i]))
			{
				cout<<file_data[i];
				continue;
			}

			// Adding the key for the encryption
			char encpt_out = file_data[i] + (KEY[key_track % KEY.length()] % 26);

			// Rollover incase of value overflow
			while(encpt_out > 90)
				encpt_out -= 26;
			
			cout<<encpt_out;
		}
	}

	// Decryption
	else
	{
		cout<<"Decrypted text:"<<endl;

		// Iterating through all characters in the file.
		for(int i = 0; i < file_data.length(); i++)
		{
			// Check if character is an alphabet, print it directly if it isn't
			if(!isalpha(file_data[i]))
			{
				cout<<file_data[i];
				continue;
			}

			// Adding the key for the encryption
			char encpt_out = file_data[i] - (KEY[key_track % KEY.length()] % 26);

			// Rollover incase of value overflow
			while(encpt_out < 65)
				encpt_out += 26;
			
			cout<<encpt_out;
			key_track++;
		}
	}
}