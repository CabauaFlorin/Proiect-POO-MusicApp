#pragma once
#include <iostream>
#include <locale>
#include <codecvt>
#include <string>

#include "Query.h"

using namespace std;


#define WSTR_TO_STR(str) wstring_convert<codecvt_utf8<wchar_t>>().from_bytes(str) //wide string to normal string convertor

class SQLManager
{
private:
    SQLManager();
    ~SQLManager();

    static SQLManager* instance;

public:

    static SQLManager* getInstance();

    string makeCustomQuery(const wchar_t* query, int column); //E.g. query: "SELECT * FROM Employees", /// column e coloana pe care o vreau
    string getAllUserNames();
    string makeRangeQuery(const wchar_t* query, int column_start, int column_finish);

    bool authentifyUser(string mail_string, string password_string);

    void insert_data(string mail, string username, string parola);
    void insertNewClient(string queryBuffer); //it must contain every column except UserID
};