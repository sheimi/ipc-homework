#include "server/db.h"
#include "env.h"
#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>

static sqlite3 * db;
int user_id;

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
  bool result = false;
  sprintf(sql, "select id from user where username=\"%s\" and password=\"%s\"", username, password); 
  sqlite3_get_table(db, sql, &dbr, &nrow, &ncolumn, &errmsg);
  if (nrow > 0) {
    user_id = atoi(dbr[1]);
    result = true;
  }
  sqlite3_free_table(dbr);
  return result;
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

bool query_stations_db(char *** dbr, int * nrow, int * ncolumn) {
  char * sql = "select name from station";
  char * errmsg;
  sqlite3_get_table(db, sql, dbr, nrow, ncolumn, &errmsg);
  return true;
}

bool query_train_db(char *** dbr, int * row, int * column, char * start_station, char * end_station) {
  char sql[256];
  char * errmsg;
  sprintf(sql, "select train.name, s1.name, s2.name from train, station as s1, station as s2 where"
                " train.start_station = s1.id and train.end_station = s2.id and s1.name = '%s'"
                " and s2.name = '%s'", start_station, end_station);
  sqlite3_get_table(db, sql, dbr, row, column, &errmsg);   
  return true;
} 

bool buy_ticket_db(char * trainname, char * date) {
  char sql[128];
  int nrow, ncolumn;
  char ** dbr;
  char * errmsg;
  int num, train_id;

  sprintf(sql, "select id, seat_num from train where name = '%s'", trainname);
  sqlite3_get_table(db, sql, &dbr, &nrow, &ncolumn, &errmsg);

  if (nrow == 0) {
    sqlite3_free_table(dbr); 
    return false;
  }
    
  
  train_id = atoi(dbr[2]);
  num = atoi(dbr[3]);
  sqlite3_free_table(dbr); 

  sprintf(sql, "select count(*) from sell_log where train_id = %d and buy_date = '%s'", train_id, date);
  sqlite3_get_table(db, sql, &dbr, &nrow, &ncolumn, &errmsg);
  if (num <= atoi(dbr[1])) {
    sqlite3_free_table(dbr); 
    return false;
  }
  sqlite3_free_table(dbr); 

  sprintf(sql, "insert into sell_log(\"user_id\", \"train_id\", \"buy_date\") values(%d, %d, \"%s\")", 
            user_id, train_id, date);
  sqlite3_exec(db, sql, NULL, NULL, &errmsg); 
  return true;
}

bool query_orders_db(char *** dbr, int * nrow, int * ncolumn) {
  char sql[256];
  char * errmsg;
  sprintf(sql, "select sell_log.id, train.name, buy_date from sell_log,"
                " train where sell_log.user_id = %d and train.id = sell_log.train_id", user_id);
  sqlite3_get_table(db, sql, dbr, nrow, ncolumn, &errmsg);
  return true;
}

bool delete_order_db(char * order_id) {
  char sql[128];
  int nrow, ncolumn;
  char ** dbr;
  char * errmsg;

  sprintf(sql, "delete from sell_log where id = %s", order_id);
  sqlite3_exec(db, sql, NULL, NULL, &errmsg); 

  return true;
}

void release_dbr(char ** dbr) {
  sqlite3_free_table(dbr); 
}
