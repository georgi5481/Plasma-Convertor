#include<fstream>
#include<string>
#include<ctype.h>
#include<vector>
#include<set>
#include<iostream>
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
			if (line == "AcDbPolyline" ) {	//when we catch up to the cordinates/place we want to work

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

void writingTheCNC(std::string& nameOfFile, int plasmaSpeed) {

	std::string thePath = "./CNC/" + nameOfFile + ".CNC";

	std::ofstream outputStream(thePath);
	outputStream << "\nN0G92X0Y0\nG91F" << plasmaSpeed;
	
	for (std::vector<Coordinates>::iterator i = polylineStorage.begin(); i != polylineStorage.end(); i++) {


		if (i == polylineStorage.begin()) {
			outputStream << "\nG00X" << turnIntoFourDigits(i->getFirstX()) << "Y" << turnIntoFourDigits(i->getFirstY()) << "\n/P86M98\n";

		}
		 if (i->getBulge() != 0 ) {
			std::pair<long double, long double> theCenter = i->getCenter();
			long double x = i->getSecondX() - i->getFirstX();
			long double y = i->getSecondY() - i->getFirstY();
			if (i != polylineStorage.begin() && (i - 1)->getSecondX() == i->getFirstX() && (i - 1)->getSecondY() == i->getFirstY()) {
				outputStream << "G03";
			}
			outputStream << "X" << turnIntoFourDigits(x) << "Y" << turnIntoFourDigits(y) <<
				"I" << turnIntoFourDigits(i->getSecondX() - theCenter.first) << "J" << turnIntoFourDigits(i->getSecondY() - theCenter.second) << std::endl;
		}

		

	}
	
	
	
	//	/ P86M98
	//	G03X0Y - 6000I4566J - 3000
	//	X - 49Y0I0J6000
	//	/ P95M98
	//	G00X - 30621Y - 27277
	//	/ P86M98
	//	G03X29437Y0I14718J - 8501
	//	/ P95M98
	//	M02


	outputStream.close();
}

int main()
{

	printf("Type \"HELP\"  for more information. \n\nPlease insert the name of the DXF file you want to convert: ");

	std::string nameOfFile("");
	std::getline(std::cin, nameOfFile);

	printf("Now please enter the desired working speed (default = 1000): ");
	std::string speedForPlasma("");
	std::getline(std::cin, speedForPlasma);
	int theSpeed(0);
	if (speedForPlasma == "") {
		theSpeed = 1000;
	}
	else if (checkForChars(speedForPlasma)) {
		theSpeed = stoi(speedForPlasma);
	}
	else {
		std::cout << "There has been an error with putting the speed, please retart the program.\n";
	}
	
	

	if (nameOfFile != "Help" && nameOfFile != "HELP" && nameOfFile != "help") {
		//Checking if the user wants more information about the program

		readingTheDXF(nameOfFile);	//calling the function for reading the file 

		writingTheCNC(nameOfFile, theSpeed);
	}
	else {

		std::cout << "the help section";
	}
   

}

