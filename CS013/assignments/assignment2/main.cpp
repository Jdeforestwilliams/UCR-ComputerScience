// Course: CS 13 
//
// First Name: Joshua 
// Last Name: DeForest-Williams
// ILearn username: jdefo002
//
// Lecture Section: 001
// Lab Section: 022 
// TA: Byung Hyung Kim
//
// Assignment: Programming Assignment 2
//
// I hereby certify that the code in this file
// is ENTIRELY my own original work.
//
// =====================================================
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;
const int ROWS = 6.0;
const int COLS = 8.0;
void initialize( double grid[ROWS][COLS], double top, double right, double bottom,
	double left)
{
	for (int i = 1; i < COLS-1; i++)
	{
		grid[0][i]= top; 
	}
	for (int i = 1; i < ROWS-1; i++)
	{
		grid[i][COLS-1]= right; 
	}
	for (int i = 1; i < COLS-1; i++)
	{
		grid[ROWS-1][i]= bottom; 
	}
	for (int i = 1; i < ROWS-1; i++)
	{
		grid[i][0]= left; 
	}
	for (int i = 1; i < ROWS-2; i++)
	{
		for (int j =1; j < COLS-2; j++)
		{
			grid[i][j] = 0; 
		}
		
	}
	
}
double average ( double grid[ROWS][COLS], double &largest )
{
	for (int i = 1; i < ROWS-1; i++)
	{
		for (int j = 1; j < COLS-1; j++)
		{
			grid[i][j] = (((grid[i-1][j]) + (grid[i+1][j]) + (grid[i][j-1])
				+ (grid[i][j+1])))/4;
			if (largest < grid[i][j])
			{
				largest = grid[i][j]-largest;
			}
		}
	}
	return largest; 
}
int main()
{
	cout << "Enter initial temperatures (top, right, bottom, left): " ; 
	double top;
	double right; 
	double bottom;
	double left;
	cin >> top >> right >> bottom >> left ;
	cout << "Enter tolerance for equilibrium: ";
	double tolerance;
	cin >> tolerance; 
	double grid[ROWS][COLS];
	initialize(grid, top, right, bottom, left);
	double largest = 0.0;
	average(grid,largest);
	while (largest > tolerance)
	{
		average(grid,largest);
	}
	
	
	// to output grid after averaged 
	cout << "Equilibrium Values: " << endl; 
	for (int i = 1; i < ROWS-1; i++)
	{
		for (int j =1; j < COLS-1; j++)
		{
			cout << fixed << setprecision (4) << setw(9) << grid[i][j] << " " ;
		}
		cout << endl; 
	}		
}
