/*
Joseph Brinton
Group 9 Lab #2
CS 3310 Section 001
*/

#define _SCL_SECURE_NO_WARNINGS 

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <dos.h>
#include <iomanip>
#include <vector>
#include <algorithm>      
#include <random>

using namespace std;
using std::setw;

int basic_operations = 0;
int optimal = 0;
std::string s, s2,t,t2,d,d2;
int m, n;

std::vector<std::vector<int>> matrix;

//dynamic algorithm
void dynamic(int i, int j) {
	int penalty = 0;
	m = i;
	n = j;
	matrix.resize(m+1);
	for (int k = 0; k <= m; k++)
		matrix[k].resize(n+1);
	for (i = m; i >=0; i--) {
		for (j=n; j>= 0; j--) {
			basic_operations++;
			if (i == m) // basic operation
				matrix[i][j] = 2 * (n - j);
			else if (j == n)
				matrix[i][j] = 2 * (m - i);
			else {
				if (s[i] == s2[j])
					penalty = 0;
				else
					penalty = 1;
				matrix[i][j] = min({ matrix[i + 1][j + 1] + penalty, matrix[i + 1][j] + 2, matrix[i][j + 1] + 2 });
			}
		}
	}
	int ioffset = 0;
	int	joffset=0;

	for (int i = 0, j = 0; i < m&&j < n; i++, j++) {

		if ((matrix[i][j] == matrix[i + 1][j + 1] && s[i] == s2[j]) || (matrix[i][j] == matrix[i + 1][j + 1] + 1)) {
		}
		else if (matrix[i][j] == matrix[i][j + 1] + 2) {
			t.insert(i+ ioffset, " ");
			ioffset++;
			i--;

		}
		else if (matrix[i][j] == matrix[i + 1][j] + 2) {
			t2.insert(j+ joffset, " ");
			joffset++;
			j--;

		}
	}
}

//recursion
int divide(int i, int j) {
	int penalty;
	basic_operations++;
	if (i == m) { // basic operation
		optimal = 2 * (n - j);
	}
	else if (j == n) {
		optimal = 2 * (m - i);
	}
	else {
		if (s[i] == s2[j])
			penalty = 0;
		else
			penalty = 1;
		optimal = min({ divide(i + 1, j + 1) + penalty, divide(i + 1, j) + 2, divide(i, j + 1) + 2 });
	}
	return optimal;
} 
//calls recursive function
void conquer() {
	int ioffset = 0;
	int	joffset = 0;
	for (int i = 0, j = 0; i < m&&j < n;i++,j++) {
		
		if ((divide(i, j) == divide(i + 1, j + 1) && s[i] == s2[j])|| (divide(i, j) == divide(i + 1, j + 1)+1 )){
		}
		else if (divide(i, j) == (divide(i, j + 1) + 2)) {
			d.insert(i+ ioffset, " ");
			ioffset;
			i--;
		}
		else if (divide(i, j) == (divide(i + 1, j) + 2)) {
			d2.insert(j+ joffset, " ");
			joffset;
			j--;
		}
	}
}

// Random string generator
void stringGen(double size, std::string& s) {
	int v1 = 0;
	for (int i = 0; i < size; i++) {
		v1 = rand() % 4;
		if (v1 == 0)
			s += 'A';
		else if(v1 == 1)
			s += 'G';
		else if (v1 == 2)
			s += 'C';
		else if (v1 == 3)
			s += 'T';
	}
}
//mutates string
void mutate(std::string& s) {
	int v1 = 0;
	long int z = s.length();
	for (size_t i = 0;i<z&&i< s.length(); i++) {
		
		v1 = rand() % 20;
		if (v1 == 0)
			s.replace(i,1, "A");
		else if (v1 == 1)
			s.replace(i, 1,"G");
		else if (v1 == 2)
			s.replace(i, 1,"C");
		else if (v1 == 3)
			s.replace(i,1, "T");
		else if (v1 == 4)
			s.insert(i, "A");
		else if (v1 == 5)
			s.insert(i, "G");
		else if (v1 == 6)
			s.insert(i, "C");
		else if (v1 == 7)
			s.insert(i,"T");
		else if (v1 >= 8 &&v1<12)
			s.erase(i,1);
	}

}

int main()
{
	while (true) {
		
		int exp;

		int count = 0;
		cout << "Enter an exponent that will determine the size of the DNA sequence: ";
		cin >> exp;
		while (!cin || exp<0) {
			cin.clear();
			cin.ignore();
			cout << "Input invalid. Enter an exponent that will determine the size of the DNA sequence: ";
			cin >> exp;
		}

		double size = pow(2, exp);

		stringGen(size, s);

		count = (int)size;
		s2 = s;
		
		cout <<"Original Sequence: "<< s << endl;
		mutate(s2);
		cout << "Mutation Sequence: " << s2 << endl;

		t = s;
		t2 = s2;
		d = s;
		d2 = s2;

		cout << setw(11) << std::left << "Alignment" << setw(11) << std::left << "Number" << setw(11) << std::left << "Time" << setw(11) << std::left << "Basic" << endl;
		cout << setw(11) << std::left << "Algorithm" << setw(11) << std::left << "Items (n)" << setw(11) << std::left << "Elapsed" << setw(11) << std::left << "Operations" << endl;

		clock_t start;
		clock_t end;
		clock_t elapsed_clock;
		clock_t elapsed_time;


		m = s.length();
		n = s2.length();
		start = clock();

		dynamic(m, n);

		end = clock();
		elapsed_clock = end - start;
		elapsed_time = ((end - start) / (CLK_TCK));

		
		cout << setw(11) << "Dynamic" << setw(11) << count << setw(11) << elapsed_clock << setw(11) << basic_operations << endl;

		//reset global variables
		basic_operations = 0;
		optimal = 0;
		start = 0;
		end = 0;
		elapsed_clock = 0;
		elapsed_time = 0;
		m = s.length();
		n = s2.length();
		
		
		start = clock();
		
		conquer();

		end = clock();
		elapsed_clock = end - start;
		elapsed_time = ((end - start) / (CLK_TCK));

		cout << setw(11) << "Divide" << setw(11) << count << setw(11) << elapsed_clock << setw(11) << basic_operations << endl;
		cout << "Dynamic Alignment:" << endl;
		cout << t << endl;
		cout << t2 << endl;
		cout << "Divide and Conquer Alignment:" << endl;
		cout << d << endl;
		cout << d2 << endl;

		//reset stats
		basic_operations = 0;

		s.clear();
		s2.clear();
		d.clear();
		d2.clear();
		t.clear();
		t2.clear();

	}

}

