// TestMatrixSaveLoad.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"

#include "matrix4x4f.h"
#include <fstream>
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
	matrix4x4f m, n, p, q, r;
	n.translate(vector3f(1,2,4));
	m.rotate(45, vector3f(1,2,4));
	p = m+n*2;

	ofstream ff("test.txt");
	ff<<p<<endl;
	ff<<m<<endl;
	ff<<n<<endl;

	cout << "Matrix p:" << endl << p << endl;
	cout << "Matrix m:" << endl << m << endl;
	ff.close();

	ifstream ifs("test.txt");
	ifs>>q;
	ifs>>r;

	cout << "Matrix q:" << endl << q << endl;
	cout << "Matrix r:" << endl << r << endl;

	return 0;
}

