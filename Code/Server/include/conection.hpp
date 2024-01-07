#pragma once
#include <array>

using std::array;

class Conection
{
private:
	static const size_t bufferSize{ 1 * 1024 };
	array<char, Conection::bufferSize> textBuffer;

private:
	//void Read();
	//void Send();

public: 
	//Conection();

	void Run();

	//virtual ~Conection();
};