PRAGMA foreign_keys = false;

DROP TABLE IF EXISTS "user";
CREATE TABLE "user" (
  id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
  username VARCHAR NOT NULL,
  password VARCHAR NOT NULL
);

DROP TABLE IF EXISTS "station";
CREATE TABLE "station" (
  id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
  name VARCHAR NOT NULL
);

DROP TABLE IF EXISTS "train";
CREATE TABLE "train" (
  id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
  name  VARCHAR NOT NULL,
  seat_num INTEGER NOT NULL
);

DROP TABLE IF EXISTS "seat";
CREATE TABLE "seat" (
  id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
  num INTEGER NOT NULL,
  train_id INTEGER NOT NULL,
  FOREIGN KEY(train_id) REFERENCES "train"(id)
);

DROP TABLE IF EXISTS "train_station";
CREATE TABLE "train_station" (
  id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
  train_id INTEGER NOT NULL,
  station_id INTEGER NOT NULL,
  num INTEGER NOT NULL,
  FOREIGN KEY(train_id) REFERENCES "train"(id),
  FOREIGN KEY(station_id) REFERENCES "statidon"(id)
);

DROP TABLE IF EXISTS "ticket";
CREATE TABLE "ticket" (
  id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
  start_station INTEGER NOT NULL,
  end_station   INTEGER NOT NULL,
  seat_id       INTEGER NOT NULL,
  FOREIGN KEY(start_station) REFERENCES "station"(id),
  FOREIGN KEY(end_station) REFERENCES "station"(id),
  FOREIGN KEY(seat_id) REFERENCES "seat"(id)
);

DROP TABLE IF EXISTS "sell_log";
CREATE TABLE "sell_log" (
  id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
  user_id INTEGER NOT NULL,
  ticket_id INTEGER NOT NULL,
  buy_date DATETIME NOT NULL,
  FOREIGN KEY(user_id) REFERENCES "user"(id),
  FOREIGN KEY(ticket_id) REFERENCES "ticket"(id)
);
/***********HERE IS THE DATA***************/
BEGIN;
  INSERT INTO "user" values (1, "sheimi", "zhang");
COMMIT;
