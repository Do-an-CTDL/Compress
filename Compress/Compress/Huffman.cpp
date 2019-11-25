#include "Huffman.h"


Huffman::Huffman() {
	_char = NULL;
	_frq = 0;
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
	/*delete[] _left;
	delete[] _right;*/
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

void Huffman::SetChar(char c) {
	_char = c;
}

void Huffman::SetCode(string s) {
	_code = s;
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
	return 0;
}

void Huffman::CreateNode(string _name, vector <Huffman*>& _arr, vector <char> &data) {
	
	string _nameout = "Test/" + _name;
	_name = "Tests/" + _name;
	ifstream f_read(_name, ios::binary | ios::in);
	

	
	
	char x;
	if (f_read.fail()) {
		cout << "Can't open this file" << endl;
		return;
	}
	f_read.unsetf(ios::skipws);


	while (f_read >> x) {
		
		data.push_back(x);
		if (IsAvailable(x, _arr)) {
			int pos = FindPos(x, _arr);
			_arr[pos]->_frq++;
		}
		else {
			Huffman* tmp = new Huffman(x);
			_arr.push_back(tmp);
		}
		
	
	}
	
	

	f_read.close();
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

string Huffman::_32ToBinary(string& s) {
	vector <Huffman*> _dic; //Tao bang tra cuu
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

	string result = "";
	for (int i = 0; i < s.length(); i++) {
		string tmp = FindCode(_dic, s[i]);
		tmp = tmp.substr(3);
		result += tmp;
	}

	for (int i = 0; i < _dic.size(); i++) {
		delete _dic[i];
	}
	_dic.clear();
	return result;
}

string Huffman::ReadLine(int pos, string s) {
	string result = "";
	for (int i = pos; i < s.length(); i++) {
		if (s[i] != '\n') {
			result += s[i];
		}
		else {
			return result;
		}
	}
}

void Huffman::Encoding(vector <Huffman*> _arr, vector <char> data, string outFile, string outFolder ) {
	//vector <Huffman*> _arr;
	//Huffman CreateNode(_name, _arr);

	vector <Huffman*> _tmp = _arr; //Sao chep mang luu tru cac ky tu

	//Tao ma cho tung nut
	Huffman* root = Huffman::CreateTree(_arr);
	string code = "";
	Huffman::AddCode(root, code);

	if (outFolder != "") {
		outFile = outFolder + "/" + outFile;
	}
	

	
	fstream _output;
	_output.open(outFile, ios::out | ios::binary);

	

	//Ma hoa file txt
	_output << _tmp.size() << endl; //Ghi lai bang ma Huffman de cho viec ma hoa
	for (int i = 0; i < _tmp.size(); i++) {
		if (_tmp[i]->_char == '\n') {
			_output << "\\n";
		}
		else {
			_output << _tmp[i]->_char;
		}
		_output << _tmp[i]->_code << endl;
	}

	string s;

	for (int i = 0; i < data.size(); i++) {

		s += FindCode(_tmp, data[i]);
	}
	
	_output << s.length() << endl;

	_output << BinaryTo32(s);
	
	for (int i = 0; i < _tmp.size(); i++) {
		delete _tmp[i];
	}

	_output.close();
	delete root;

	_tmp.clear();
}

void Huffman::Decoding(string _name, string nameFolder, string nameOut) {
	fstream _input;

	string nameInput = _name;
	if (nameOut != "") {

		nameInput = nameFolder + "/" + _name;
	}

	_input.open(nameInput, ios::in | ios::binary);
	if (_input.fail()) {
		cout << "Can't open this file" << endl;
		return;
	}

	stringstream ss;  //Luu toan bo nd file vao chuoi _data
	ss << _input.rdbuf();
	string _data = ss.str();
	_input.close();

	//Tai tao lai bo ma Huffman
	string tmp = ReadLine(0, _data);
	int N = atoi(tmp.c_str()); //So luong ki tu co trong bo ma Huffman
	int pos = tmp.length() + 1; //Bien pos luu lai vi tri dang doc
	vector <Huffman*> _arr;
	for (int i = 0; i < N; i++) {
		if (tmp != "\0")
			tmp = ReadLine(pos, _data); //Doc tung dong lay ki tu va ma cua chung
		pos = pos + tmp.length() + 1; //Doi vi tri doc xuong dong tiep theo
		Huffman* _a = new Huffman;
		if (tmp[0] != '\\') { //TH dac biet la ki tu xuong dong (ki tu duoc luu tru la \n)
			_a->_char = tmp[0]; //Chu cai dau tien trong chuoi la ki tu
			if (tmp != "\0")
				_a->_code = tmp.substr(1); //Nhung chu cai con lai la ma
		}
		else {
			_a->_char = '\n';
			if (tmp != "\0")
				_a->_code = tmp.substr(2);
		}
		_arr.push_back(_a);

	}

	//Lay do dai cua chuoi ban dau (vi khi ma hoa co them bit '0' de du bit)
	tmp = ReadLine(pos, _data); 
	pos = pos + tmp.length() + 1;
	int len = atoi(tmp.c_str());
	
	//Sao chep chuoi ma hoa
	tmp.clear();
	for (int i = pos; i < _data.size(); i++) {
		tmp += _data[i];
	}
	tmp = _32ToBinary(tmp); //Ma hoa chuoi he 32 thanh he nhi phan
	if (tmp.length() > len) { //Chuan hoa chuoi thanh co so bit bang dung chuoi ban dau
		tmp = tmp.substr(tmp.length() - len);
	}

	//Bat dau ma hoa va luu lai vao file txt
	fstream _output;
	
	if (nameOut != "") {

		_name = nameOut + "/" + _name;
	}

	_output.open(_name, ios::binary | ios::out);
	if (_output.fail()) {
		cout << "Failed";
		return;
	}
	//int max = _arr.back()->_code.size();

	string s = ""; //chuoi s de luu chuoi
	string s1; //chuoi s1 dung de so sanh
	for (int i = 0; i < tmp.size(); i++) {
		cout << i << "\n";
		s += tmp[i];
		if (i + 1 < tmp.size()) {
			s1 = s + tmp[i + 1];
		}
		else {
			s1 += '3'; //TH doc nhung bit cuoi cung
		}

		if (FindChar(s, _arr) != NULL && FindChar(s1, _arr) == NULL) {
			_output << FindChar(s, _arr);
			s.clear();
			s1.clear();
		}
	}
	_output.close();

	for (int i = 0; i < _arr.size(); i++) { //Xoa bang tra cuu
		delete _arr[i];
	}
}