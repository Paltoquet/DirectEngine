#include "stdafx.h"
#include "loger.h"

using namespace std;

string Loger::m_parserLoger = "log.txt";
ofstream Loger::m_file;

Loger::Loger()
{

}


Loger::~Loger()
{

}

void Loger::initialise() {
	m_file.open(m_parserLoger);
}

void Loger::close() {
	m_file.close();
}

void Loger::log(string msg) {
	m_file << msg.c_str() << endl;
}