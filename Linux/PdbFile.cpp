
/************************************************************************
* RSA 6.9.21
* Because we are using this from CGI scripts in python, the return value is everything from cout
************************************************************************/
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>

#include "PdbFile.h"
using namespace std;

PdbFile::PdbFile(string pdbCode, string directory)
{
	_pdbCode = pdbCode;
	string fileName = directory + "pdb" + pdbCode + ".ent";
	ifstream myfile(fileName.c_str());
	
	if (myfile.is_open())
	{
		string line = "";
		while (getline(myfile, line))
		{
			//Add HOH, ATOM and HETATOM for now
			int posHET = line.find("HETATM");
			int posATM = line.find("ATOM");
			int posHOH = line.find("HOH");

			if (posHET == 0 || posATM == 0 || posHOH == 0)
				_atoms.push_back(Atom(line));
		}
		myfile.close();
		_loaded = true;
	}
	
}

bool PdbFile::isLoaded()
{
	return _loaded;
}

string PdbFile::getPdbCode()
{
	return _pdbCode;
}

Atom* PdbFile::getNearest(double x, double y, double z)
{	
	return &_atoms[0];
}
