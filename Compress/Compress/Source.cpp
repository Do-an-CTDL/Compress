#include <conio.h>
#include "Huffman.h"


void main() {
	string _name;
	cout << "Input name: ";
	getline(cin, _name);

	//fstream _input;
	//_input.open(_name, ios::in | ios::binary);
	//if (_input.fail()) {
	//	cout << "Can't open this file" << endl;
	//	return;
	//}

	//stringstream ss;  //Luu toan bo nd file vao chuoi _data
	//ss << _input.rdbuf();
	//string _data = ss.str();
	//_input.close();

	////Tai tao lai bo ma Huffman
	//string tmp = Huffman::ReadLine(0, _data);
	//int N = atoi(tmp.c_str()); //So luong ki tu co trong bo ma Huffman
	//int pos = 2; //Bien pos luu lai vi tri dang doc
	//vector <Huffman*> _arr;
	//for (int i = 0; i < N; i++) {
	//	tmp = Huffman::ReadLine(pos, _data); //Doc tung dong lay ki tu va ma cua chung
	//	pos = pos + tmp.length() + 1; //Doi vi tri doc xuong dong tiep theo
	//	Huffman* _a = new Huffman;
	//	if (tmp[0] != '\\') { //TH dac biet la ki tu xuong dong (ki tu duoc luu tru la \n)
	//		_a->SetChar(tmp[0]); //Chu cai dau tien trong chuoi la ki tu
	//		_a->SetCode(tmp.substr(1)); //Nhung chu cai con lai la ma
	//	}
	//	else {
	//		_a->SetChar('\n');
	//		_a->SetCode(tmp.substr(2));
	//	}
	//	_arr.push_back(_a);

	//}

	//for (int i = 0; i < _arr.size(); i++) {
	//	cout << _arr[i]->GetChar() << " " << _arr[i]->GetCode() << endl;
	//}

	//tmp = Huffman::ReadLine(pos, _data);
	//pos = pos + tmp.length() + 1;
	//int len = atoi(tmp.c_str());
	//cout << len;
	////pos = pos + tmp.length() + 1;

	////Sao chep chuoi ma hoa
	//tmp.clear();
	//for (int i = pos; i < _data.size(); i++)
	//	tmp += _data[i];
	////tmp = Huffman::_32ToBinary(tmp); //Ma hoa chuoi he 32 thanh he nhi phan
	////if (tmp.length() > len) { //Chuan hoa chuoi thanh co so bit bang dung chuoi ban dau
	////	tmp = tmp.substr(tmp.length() - len);
	////}
	//cout << endl << tmp;
	//for (int i = 0; i < _arr.size(); i++) { //Xoa bang tra cuu
	//	delete _arr[i];
	//}


	Huffman::Encoding(_name);

	_name = "Test01";
	Huffman::Decoding(_name);

	//_input.close();


	//return 0;
	_getch();
}