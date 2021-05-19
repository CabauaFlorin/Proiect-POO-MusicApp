#pragma once

#include <windows.h>
#include <sqlext.h>
#include <sqltypes.h>
#include <sql.h>
namespace olc
{
	namespace net
	{
#define SQL_RESULT_LEN 240
#define SQL_RETURN_CODE_LEN 1000

		template<typename T>
		class dbconnector
		{
		public:
			dbconnector()
			{
				sqlEnvHandle = NULL;
				sqlConnHandle = NULL;
				sqlStmtHandle = NULL;
			}
			virtual ~dbconnector()
			{
				//close connection and free resources
				SQLFreeHandle(SQL_HANDLE_STMT, sqlStmtHandle);
				SQLDisconnect(sqlConnHandle);
				SQLFreeHandle(SQL_HANDLE_DBC, sqlConnHandle);
				SQLFreeHandle(SQL_HANDLE_ENV, sqlEnvHandle);
			}
			bool OnAttemptToConnect()
			{
				if (SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &sqlEnvHandle) != SQL_SUCCESS)
				{
					return false;
				}
				if (SQLSetEnvAttr(sqlEnvHandle, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0) != SQL_SUCCESS)
				{
					return false;
				}
				if (SQLAllocHandle(SQL_HANDLE_DBC, sqlEnvHandle, &sqlConnHandle) != SQL_SUCCESS)
				{
					return false;
				}

				std::cout << "[dbconnector] Attempting connection to SQL Server...\n";

				//connect to SQL Server  
				switch (SQLDriverConnect(sqlConnHandle,
					NULL,
					//(SQLWCHAR*)L"DRIVER={SQL Server};SERVER=localhost, 1433;DATABASE=master;UID=username;PWD=password;",
					(SQLWCHAR*)L"DRIVER={SQL Server};SERVER=localhost, 1434;DATABASE=CabManDB;Trusted=true;",
					SQL_NTS,
					retconstring,
					1024,
					NULL,
					SQL_DRIVER_NOPROMPT)) {
				case SQL_SUCCESS:
					std::cout << "[dbconnector] Successfully connected to SQL Server";
					std::cout << "\n";
					break;
				case SQL_SUCCESS_WITH_INFO:
					std::cout << "[dbconnector] Successfully connected to SQL Server";
					std::cout << "\n";
					break;
				case SQL_INVALID_HANDLE:
					std::cout << "[dbconnector] Could not connect to SQL Server";
					std::cout << "\n";
					return false;
				case SQL_ERROR:
					std::cout << "[dbconnector] Could not connect to SQL Server";
					std::cout << "\n";
					return false;
				default:
					break;
				}

				// if there is a problem connecting then exit
				if (SQLAllocHandle(SQL_HANDLE_STMT, sqlConnHandle, &sqlStmtHandle) != SQL_SUCCESS)
				{
					return false;
				}

				return true;
			}

			bool isConnected()
			{
				return SQLGetConnectAttr(sqlConnHandle, SQL_ATTR_CONNECTION_DEAD, NULL, NULL, NULL);
			}

			void ExecuteQuery(const std::string& query)
			{
				std::cout << "\n";
				std::cout << "[dbconnector] Executing SQL query...";
				std::cout << "\n";

				if (SQLPrepareA(sqlStmtHandle, (SQLCHAR*)query.c_str(), SQL_NTS) != SQL_SUCCESS)
				{
					std::cout << "[dbconnector] Error querying SQL Server";
					std::cout << "\n";
				}
				else
				{
					SQLExecute(sqlStmtHandle);
					std::cout << "[dbconnector] Query executed successfully!\n";
				}

				// finish the query and disconnect. Expect connect attempt in Server.ExecQuery()!!!!!!!!!!!!
				SQLDisconnect(sqlConnHandle);
			}

			std::string GetResultFromExecuteQuery(const std::string& query, int columnIndex = 1)
			{
				std::string resultString = "";
				std::cout << "\n";
				std::cout << "[dbconnector] Executing SQL query...";
				std::cout << "\n";

				if (SQLPrepareA(sqlStmtHandle, (SQLCHAR*)query.c_str(), SQL_NTS) != SQL_SUCCESS)
				{
					std::cout << "[dbconnector] Error querying SQL Server";
					std::cout << "\n";
				}
				else
				{
					SQLExecute(sqlStmtHandle);
					std::cout << "[dbconnector] Query executed successfully!\n";
					//declare output variable and pointer
					SQLCHAR queryResult[SQL_RESULT_LEN];
					SQLLEN ptrQueryResult;
					if (SQLFetch(sqlStmtHandle) == SQL_SUCCESS)
					{
						SQLGetData(sqlStmtHandle, columnIndex, SQL_CHAR, queryResult, SQL_RESULT_LEN, &ptrQueryResult);
						std::string str((const char*)queryResult);
						resultString += str;
					}
				}
				// finish the query and disconnect. Expect connect attempt in Server.ExecQuery()
				SQLDisconnect(sqlConnHandle);

				return resultString;
			}
		private:
			SQLHANDLE sqlConnHandle;
			SQLHANDLE sqlStmtHandle;
			SQLHANDLE sqlEnvHandle;
			SQLWCHAR retconstring[SQL_RETURN_CODE_LEN];
		};
	}
}