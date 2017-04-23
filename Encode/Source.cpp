// Jedidiah Fowler
/* Project to take a written message and encode it into
	decimal -> excess-3 -> gray code -> hamming code */

#include<iostream>
#include<fstream>
#include<string>

using namespace std;

int main()
{
	// VARIABLES
	const int MAX = 12;
	ifstream inFile;
	ofstream outFile;
	string input, output;
	int Code[MAX];
	int C2[MAX];
	char x;
	int y, c, count;

	/************************************************
	MAIN PROGRAM
	************************************************/
	// ask user for file to be encoded
	cout << "Please enter the file name you wish to";
	cout << " be encoded.  Include the file ";
	cout << "extension." << endl;
	cout << ":  ";
	cin >> input;

	// open file to be encoded
	inFile.open(input);
	// test to see if file was openned
	if (!inFile)
	{
		cout << "Error.  File not found.";
		return 1;
	}
	cout << "File found and open for encoding.\n\n";

	size_t lastindex = input.find_last_of(".");
	output = input.substr(0, lastindex);

	cout << output << endl;
	// create file named based on input file
	output = output + "coded.dat";
	// open file for writing
	outFile.open(output);

	/************************************************
	PARSE DATA WITH A WHILE LOOP
	************************************************/
	// count the chars in file
	count = 0;
	while (inFile)
	{
		inFile.get(x);
		count = count + 1;
	}
	count = count - 1;

	inFile.close();
	inFile.open(input);

	// loop to do just the chars we need encoded
	for (int j = 0; j < count; j++)
	{
		// get first char to encode
		inFile.get(x);
		//cout << x << endl;

		// cast the ascii char as an int
		y = (int)x;
		//cout << y << endl;
		
		/********************************************
		CONVERT INT TO E3 THEN BINARY
		********************************************/
		// add 3 for E3
		y = y + 3;
		if (y - 128 > -1)
		{
			Code[0] = 1;
			y = y - 128;
		}
		else
		{
			Code[0] = 0;
		}
		if (y - 64 > -1)
		{
			Code[1] = 1;
			y = y - 64;
		}
		else
		{
			Code[1] = 0;
		}
		if (y - 32 > -1)
		{
			Code[2] = 1;
			y = y - 32;
		}
		else
		{
			Code[2] = 0;
		}
		if (y - 16 > -1)
		{
			Code[3] = 1;
			y = y - 16;
		}
		else
		{
			Code[3] = 0;
		}
		if (y - 8 > -1)
		{
			Code[4] = 1;
			y = y - 8;
		}
		else
		{
			Code[4] = 0;
		}
		if (y - 4 > -1)
		{
			Code[5] = 1;
			y = y - 4;
		}
		else
		{
			Code[5] = 0;
		}
		if (y - 2 > -1)
		{
			Code[6] = 1;
			y = y - 2;
		}
		else
		{
			Code[6] = 0;
		}
		if (y - 1 > -1)
		{
			Code[7] = 1;
			y = y - 1;
		}
		else
		{
			Code[7] = 0;
		}

		/* debug
		cout << x << " in Binary is:" << endl;
		for (int i = 0; i < 8; i++)
		{

			cout << Code[i];
		}
		cout << endl;*/

		/********************************************
		CONVERT E3 TO GRAY CODE
		********************************************/
		C2[0] = Code[0];
		for (int i = 0; i < 7; i++)
		{
			// XOR bits to obtain Excess-3 from Gray
			if (Code[i] == Code[i + 1])
			{
				C2[i + 1] = 0;
			}
			else
			{
				C2[i + 1] = 1;
			}
		}

		/* debug
		cout << x << " in Gray Code is:" << endl;
		for (int i = 0; i < 8; i++)
		{

			cout << C2[i];
		}
		cout << endl;*/

		/********************************************
		CONVERT GRAY TO HAMMING CODE
		********************************************/
		// move bits to make room for parity bits
		for (int i = 4; i < 8; i++)
		{
			C2[i + 4] = C2[i];
		}
		for (int i = 1; i < 4; i++)
		{
			C2[i + 3] = C2[i];
		}
		C2[2] = C2[0];

		c = 0;
		// set parity bit 1
		for (int i = 2; i < 12; i = i + 2)
		{
			if (C2[i] == 1)
				c = c + 1;
		}
		if (c % 2 == 0)
			C2[0] = 0;
		else
			C2[0] = 1;
		
		c = 0;
		// set parity bit 2
		if (C2[2] == 1)
			c = c + 1;
		if (C2[5] == 1)
			c = c + 1;
		if (C2[6] == 1)
			c = c + 1;
		if (C2[9] == 1)
			c = c + 1;
		if (C2[10] == 1)
			c = c + 1;
		if (c % 2 == 0)
			C2[1] = 0;
		else
			C2[1] = 1;

		c = 0;
		// set parity bit 4
		if (C2[4] == 1)
			c = c + 1;
		if (C2[5] == 1)
			c = c + 1;
		if (C2[6] == 1)
			c = c + 1;
		if (C2[11] == 1)
			c = c + 1;
		if (c % 2 == 0)
			C2[3] = 0;
		else
			C2[3] = 1;

		c = 0;
		// set parity bit 8
		for (int i = 8; i < 12; i++)
		{
			if (C2[i] == 1)
				c = c + 1;
		}
		if (c % 2 == 0)
			C2[7] = 0;
		else
			C2[7] = 1;

		/* debug
		cout << "Hamming: " << endl;
		for (int i = 0; i < 12; i++)
		{
			cout << C2[i];
		}
		cout << endl;*/

		// loop to write 1 code per line in the file
		for (int i = 0; i < 12; i++)
		{
			cout << C2[i];
		}
		cout << endl;

		for (int i = 0; i < 12; i++)
		{
			outFile << C2[i];
		}
		outFile << endl;
	}



	inFile.close();
	outFile.close();

	// END PROGRAM
	return 0;
}