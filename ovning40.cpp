#include <iostream>
#include <sql.h>
#include <sqlext.h>
#include <sqltypes.h>

// CREATE DATABASE chas;
// CREATE TABLE chas.users (name TEXT UNIQUE KEY);
// INSERT INTO chas.users VALUES ('admin'), ('example');

int main(int argc, char *argv[])
{
  SQLHENV henv = nullptr;
  SQLHDBC hdbc = nullptr;
  SQLRETURN ret;

  SQLCHAR dsn[] =
    "DRIVER=MariaDB;"
    "SERVER=localhost;"
    "DATABASE=chas;"
    "USER=chas;"
    "PASSWORD=secret";
  // Initialize ODBC environment
  SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv);

  // Set ODBC version to 3
  SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER);

  // Initialize connection handle
  SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc);

  // Connect to the MySQL server
  SQLDriverConnect(hdbc, henv, dsn, SQL_NTS,
                   nullptr, 0, nullptr,
                   SQL_DRIVER_COMPLETE);

  SQLCHAR query[] = "SELECT * FROM chas.users;";
  SQLHSTMT hstmt = nullptr;
  SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
  SQLPrepare(hstmt, query, SQL_NTS);
  SQLExecute(hstmt);

  SQLLEN count = 0;
  SQLRowCount(hstmt, &count);
  for (int i = 0; i < count; ++i) {
    SQLFetch(hstmt);
    SQLCHAR name[64];
    SQLLEN size = 0;
    SQLGetData(hstmt, 1, SQL_C_CHAR, name, sizeof(name), &size);
    std::cout << i << '\t' << size << ':' << name << '\n';
  }

  // Free statment
  SQLFreeHandle(SQL_HANDLE_STMT, hstmt);

  // Disconnect from db
  SQLDisconnect(hdbc);

  // Free the environment
  SQLFreeHandle(SQL_HANDLE_DBC, hdbc);
  SQLFreeHandle(SQL_HANDLE_ENV, henv);

  return 0;
}
