#include "FrequencyTable.h"

Table::Table() {
	_len = 0;
}

Table::~Table() {
	_a.clear();
}

bool Table::CheckAvailable(char c) {
	for (int i = 0; i < _a.size(); i++) {
		if (_a[i]._char == c) {
			return true;
		}
	}
	return false;
}

int Table::FindPos(char c) {
	for (int i = 0; i < _a.size(); i++) {
		if (_a[i]._char == c) {
			return i;
		}
	}
}

void Table::CreateTable() {
	string _name;
	cout << "Please input the name of the file: ";
	getline(cin, _name);
	ifstream _input(_name);

	if (_input.fail()) {
		cout << "Can't open this file" << endl;
		return;
	}


	while (!_input.eof()) {
		char* Buffer = new char;
		if (_input.read(Buffer, 1)) {
			_len++;
			if (CheckAvailable(*Buffer)) {
				int pos = FindPos(*Buffer);
				_a[pos]._freq++;
			}
			else {
				Frenquency tmp;
				tmp._char = *Buffer;
				tmp._freq = 1;
				_a.push_back(tmp);
			}
		}
		delete Buffer;
	}
	


	for (int i = 0; i < _a.size(); i++) {
		_a[i]._freq /= _len;
	}
	_input.close();
	
}

ostream& operator<<(ostream& out, const Table& p) {
	for (int i = 0; i < p._a.size(); i++) {
		out << p._a[i]._char << " " << p._a[i]._freq << endl;
	}
	return out;
}