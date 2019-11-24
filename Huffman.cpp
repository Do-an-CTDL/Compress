#include "Huffman.h"


Huffman::Huffman() {
	_left = NULL;
	_right = NULL;
}

Huffman::Huffman(char c) {
	_char = c;
	_frq = 1;
	_left = NULL;
	_right = NULL;
}

Huffman::~Huffman() {
	delete _left;
	delete _right;
}

char Huffman::GetChar() const {
	return _char;
}

string Huffman::GetCode() const {
	return _code;
}

int Huffman::GetFreq() const {
	return _frq;
}

bool Huffman::IsAvailable(char c, vector <Huffman*> _arr) {
	for (int i = 0; i < _arr.size(); i++) {
		if (_arr[i]->_char == c) {
			return true;
		}
	}
	return false;
}

int Huffman::FindPos(char c, vector <Huffman*> _arr) {
	for (int i = 0; i < _arr.size(); i++) {
		if (_arr[i]->_char == c) {
			return i;
		}
	}
}

void Huffman::CreateNode(string _name, vector <Huffman*>& _arr) {
	
	ifstream _input(_name);

	if (_input.fail()) {
		cout << "Can't open this file" << endl;
		return;
	}

	while (!_input.eof()) {
		char* Buffer = new char;
		if (_input.read(Buffer, 1)) {
			if (IsAvailable(*Buffer, _arr)) {
				int pos = FindPos(*Buffer, _arr);
				_arr[pos]->_frq++;
			}
			else {
				Huffman* tmp = new Huffman(*Buffer);
				_arr.push_back(tmp);
			}
		}
		delete Buffer;
	}

	_input.close();
}

void Huffman::Arrange(vector <Huffman*>& _arr) {
	for (int i = 0; i < _arr.size() - 1; i++) {
		for (int j = i + 1; j < _arr.size(); j++) {
			if (_arr[i]->_frq > _arr[j]->_frq) {
				swap(_arr[i], _arr[j]);
			}
		}
	}
}

Huffman* Huffman::CreateTree(vector <Huffman*>& _arr) {
	while (_arr.size() != 1) {
		Arrange(_arr);
		Huffman* tmp = new Huffman;
		tmp->_char = NULL;
		tmp->_frq = _arr[0]->_frq + _arr[1]->_frq;
		tmp->_left = _arr[0];
		tmp->_right = _arr[1];
		_arr.push_back(tmp);
		_arr.erase(_arr.begin(), _arr.begin() + 2);
	}
	return _arr[0];
}

void Huffman::AddCode(Huffman* _root, string code) {
	if (_root->_left == NULL && _root->_right == NULL) {
		_root->_code = code;
	}
	else {
		AddCode(_root->_left, code + '0');
		AddCode(_root->_right, code + '1');
	}
}

string Huffman::FindCode(vector <Huffman*> _arr, char c) {
	for (int i = 0; i < _arr.size(); i++) {
		if (_arr[i]->GetChar() == c) {
			return _arr[i]->GetCode();
		}
	}
}

char Huffman::FindChar(string s, vector <Huffman*> _arr) {
	for (int i = 0; i < _arr.size(); i++) {
		if (_arr[i]->_code == s) {
			return _arr[i]->_char;
		}
	}
	return NULL;
}

int Huffman::BinaryToDecimal(string& s)  {
	int result = 0;
	for (int i = 0; i < s.size(); i++)
		result = result * 2 + s[i] - '0';
	return result;
}

string Huffman::DecimalToBinary(int x)
{
	string temp = "";
	string result = "";
	while (x)
	{
		temp += ('0' + x % 2);
		x /= 2;
	}
	result.append(8 - temp.size(), '0');													
	for (int i = temp.size() - 1; i >= 0; i--)
	{
		result += temp[i];
	}
	return result;
}

string Huffman::BinaryToHex(string& s) {
	vector <Huffman*> _dic; //Tao bang ma 16
	for (int i = 0; i < 16; i++) {
		_dic.resize(i + 1);
		_dic[i] = new Huffman;
		if (i >= 10) {
			_dic[i]->_char = char(65 + i - 10);
		}
		else {
			_dic[i]->_char = i + '0';
		}
		_dic[i]->_code = DecimalToBinary(i);
	}

	while (s.size() % 4 != 0) { //Them cho du so bit
		s = '0' + s;
	}

	string result = "";
	for (int i = 0; i < s.length(); i += 4) {
		string tmp = s.substr(i, 4);
		for (int i = 0; i < 4; i++) {
			tmp = '0' + tmp;
		}
		result += FindChar(tmp, _dic);
	}

	for (int i = 0; i < _dic.size(); i++) {
		delete _dic[i];
	}
	_dic.clear();
	return result;
}

string Huffman::BinaryTo32(string& s) {
	vector <Huffman*> _dic; //Tao bang ma 32

	for (int i = 0; i < 32; i++) {
		_dic.resize(i + 1);
		_dic[i] = new Huffman;
		if (i >= 10) {
			_dic[i]->_char = char(65 + i - 10);
		}
		else {
			_dic[i]->_char = i + '0';
		}
		_dic[i]->_code = DecimalToBinary(i);
	}

	while (s.size() % 5 != 0) { //Them cho du so bit
		s = '0' + s;
	}

	string result = "";
	for (int i = 0; i < s.length(); i += 5) {
		string tmp = s.substr(i, 5);
		for (int i = 0; i < 3; i++) {
			tmp = '0' + tmp;
		}
		result += FindChar(tmp, _dic);
	}

	for (int i = 0; i < _dic.size(); i++) {
		delete _dic[i];
	}
	_dic.clear();
	return result;
}

void Huffman::Encoding(string _name) {
	vector <Huffman*> _arr;
	Huffman::CreateNode(_name, _arr);
	vector <Huffman*> _tmp = _arr; //Sao chep mang luu tru cac ky tu

	//Tao ma cho tung nut
	Huffman* root = Huffman::CreateTree(_arr);
	string code = "";
	Huffman::AddCode(root, code);


	fstream _input;
	fstream _output;
	_input.open(_name, ios::in);
	_output.open("test01", ios::out | ios::binary);

	if (_input.fail()) {
		cout << "Can't open this file" << endl;
		return;
	}

	//Ma hoa file txt

	/*for (int i = 0; i < _tmp.size(); i++) {
		_output << _tmp[i]->GetChar() << _tmp[i]->GetCode() << endl;
	}*/
	string s;
	while (!_input.eof()) {
		char* Buffer = new char;
		if (_input.read(Buffer, 1)) {
			 s += FindCode(_tmp, *Buffer);
		}
		delete Buffer;
	}
	_output << BinaryTo32(s);
	
	

	_input.close();
	_output.close();
	delete root;
	_arr.clear();
	_tmp.clear();
}