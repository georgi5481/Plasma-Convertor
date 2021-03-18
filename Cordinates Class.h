#ifndef CORDINATES_DECLARATION
#define CORDINATES_DECLARATION


class Coordinates {
private:
	long double firstPointX;
	long double firstPointY;
	long double bulge;

	long double secondPointX;
	long double secondPointY;

	long double distanceBetweenPoints;

	long double centerCircleX;
	long double centerCircleY;

public:
	Coordinates() :firstPointX(0), firstPointY(0), bulge(0), secondPointX(0), secondPointY(0), distanceBetweenPoints(0), centerCircleX(0),
		centerCircleY(0) {
		std::cout << "\nThere has been an error. Please restart the program\n";
	}//the default constructor won't/shouldn't be called

	Coordinates(long double firstX, long double firstY, long double incomingBulge, long double secondX, long double secondY) :
		firstPointX(firstX), firstPointY(firstY), bulge(incomingBulge), secondPointX(secondX), secondPointY(secondY),
		centerCircleX(0), centerCircleY(0)
	{	
		distanceBetweenPoints = sqrt(pow((this->secondPointX - this->firstPointX), 2) + pow((this->secondPointY - this->firstPointY), 2));
		//calculating the distance
		std::cout << "\n the distance is : " << distanceBetweenPoints;
	}


	long double getFirstX()	 { return firstPointX; }
	long double getFirstY()	 { return firstPointY; }
	long double getBulge()	 { return bulge; }
	long double getSecondX() { return secondPointX; }
	long double getSecondY() { return secondPointY; }

	std::pair<long double,long double> getCenter() {

		if (this->bulge != 0) {

			long double saditta = (distanceBetweenPoints / 2);		//calculating the lengths
			long double radius = (saditta * (pow(this->bulge, 2) + 1)) / (2 * this->bulge);

			long double directionX = ((secondPointX - firstPointX) / distanceBetweenPoints);
			long double directionY = ((secondPointY - firstPointY) / distanceBetweenPoints);

			long double centerX = (directionY * distanceBetweenPoints) + ((firstPointX + secondPointX) / 2);
			long double centerY = ((directionX) * distanceBetweenPoints) + ((firstPointY + secondPointY) / 2);
			
			std::pair<long double, long double> bothCenters(centerX, centerY);
			return bothCenters;		
		}
		else {
			std::cout << "\nThere has been an error with calculating the center point of the arc.\n";
			std::pair<long double, long double> bothCenters(0, 0);
			return bothCenters;
		}

	}

	friend int turnIntoFourDigits(long double&);

};
int turnIntoFourDigits(long double theDouble) {
	// stored as 54.999999...
	theDouble = theDouble * 1000; // x is now 55499.999...
	int y = (int)theDouble; // truncated to 55499
	return y;
}
#endif // !CORDINATES_DECLARATION
