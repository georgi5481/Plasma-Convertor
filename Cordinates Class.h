#ifndef CORDINATES_DECLARATION
#define CORDINATES_DECLARATION

class Coordinates {
private:
	long double firstPointX;
	long double firstPointY;
	long double bulge;

	long double secondPointX;
	long double secondPointY;

public:
	Coordinates() :firstPointX(0), firstPointY(0), bulge(0), secondPointX(0), secondPointY(0) {
		std::cout << "\nThere has been an error. Please restart the program\n";
	}//the default constructor won't/shouldn't be called

	Coordinates(long double firstX, long double firstY, long double incomingBulge, long double secondX, long double secondY) :
		firstPointX(firstX), firstPointY(firstY), bulge(incomingBulge), secondPointX(secondX), secondPointY(secondY)
	{	}


	long double getFirstX() { return firstPointX; }
	long double getFirstY() { return firstPointY; }
	long double getBulge() { return bulge; }
	long double getSecondX() { return secondPointX; }
	long double getSecondY() { return secondPointY; }

};

#endif // !CORDINATES_DECLARATION
