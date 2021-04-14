#include <iostream>
#include "SQLManager.h"
#include "Query.h"
using namespace std;

void insert_data(string mail, string username, string parola)
{
	string temp_string = "('";
	temp_string += mail;
	temp_string += "', '";
	temp_string += username;
	temp_string += "', '";
	temp_string += parola;
	temp_string += "')";
	SQLManager::getInstance()->insertNewClient(temp_string);
}

int main()
{
	//cout << SQLManager::getInstance()->makeCustomQuery(L"insert into Clienti(Email, Username, Parola) values('cabauaflorin@yahoo.com', 'Cabelu', 'bratara')", 1);
	insert_data("andronache@yahoo.ro", "boss", "parolatare");


	return 0;
}