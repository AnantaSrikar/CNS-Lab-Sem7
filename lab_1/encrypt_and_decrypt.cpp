/*
	Code to encrypt and decrypt text using the following ciphers
		- Caesar's
		- Vigenere
		- Playfair

	Author: Srikar
*/

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

	if(!(alg_choice >= 0 && alg_choice <= 2))
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
	void playfair(string, int, string);
	string strToUpper(string);

	file_data =  strToUpper(file_data);

	switch(alg_choice)
	{
		case 0:
				caesar(file_data, do_encrypt, KEY);
				break;

		case 1:
				vigenere(file_data, do_encrypt, KEY);
				break;

		case 2:
				playfair(file_data, do_encrypt, KEY);
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
	if(!do_encrypt)
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
	if(!do_encrypt)
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

// Function to check if a character is in the matrix
int inMatrix(char matrix[5][5], char findChar)
{
	for(int i = 0; i < 5; i++)
		for(int j = 0; j < 5; j++)
			if(findChar == matrix[i][j] || (findChar == 'I' && matrix[i][j] == 'J') || (findChar == 'J' && matrix[i][j] == 'I'))	// Weird edge case for the cipher
			{
				// cout<<"Found "<<findChar<<endl;
				return 1;
			}

	return 0;
}

void playfair(string file_data, int do_encrypt, string KEY)
{
	// Check for sus characters in KEY
	for(int i = 0; i < KEY.length(); i++)
	if(!isalpha(KEY[i]))
		{
			cout<<"Invalid key entered for Playfair Cipher! Please go through README.md";
			exit(-1);
		}

	KEY = strToUpper(KEY);

	cout<<KEY<<endl;
	
	char KEY_TABLE[5][5];

	for(int i = 0; i < 5; i ++)
		for(int j = 0; j < 5; j++)
			KEY_TABLE[i][j] = '1';


	int key_track = 0;

	for(int i = 0; i < 5; i++)
		for(int j = 0; j < 5; j++)
		{
			// Fill key_table with key characters
			if(key_track < KEY.length())
			{
				// Skip character if already in matrix
				while(inMatrix(KEY_TABLE, KEY[key_track]))
					if(key_track < KEY.length())
						key_track++;
					else
						break;

				if(key_track < KEY.length())
					KEY_TABLE[i][j] = KEY[key_track++];
				else
					goto REST_OF_THE_CHARS;
			}

			// Fill with rest of the alphabets
			else
			{
				REST_OF_THE_CHARS:
				for(char ch = 'A'; ch <= 'Z'; ch++)
					if(inMatrix(KEY_TABLE, ch))
						continue;
					else
					{
						KEY_TABLE[i][j] = ch;
						break;
					}
			}
		}

	for(int i = 0; i < 5; i++)
	{
		for(int j = 0; j < 5; j++)
			cout<<KEY_TABLE[i][j]<<"\t";
		cout<<endl;
	}

	// Encryption
	// if(!do_encrypt)
	// {
	// 	cout<<"Encrypted text:"<<endl;

	// 	// Iterating through all characters in the file.
	// 	for(int i = 0; i < file_data.length(); i++)
	// 	{
	// 		// Check if character is an alphabet, print it directly if it isn't
	// 		if(!isalpha(file_data[i]))
	// 		{
	// 			cout<<file_data[i];
	// 			continue;
	// 		}

	// 		// Adding the key for the encryption
	// 		char encpt_out = file_data[i] + (KEY[key_track % KEY.length()] % 26);

	// 		// Rollover incase of value overflow
	// 		while(encpt_out > 90)
	// 			encpt_out -= 26;
			
	// 		cout<<encpt_out;
	// 	}
	// }

	// // Decryption
	// else
	// {
	// 	cout<<"Decrypted text:"<<endl;

	// 	// Iterating through all characters in the file.
	// 	for(int i = 0; i < file_data.length(); i++)
	// 	{
	// 		// Check if character is an alphabet, print it directly if it isn't
	// 		if(!isalpha(file_data[i]))
	// 		{
	// 			cout<<file_data[i];
	// 			continue;
	// 		}

	// 		// Adding the key for the encryption
	// 		char encpt_out = file_data[i] - (KEY[key_track % KEY.length()] % 26);

	// 		// Rollover incase of value overflow
	// 		while(encpt_out < 65)
	// 			encpt_out += 26;
			
	// 		cout<<encpt_out;
	// 		key_track++;
	// 	}
	// }
}