#include "Query.h"

Query::Query()
{

}

string Query::getAllUserNames()
{
    return makeCustomQuery(L"SELECT FirstName + ' ' + LastName FROM Users", 1);
}

string Query::authentifyUser(wstring mail_wstring, wstring password_wstring)
{
    wstring temp_wstring;
    temp_wstring = L"SELECT * FROM Users WHERE PasswordHash = '" + password_wstring + L"' AND Email = '" + mail_wstring + L"'";
    string tempStr = makeCustomQuery(temp_wstring.c_str(), 4);
    tempStr += ' ' + makeCustomQuery(temp_wstring.c_str(), 5);
    return tempStr;
}

string Query::makeRangeQuery(const wchar_t* query, int column_start, int column_finish)
{
    wstring ws; //= L"Select * from ";
    string return_buffer;
    ws += query;

    //initializations
    sqlConnHandle = NULL;
    sqlStmtHandle = NULL;
    //allocations
    if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &sqlEnvHandle))
        goto COMPLETED;
    if (SQL_SUCCESS != SQLSetEnvAttr(sqlEnvHandle, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0))
        goto COMPLETED;
    if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_DBC, sqlEnvHandle, &sqlConnHandle))
        goto COMPLETED;
    //output
    cout << "Attempting connection to SQL Server...";
    cout << "\n";
    //connect to SQL Server  

    switch (SQLDriverConnect(sqlConnHandle,
        NULL,
        (SQLWCHAR*)L"DRIVER={SQL Server};SERVER=localhost, 1433;DATABASE=CabManDB;Trusted=true;", //Precizeaza baza de date / database-ul
        SQL_NTS,
        retconstring,
        1024,
        NULL,
        SQL_DRIVER_NOPROMPT)) {
    case SQL_SUCCESS:
        cout << "Successfully connected to SQL Server";
        cout << "\n";
        break;
    case SQL_SUCCESS_WITH_INFO:
        cout << "Successfully connected to SQL Server";
        cout << "\n";
        break;
    case SQL_INVALID_HANDLE:
        cout << "Could not connect to SQL Server";
        cout << "\n";
        goto COMPLETED;
    case SQL_ERROR:
        cout << "Could not connect to SQL Server";
        cout << "\n";
        goto COMPLETED;
    default:
        break;
    }
    //if there is a problem connecting then exit application
    if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_STMT, sqlConnHandle, &sqlStmtHandle))
        goto COMPLETED;
    //output
    cout << "\n";
    cout << "Executing T-SQL query...";
    cout << "\n";
    //if there is a problem executing the query then exit application
    //else display query result
    if (SQL_SUCCESS != SQLExecDirect(sqlStmtHandle, (SQLWCHAR*)ws.c_str(), SQL_NTS)) {
        cout << "Error querying SQL Server";
        cout << "\n";
        goto COMPLETED;
    }
    else {
        //declare output variable and pointer
        SQLCHAR sqlVersion[SQL_RESULT_LEN];

        SQLLEN ptrSqlVersion;
        while (SQLFetch(sqlStmtHandle) == SQL_SUCCESS) {
            //template pentru ciclarea mai multor coloane
            for (int index = column_start; index < column_finish; index++) {
                SQLGetData(sqlStmtHandle, index, SQL_CHAR, sqlVersion, SQL_RESULT_LEN, &ptrSqlVersion);
                return_buffer += (string((const char*)sqlVersion)) + " ";
            }

            //return_buffer += "\n";
        }
    }
    return return_buffer;
    //close connection and free resources
COMPLETED:
    SQLFreeHandle(SQL_HANDLE_STMT, sqlStmtHandle);
    SQLDisconnect(sqlConnHandle);
    SQLFreeHandle(SQL_HANDLE_DBC, sqlConnHandle);
    SQLFreeHandle(SQL_HANDLE_ENV, sqlEnvHandle);
    return NULL;
}

string Query::makeCustomQuery(const wchar_t* query, int column)
{
    wstring ws; //= L"Select * from ";
    string return_buffer;
    ws += query;

    //initializations
    sqlConnHandle = NULL;
    sqlStmtHandle = NULL;
    //allocations
    if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &sqlEnvHandle))
        goto COMPLETED;
    if (SQL_SUCCESS != SQLSetEnvAttr(sqlEnvHandle, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0))
        goto COMPLETED;
    if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_DBC, sqlEnvHandle, &sqlConnHandle))
        goto COMPLETED;
    //output
    cout << "Attempting connection to SQL Server...";
    cout << "\n";
    //connect to SQL Server  

    switch (SQLDriverConnect(sqlConnHandle,
        NULL,
        (SQLWCHAR*)L"DRIVER={SQL Server};SERVER=localhost, 1433;DATABASE=CabManDB;Trusted=true;", //Precizeaza baza de date / database-ul
        SQL_NTS,
        retconstring,
        1024,
        NULL,
        SQL_DRIVER_NOPROMPT)) {
    case SQL_SUCCESS:
        cout << "Successfully connected to SQL Server";
        cout << "\n";
        break;
    case SQL_SUCCESS_WITH_INFO:
        cout << "Successfully connected to SQL Server";
        cout << "\n";
        break;
    case SQL_INVALID_HANDLE:
        cout << "Could not connect to SQL Server";
        cout << "\n";
        goto COMPLETED;
    case SQL_ERROR:
        cout << "Could not connect to SQL Server";
        cout << "\n";
        goto COMPLETED;
    default:
        break;
    }
    //if there is a problem connecting then exit application
    if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_STMT, sqlConnHandle, &sqlStmtHandle))
        goto COMPLETED;
    //output
    cout << "\n";
    cout << "Executing T-SQL query...";
    cout << "\n";
    //if there is a problem executing the query then exit application
    //else display query result
    if (SQL_SUCCESS != SQLExecDirect(sqlStmtHandle, (SQLWCHAR*)ws.c_str(), SQL_NTS)) {
        cout << "Error querying SQL Server";
        cout << "\n";
        goto COMPLETED;
    }
    else {
        //declare output variable and pointer
        SQLCHAR sqlVersion[SQL_RESULT_LEN];

        SQLLEN ptrSqlVersion;
        while (SQLFetch(sqlStmtHandle) == SQL_SUCCESS) {
            SQLGetData(sqlStmtHandle, column, SQL_CHAR, sqlVersion, SQL_RESULT_LEN, &ptrSqlVersion);
            return_buffer += (string((const char*)sqlVersion)) + '\n';
            //display query result
        }
    }
    return return_buffer;
    //close connection and free resources
COMPLETED:
    SQLFreeHandle(SQL_HANDLE_STMT, sqlStmtHandle);
    SQLDisconnect(sqlConnHandle);
    SQLFreeHandle(SQL_HANDLE_DBC, sqlConnHandle);
    SQLFreeHandle(SQL_HANDLE_ENV, sqlEnvHandle);
    return NULL;
}

void Query::insertNewClient(wstring queryBuffer)
{
    wstring temp_wstring = L"USE CabManDb INSERT INTO Clienti(Email, Username, Parola) VALUES ";
    temp_wstring += queryBuffer;

    //initializations
    sqlConnHandle = NULL;
    sqlStmtHandle = NULL;
    //allocations
    if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &sqlEnvHandle))
        goto COMPLETED;
    if (SQL_SUCCESS != SQLSetEnvAttr(sqlEnvHandle, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0))
        goto COMPLETED;
    if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_DBC, sqlEnvHandle, &sqlConnHandle))
        goto COMPLETED;
    //output
    cout << "Attempting connection to SQL Server...";
    cout << "\n";
    switch (SQLDriverConnect(sqlConnHandle,
        NULL,
        (SQLWCHAR*)L"DRIVER={SQL Server};SERVER=localhost, 1433;DATABASE=CabManDB;Trusted=true;",
        SQL_NTS,
        retconstring,
        1024,
        NULL,
        SQL_DRIVER_NOPROMPT)) {
    case SQL_SUCCESS:
        cout << "Successfully connected to SQL Server";
        cout << "\n";
        break;
    case SQL_SUCCESS_WITH_INFO:
        cout << "Successfully connected to SQL Server";
        cout << "\n";
        break;
    case SQL_INVALID_HANDLE:
        cout << "Could not connect to SQL Server";
        cout << "\n";
        goto COMPLETED;
    case SQL_ERROR:
        cout << "Could not connect to SQL Server";
        cout << "\n";
        goto COMPLETED;
    default:
        break;
    }
    //if there is a problem connecting then exit application
    if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_STMT, sqlConnHandle, &sqlStmtHandle))
        goto COMPLETED;
    //output
    cout << "\n";
    cout << "Executing T-SQL query...";
    cout << "\n";
    //if there is a problem executing the query then exit application
    //else display query result
    SQLExecDirect(sqlStmtHandle,
        (SQLWCHAR*)temp_wstring.c_str(),
        SQL_NTS);
COMPLETED:
    SQLFreeHandle(SQL_HANDLE_STMT, sqlStmtHandle);
    SQLDisconnect(sqlConnHandle);
    SQLFreeHandle(SQL_HANDLE_DBC, sqlConnHandle);
    SQLFreeHandle(SQL_HANDLE_ENV, sqlEnvHandle);
    //pause the console window - exit when key is pressed
}

Query::~Query()
{

}