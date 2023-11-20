/*
BAILEY DICKERSON
*/
#include <iostream>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <string>
using namespace std;



int main() {
	bool run = true;
	char userInput;
	string fileName;
	bool brake = false;

	while (run)
	{
		std::cout << "Please enter the filename: ";
		std::cin >> fileName;

		vector<vector<char>> arr;
		vector<string> inputs;
		int arraySize = 0;
		int numInputs = 0;
		bool wordIsCorrect = false;

		ifstream myfile;
		string line;
		myfile.open(fileName);

		if (myfile.is_open())
		{
			int counter = 0;
			string lineNoSpaces = "";
			int i = 0;
			int j = 0;

			// get n (size of array)
			getline(myfile, line);
			arraySize = stoi(line);
			counter++;

			vector<vector<char>> arr(arraySize, vector<char>(arraySize));

			while (getline(myfile, line))
			{
				// get characters for array
				if (counter > 0 && counter <= arraySize)
				{
					for (int k = 0; k < sizeof(line); k += 2)
					{
						lineNoSpaces += line[k];
					}

					for (int y = 0; y < arraySize; y++)
					{
						arr[j][i] = lineNoSpaces[y];

						i++;
					}

					j++;
					i = 0;
					lineNoSpaces = "";
				}

				// get number of inputs
				if (counter == (arraySize + 1))
				{
					numInputs = stoi(line);
				}

				// get inputs
				if (counter >= (arraySize + 2))
				{
					inputs.push_back(line);
				}

				counter++;
			}

			// scan for each of the hidden words...
			int character = 0;

			vector<int> xCoord(numInputs);
			vector<int> yCoord(numInputs);
			vector<string> direction(numInputs);

			// loop through each input
			for (int i = 0; i < numInputs; i++)
			{
				// loop through entire puzzle to check each input
				for (int y = 0; y < arraySize; y++)
				{
					for (int x = 0; x < arraySize; x++)
					{
						// find first letter
						if (arr[y][x] == inputs[i][character])
						{
							character++;

							// make sure we can check for length of input

							// N
							if (y >= inputs[i].size() - 1)
							{
								brake = false;
								for (int k = 1; k < inputs[i].size(); k++)
								{
									// if characters match we now have a direction
									if (arr[y - k][x] == inputs[i][character] && brake == false)
									{
										character++;

										// if we are on the last character, and the loop hasn't broken yet, then we good
										if (character == inputs[i].size())
										{
											xCoord[i] = x;
											yCoord[i] = y;
											direction[i] = "N";
											wordIsCorrect = true;
										}
									}
									// otherwise try again
									else
									{
										character = 1;
										brake = true;
									}
								}
							}
							// NE
							if (y >= inputs[i].size() - 1 && x <= arraySize - inputs[i].size())
							{
								brake = false;
								for (int k = 1; k < inputs[i].size(); k++)
								{
									if (arr[y - k][x + k] == inputs[i][character] && brake == false)
									{
										character++;

										if (character == inputs[i].size())
										{
											xCoord[i] = x;
											yCoord[i] = y;
											direction[i] = "NE";
											wordIsCorrect = true;
										}
									}
									else
									{
										character = 1;
										brake = true;
									}
								}
							}
							// E
							if (x <= arraySize - inputs[i].size())
							{
								brake = false;
								for (int k = 1; k < inputs[i].size(); k++)
								{
									if (arr[y][x + k] == inputs[i][character] && brake == false)
									{
										character++;

										if (character == inputs[i].size())
										{
											xCoord[i] = x;
											yCoord[i] = y;
											direction[i] = "E";
											wordIsCorrect = true;
										}
									}
									else
									{
										character = 1;
										brake = true;
									}
								}
							}
							// SE
							if (y <= arraySize - inputs[i].size() && x <= arraySize - inputs[i].size())
							{
								brake = false;
								for (int k = 1; k < inputs[i].size(); k++)
								{
									if (arr[y + k][x + k] == inputs[i][character] && brake == false)
									{
										character++;

										if (character == inputs[i].size())
										{
											xCoord[i] = x;
											yCoord[i] = y;
											direction[i] = "SE";
											wordIsCorrect = true;
										}
									}
									else
									{
										character = 1;
										brake = true;
									}
								}
							}
							// S
							if (y <= arraySize - inputs[i].size())
							{
								brake = false;
								for (int k = 1; k < inputs[i].size(); k++)
								{
									if (arr[y + k][x] == inputs[i][character] && brake == false)
									{
										character++;

										if (character == inputs[i].size())
										{
											xCoord[i] = x;
											yCoord[i] = y;
											direction[i] = "S";
											wordIsCorrect = true;
										}
									}
									else
									{
										character = 1;
										brake = true;
									}
								}
							}
							// SW
							if (y <= arraySize - inputs[i].size() && x >= inputs[i].size() - 1)
							{
								brake = false;
								for (int k = 1; k < inputs[i].size(); k++)
								{
									if (arr[y + k][x - k] == inputs[i][character] && brake == false)
									{
										character++;

										if (character == inputs[i].size())
										{
											xCoord[i] = x;
											yCoord[i] = y;
											direction[i] = "SW";
											wordIsCorrect = true;
										}
									}
									else
									{
										character = 1;
										brake = true;
									}
								}
							}
							// W
							if (x >= inputs[i].size() - 1)
							{
								brake = false;
								for (int k = 1; k < inputs[i].size(); k++)
								{
									if (arr[y][x - k] == inputs[i][character] && brake == false)
									{
										character++;

										if (character == inputs[i].size())
										{
											xCoord[i] = x;
											yCoord[i] = y;
											direction[i] = "W";
											wordIsCorrect = true;
										}
									}
									else
									{
										character = 1;
										brake = true;
									}
								}
							}
							// NW
							if (y >= inputs[i].size() - 1 && x >= inputs[i].size() - 1)
							{
								brake = false;
								for (int k = 1; k < inputs[i].size(); k++)
								{
									if (arr[y - k][x - k] == inputs[i][character] && brake == false)
									{
										character++;

										if (character == inputs[i].size())
										{
											xCoord[i] = x;
											yCoord[i] = y;
											direction[i] = "NW";
											wordIsCorrect = true;
										}
									}
									else
									{
										character = 1;
										brake = true;
									}
								}
							}
						}

						// Thought we found first letter, but we didn't. TRY AGAIN!!!
						character = 0;
					}
				}

				if (!wordIsCorrect)
				{
					xCoord[i] = -1;
					yCoord[i] = -1;
					direction[i] = "Z";
				}

				wordIsCorrect = false;
				character = 0;
			}

			// output
			std::cout << "WORD           LOC       DIR" << endl;
			std::cout << "----------------------------" << endl;
			for (int i = 0; i < inputs.size(); i++)
			{
				if (xCoord[i] > -1 && yCoord[i] > -1)
				{
					std::cout << inputs[i] << string(15 - inputs[i].size(), ' ') << yCoord[i] + 1 << string(3 - to_string(yCoord[i]).length(), ' ') << xCoord[i] + 1 << string(7 - to_string(xCoord[i]).length(), ' ') << direction[i] << endl;
				}
				else
				{
					std::cout << inputs[i] << string(15 - inputs[i].size(), ' ') << "NOT IN PUZZLE" << endl;
				}
			}


			myfile.close();
		}
		std::cout << "Run again? Y/N: ";
		std::cin >> userInput;

		if (userInput == 'Y' || userInput == 'y')
		{
			run = true;
			std::cout << endl;
		}
		else
		{
			run = false;
		}
	}

	return 0;
}