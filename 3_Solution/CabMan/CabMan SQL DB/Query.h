#pragma once

#include <iostream>
#include <windows.h>
#include <sqlext.h>
#include <sqltypes.h>
#include <sql.h>
#include <stdio.h>  

#include <odbcss.h>  

#define SQL_RESULT_LEN 240
#define SQL_RETURN_CODE_LEN 1000

#define TEXTSIZE  12000  
#define MAXBUFLEN 256  

using namespace std;


class Query
{
private:
    SQLHANDLE sqlConnHandle;
    SQLHANDLE sqlStmtHandle;
    SQLHANDLE sqlEnvHandle;
    SQLWCHAR retconstring[SQL_RETURN_CODE_LEN];
public:

    Query();

    string getAllUserNames();
    string makeCustomQuery(const wchar_t* query, int column); //E.g. query: "SELECT * FROM Employees", /// column e coloana pe care o vreau
    string authentifyUser(wstring mail_wstring, wstring password_wstring);
    string makeRangeQuery(const wchar_t* query, int column_start, int column_finish);

    void insertNewClient(wstring queryBuffer);//it must contain every column except UserID

    ~Query();
};