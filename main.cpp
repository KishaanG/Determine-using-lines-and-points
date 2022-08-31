/*
	Author: Kishaan G.
	Description: Structures assignment with lines and points.
	Last modified: June 9, 2022.
*/

// ============= Pre-processor commmands =============

#include <iostream>
#include <cmath>
using namespace std;

// ==================== Structures ====================

struct Point
{
	double xCoord;
	double yCoord;
};

struct Line
{
	double slope;
	double yInt;
};

// ==================== Prototypes ====================

void keyToContinue();
double getDouble(string);
int menu(string, string[], int, string);

void getPoints(Point &, Point &);
void getLines(Line &, Line &);

void displayLine(Line);
void displayPoint(Point);

void initLine(double, double, Line &);
void initPoint(double, double, Point &);

double getSlope(Point, Point);
double getYIntercept(double, Point);

Line getLine(Point, Point);
Point determinePOI(Line, Line);

void mainInterface();

// ==================== Definitions ====================

// =======================

void keyToContinue()
{
	cin.ignore();
	cout << "Type any key to continue..." << endl;
	getchar();
	return;
}

// =======================

double getDouble(string prompt)
{
	double response;
	cout << prompt << endl;
	cin >> response;
	return response;	
}

// =======================

int menu(string prompt, string options[], int numberOfOptions, string errorMsg)
{
	int response;
	do
	{
		cout << prompt << endl;
		for(int i = 0; i < numberOfOptions; i++)
		{
			for(int j = 0; j < i; j++)
			{ // This just makes the menu look nice by making every line one indent further than the previous. 
				cout << "	";
			}
			cout << i+1 << ") " << options[i] << endl;
		}
		cin >> response;
		if(response < 1 or response > numberOfOptions)
		{
			cout << errorMsg << endl;
			keyToContinue();
			system("clear");
		}
	}while (response < 1 or response > numberOfOptions);
	return response;
}

// =======================

void getPoints(Point & _point1, Point & _point2)
{
	double point1xCoord = getDouble("What would you like to be the x coordinate of the first point.");
	system("clear"); // Gets the x and y coordinates of the two points.
	
	double point1yCoord = getDouble("What would you like to be the y coordinate of the first point.");
	system("clear");
	
	double point2xCoord = getDouble("What would you like to be the x coordinate of the second point.");
	system("clear");
	
	double point2yCoord = getDouble("What would you like to be the y coordinate of the second point.");
	system("clear");

	initPoint(point1xCoord, point1yCoord, _point1); // Initializes the points with the values. 
	initPoint(point2xCoord, point2yCoord, _point2);
	return;
}

// =======================

void getLines(Line & _line1, Line & _line2)
{
	double line1Slope = getDouble("What would you like to be the slope of the first line.");
	system("clear"); // Gets the values of the parts of the lines.
	
	double line1YInt = getDouble("What would you like to be the y-intercept of the first line.");
	system("clear");
	
	double line2Slope = getDouble("What would you like to be the slope of the second line.");
	system("clear");
	
	double line2YInt = getDouble("What would you like to be the y-intercept of the second line.");
	system("clear");

	initLine(line1Slope, line1YInt, _line1); // Initializes the lines with the values given by the user.
	initLine(line2Slope, line2YInt, _line2);
	return;
}

// =======================

void displayLine(Line line)
{
	if(line.yInt == 0)
	{
		cout << "y = " << line.slope << "x";  // If the y intercept is 0, you do not need to display + 0.
	}
	else if (line.yInt < 0)
	{
		cout << "y = " << line.slope << "x - " << -1 * line.yInt; // If the y intercept is negative, you do not need to display + -yInt, instead display - yInt.
	}
	else if(line.slope == 0)
	{
		cout << "y = " << line.yInt; // If the slope is 0, you do not need to display the slope.
	}
	else cout << "y = " << line.slope << "x + " << line.yInt; // Otherwise, display the slope and y intercept in standard y = mx + b form. 
	return;
}

// =======================

void displayPoint(Point point)
{
	cout << "(" << point.xCoord << ", " << point.yCoord << ")"; // This displays a point.
	return;
}

// =======================

void initLine(double slope, double yInt, Line & _line)
{
	_line.slope = slope; // Sets the values given into a line.
	_line.yInt = yInt;
	return;
}

// =======================

void initPoint(double xCoord, double yCoord, Point & _point)
{
	_point.xCoord = xCoord; // Sets the parts of a point with the values given.
	_point.yCoord = yCoord;
	return;
}

// =======================

double getSlope(Point _point1, Point _point2)
{
	if(_point1.yCoord == _point2.yCoord)
	{ // If the y coordinate is not changing, the slope is 0.
		return 0;
	}
	else if(_point1.xCoord == _point2.xCoord)
	{ // If the slope is infinity, it is a vertical line, which returns an error.
		return INFINITY;
	}
	return (_point2.yCoord - _point1.yCoord) / (_point2.xCoord - _point1.xCoord); // Uses the slope formula to determine the slope of the given points.
}

// =======================

double getYIntercept(double _slope, Point _point)
{
	return _point.yCoord - (_slope * _point.xCoord); // Calculates the y intercept.
}

// =======================

Line getLine(Point point1, Point point2)
{
	Line line;
	double yInt = 0;
	double slope = 0;
	
	if(point1.xCoord == point2.xCoord and point1.yCoord == point2.yCoord)
	{ // If the points are identical, there is an error.
		yInt = INFINITY;
		slope = INFINITY;
	}
	else
	{
		slope = getSlope(point1, point2); // Gets the slope that goes through the two points.
		if(slope == INFINITY)
		{ // If the line is vertical, there is an error.
			slope = INFINITY;
			yInt = 404;
		}
		else yInt = getYIntercept(slope, point1); // Gets the y intercept.
	}
	initLine(slope, yInt, line);
	return line;
}

// =======================

Point determinePOI(Line line1, Line line2)
{
	Point POI;
	double xCoord = 0;
	double yCoord = 0;
	if(line1.slope == line2.slope)
	{ // If the lines are parallel, it is an error. 
		xCoord = INFINITY;
		yCoord = INFINITY;
	}
	else
	{ // Calculates the point of intersection of two lines.
		xCoord = ((line1.yInt - line2.yInt) / (line1.slope - line2.slope))*-1;
		yCoord = (line1.slope * xCoord) + line1.yInt;
	}
	initPoint(xCoord, yCoord, POI);  // Initializes the point of intersection.
	return POI;
}

// =======================

void mainInterface()
{
	Point point1;
	Point point2;
	Line lineAnswer;
	Line line1;
	Line line2;
	Point POI;

	string prompt = "What what you like to do: ";
	string menuOptions[3] = {"Get the line that passes through 2 points.", "Get the point of intersection of two lines.", "Quit."};
	string errorMsg = "Please type either 1, 2, or 3.";
	
	int userMenuChoice = 0;
	do
	{
		userMenuChoice = menu(prompt, menuOptions, 3, errorMsg); // Gets the user's choice of what action to perform.
		system("clear");
		switch(userMenuChoice)
		{
			case 1:
				getPoints(point1, point2);
				cout << "The line that passes through the points ";
				displayPoint(point1);
				cout << " and ";
				displayPoint(point2);
				cout << " is ";
				lineAnswer = getLine(point1, point2);
				displayLine(lineAnswer);
				cout << endl;
				keyToContinue();
				system("clear");
				break;

			case 2:
				getLines(line1, line2);
				cout << "The lines ";
				displayLine(line1);
				cout << " and ";
				displayLine(line2);
				cout << " intersect at ";
				POI = determinePOI(line1, line2);
				displayPoint(POI);
				cout << endl;
				keyToContinue();
				system("clear");
				break;

			case 3: // Quit option.
				break;
		}
	}while(userMenuChoice != 3);	
	return;
}

// =======================
	
int main()
{
	mainInterface();
	return 0;
}
