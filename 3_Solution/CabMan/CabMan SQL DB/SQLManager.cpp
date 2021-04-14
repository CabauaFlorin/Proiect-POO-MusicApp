#include "SQLManager.h"

SQLManager* SQLManager::instance = nullptr;

SQLManager::SQLManager()
{

}

SQLManager* SQLManager::getInstance()
{
    if (instance == nullptr)
        instance = new SQLManager;
    return instance;
}

string SQLManager::makeCustomQuery(const wchar_t* query, int column)
{
    Query* temp_query = new Query;

    return temp_query->makeCustomQuery(query, column);
}

string SQLManager::getAllUserNames()
{
    Query* temp_query = new Query;

    return temp_query->getAllUserNames();
}

string SQLManager::makeRangeQuery(const wchar_t* query, int column_start, int column_finish)
{
    Query* temp_query = new Query;
    return temp_query->makeRangeQuery(query, column_start, column_finish);
}

bool SQLManager::authentifyUser(string mail_string, string password_string)
{
    Query* temp_query = new Query;

    if (temp_query->authentifyUser(WSTR_TO_STR(mail_string), WSTR_TO_STR(password_string)).length() < 2)
        return false;
    return true;

}

void SQLManager::insert_data(string mail, string username, string parola)
{
    //('popica@yahoo.com', 'popica', 'parolamea')
    string temp_string = "('";
    temp_string += mail;
    temp_string += "', '";
    temp_string += username;
    temp_string += "', '";
    temp_string += parola;
    temp_string += "')";
    this->insertNewClient(temp_string);

    //(L"insert into Clienti(Email, Username, Parola) values('cabauaflorin@yahoo.com', 'Cabelu', 'bratara')", 1);
}

void SQLManager::insertNewClient(string queryBuffer)
{
    Query* temp_query = new Query;

    temp_query->insertNewClient(WSTR_TO_STR(queryBuffer));
}

SQLManager::~SQLManager()
{

}