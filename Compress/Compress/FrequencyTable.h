#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct Frenquency {
	char _char;
	float _freq;
};

class Table {
private:
	vector <Frenquency> _a;
	int _len;
public:
	Table();
	~Table();

	bool CheckAvailable(char c);
	int FindPos(char c);
	void CreateTable();

	friend ostream& operator<<(ostream& out, const Table& p);
};
