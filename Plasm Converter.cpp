#include <iostream>
#include<fstream>
#include<string>
#include<ctype.h>
#include<vector>
#include<set>
#include "Cordinates Class.h"


std::vector<Coordinates> polylineStorage;


bool checkForChars(std::string& line) {		//check the word if there is some unwanted char

	for (unsigned int i = 0; i != line.length(); i++) {
		if (!(isdigit(line[i]) || line[i] == '.' || line[i] == ' ')) {
			return false;
		}
	}
	return true;
}

void recordingTheCordinates(std::ifstream& loadedStream, std::string& line) {

	std::getline(loadedStream, line);

	long double firstX(0), firstY(0), buldge(0), secondX(0), secondY(0);	//going to use them temporary for storing the data and then use them for making an object

	for (int i = 0; checkForChars(line) ; std::getline(loadedStream, line))
	{	 //until we get all the cordinates

		long double theTopLine = std::stold(line);

		if (theTopLine == 10 || theTopLine == 20 || theTopLine == 42) {	//The upper line signalise (10 = X cordinate, 20 = Y, 42 = buldge)
			std::getline(loadedStream, line); //reading the next line to store the number
			

			if (theTopLine == 10 && (i % 2 == 0)) {		//checking if it's the first one or second point cordinates
				firstX = std::stold(line);
				std::cout << "\nThe first cordinate X is     " << firstX << std::endl;
				i++;
			}
			else if(theTopLine == 10 && (i % 2 == 1)) {
				secondX = std::stold(line);
				std::cout << "\nThe second cordinate X is     " << secondX << std::endl;
				i++;
			}
			else if (theTopLine == 20 && (i % 2 == 1)) {	//every cordinate has 2 points, this is why the logic is inverted with i integer
				firstY = std::stold(line);
				std::cout << "\nThe first cordinate Y is     " << firstY << std::endl;
			}
			else if (theTopLine == 20 && (i % 2 == 0)) {
				secondY = std::stold(line);
				std::cout << "\nThe second cordinate Y is     " << secondY << std::endl;
			}
			else {
				buldge = std::stold(line);
				std::cout << "\nThe Buldge is      " << buldge << std::endl;
				
			}
		}

		if (firstX != 0 && firstY != 0 && secondX != 0 && secondY != 0) {
			Coordinates recordedCordinates(firstX, firstY, buldge, secondX, secondY);

			polylineStorage.push_back(recordedCordinates);

			firstX = secondX;		//since the polyline uses the old cordinates again
			firstY = secondY;
			buldge = 0;		//to prevent opening the if state
			secondX = 0;
			secondY = 0;

			i++;	//cuz we are skipping the first cordinates next time

			std::cout << "\nworks\n";

		}

	}
}




void readingTheDXF(std::string& nameOfFile) {


	std::ifstream loadedStream;
	loadedStream.open("./DXF/" + nameOfFile + ".dxf");

	if (loadedStream.is_open()) { //Checks if the file was loaded successfully 

		std::string line("");
		while (std::getline(loadedStream, line))	//reading every line and putting it into the helping string
		{
			if (line == "AcDbPolyline") {	//when we catch up to the cordinates/place we want to work

				recordingTheCordinates(loadedStream, line);
			}

		}
		std::cout << "\n The conversion to .CNC file was successful. " << '\n';
		loadedStream.close();
	}
	else {
		std::cout << "There has been a problem with loading the file. Please restart the coonvertor." << std::endl
			<< "If this doesn't help, see if there is a problem in the file itself.";
	}
}



int main()
{

	printf("Type \"HELP\"  for more information. \n\nPlease insert the name of the DXF file you want to convert: ");

	std::string nameOfFile("");
	std::getline(std::cin, nameOfFile);
	
	

	if (nameOfFile != "Help" && nameOfFile != "HELP" && nameOfFile != "help") {
		//Checking if the user wants more information about the program

		readingTheDXF(nameOfFile);	//calling the function for reading the file 

		writingTheCNC(nameOfFile);
	}
	else {

		std::cout << "the help section";
	}
   

}

