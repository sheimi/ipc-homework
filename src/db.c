#include "server/db.h"
#include "env.h"
#include <sqlite3.h>
#include <stdio.h>

static sqlite3 * db;

void connect_db() {
  sqlite3_open("db/train.db", &db);
}

void close_db() {
  sqlite3_close(db);
}

bool check_user(char * username, char * password) {
  char sql[128];
  int nrow, ncolumn;
  char ** dbr;
  char * errmsg;
  sprintf(sql, "select * from user where username=\"%s\" and password=\"%s\"", username, password); 
  sqlite3_get_table(db, sql, &dbr, &nrow, &ncolumn, &errmsg);
  sqlite3_free_table(dbr);
  if (nrow > 0) {
    return true;
  }
  return false;
}

bool register_user(char * username, char * password) {
  char sql[128];
  int nrow, ncolumn;
  char ** dbr;
  char * errmsg;
  sprintf(sql, "select * from user where username=\"%s\"", username); 
  sqlite3_get_table(db, sql, &dbr, &nrow, &ncolumn, &errmsg);
  sqlite3_free_table(dbr);
  if (nrow > 0)
    return false;
  sprintf(sql, "insert into user(\"username\", \"password\") values(\"%s\", \"%s\")", username, password);
  sqlite3_exec(db, sql, NULL, NULL, &errmsg); 
  return true;
}
