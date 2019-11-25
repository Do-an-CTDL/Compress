#include "Folder.h"


Folder::Folder() {

	_name.clear();
	_buff.clear();
}

//Doc tat ca cac file trong folder
vector<string> Folder::GetNameFolder(string folder)
{
	vector<string> names;
	string search_path = folder + "/*.*";
	WIN32_FIND_DATA fd;
	HANDLE hFind = ::FindFirstFile(search_path.c_str(), &fd);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			
			
			if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
				names.push_back(fd.cFileName);
			}
		} while (::FindNextFile(hFind, &fd));
		::FindClose(hFind);
	}
	return names;
}

//1: nen, 0 giai nen
void Folder::Input(bool flag) {

	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;

	cout << "Nhap Ten thu muc: ";

	getline(cin, _nameFolder);

	char* tmp = new char[_nameFolder.size() + 1];

	for (int i = 0; i <= _nameFolder.size(); i++) {

		tmp[i] = (_nameFolder[i]);
	}

	const char* tmp2 = tmp;

	hFind = FindFirstFile(tmp2, &FindFileData);
	if (hFind == INVALID_HANDLE_VALUE)
	{
		printf("FindFirstFile failed (%d)\n", GetLastError());
		return;
	}
	else
	{
		printf(TEXT("The first file found is %s\n"),
			FindFileData.cFileName);

		_name = GetNameFolder(FindFileData.cFileName);
		if (flag == 1) {
			for (int i = 0; i < _name.size(); i++) {







				cout << _name[i] << "\n";
				vector <Huffman* > Buff;
				vector <char> data;
				CreateNode(_name[i], Buff, data);

				_buff.push_back(Buff);
				_data.push_back(data);
			}
		}
		else {
			
			DecodeFolder();
		
		}
		FindClose(hFind);
	}
}


//Nen ca thu muc
void Folder::EncodeFolder() {


	for (int i = 0; i < _name.size(); i++) {

		string out = _name[i];
		/*for (int j = 0; j < _name[i].size(); j++) {
			
			if (out[j] == '.') {
				out = out.substr(0, j );
				break;
			}
		}*/

		Huffman::Encoding(_buff[i], _data[i],out, "Test");
	}
}

//Giai nen ca thu muc
void Folder::DecodeFolder() {

	string nameOut = "Decode";
	for (int i = 0; i < _name.size(); i++) {

		Huffman::Decoding(_name[i], _nameFolder,  nameOut);
	}
}