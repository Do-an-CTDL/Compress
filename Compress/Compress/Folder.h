
#include "Huffman.h"
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <vector>
#include <fstream>
#include <iostream>

class Folder : public Huffman{

	string _nameFolder;
	vector <string> _name;
	vector < vector <Huffman*> >  _buff;
	vector <vector <char> > _data;

public:

	Folder();

	void Input(bool);
	vector <string> GetNameFolder(string);
	void EncodeFolder();
	void DecodeFolder();
	//void Output();

	~Folder() = default;
};


