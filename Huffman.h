#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

class Huffman
{
private:
	char _char;
	int _frq;
	string _code;
	Huffman* _left;
	Huffman* _right;
public:
	Huffman();
	Huffman(char c);
	virtual ~Huffman();

	char GetChar() const;
	string GetCode() const;
	int GetFreq() const;
	void SetChar(char c);
	void SetCode(string s);
	
	static bool IsAvailable(char c, vector <Huffman*>_arr);
	static int FindPos(char c, vector <Huffman*>_arr);
	static void CreateNode(string _name, vector <Huffman*>& _arr); //Create node

	static void Arrange(vector <Huffman*>& _arr);
	static Huffman* CreateTree(vector <Huffman*>& _arr);
	static void AddCode(Huffman* Root, string _code);
	static string FindCode(vector <Huffman*>_arr, char c);

	static char FindChar(string s, vector <Huffman*> _arr);
	static int BinaryToDecimal(string& s);
	static string DecimalToBinary(int x);
	static string BinaryToHex(string& s);
	static string BinaryTo32(string& s);
	static string _32ToBinary(string& s);
	
	static string ReadLine(int pos, string s);
	static void Encoding(string _name);
	static void Decoding(string _name);
};

