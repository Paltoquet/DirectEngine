#pragma once

#include <string>
#include <iostream>
#include <fstream>

class Loger
{
public:
	Loger();
	~Loger();

public:
	static void initialise();
	static void log(std::string msg);
	static void close();

private:
	static std::string m_parserLoger;
	static std::ofstream m_file;
};

