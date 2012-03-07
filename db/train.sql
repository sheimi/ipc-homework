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
  seat_num INTEGER NOT NULL,
  start_station INTEGER NOT NULL,
  end_station   INTEGER NOT NULL,
  FOREIGN KEY(start_station) REFERENCES "station"(id),
  FOREIGN KEY(end_station) REFERENCES "station"(id)
);

DROP TABLE IF EXISTS "sell_log";
CREATE TABLE "sell_log" (
  id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
  user_id INTEGER NOT NULL,
  train_id INTEGER NOT NULL,
  buy_date DATETIME NOT NULL,
  FOREIGN KEY(user_id) REFERENCES "user"(id),
  FOREIGN KEY(train_id) REFERENCES "train"(id)
);

/***********HERE IS THE DATA***************/
BEGIN;
  /*users*/
  INSERT INTO "user" values (1, "sheimi", "zhang");
  /*stations*/
  INSERT INTO "station"("name") values("station1");
  INSERT INTO "station"("name") values("station2");
  INSERT INTO "station"("name") values("station3");
  INSERT INTO "station"("name") values("station4");
  INSERT INTO "station"("name") values("station5");
  /*train*/
  INSERT INTO "train"("name", "seat_num", "start_station", "end_station") values("train1", 10, 1, 2);
  INSERT INTO "train"("name", "seat_num", "start_station", "end_station") values("train2", 10, 1, 3);
  INSERT INTO "train"("name", "seat_num", "start_station", "end_station") values("train3", 10, 1, 4);
  INSERT INTO "train"("name", "seat_num", "start_station", "end_station") values("train4", 10, 1, 5);
  INSERT INTO "train"("name", "seat_num", "start_station", "end_station") values("train5", 10, 2, 1);
  INSERT INTO "train"("name", "seat_num", "start_station", "end_station") values("train6", 10, 2, 3);
  INSERT INTO "train"("name", "seat_num", "start_station", "end_station") values("train7", 10, 2, 4);
  INSERT INTO "train"("name", "seat_num", "start_station", "end_station") values("train8", 10, 2, 5);
  INSERT INTO "train"("name", "seat_num", "start_station", "end_station") values("train9", 10, 3, 1);
  INSERT INTO "train"("name", "seat_num", "start_station", "end_station") values("train10", 10, 3, 2);
  INSERT INTO "train"("name", "seat_num", "start_station", "end_station") values("train11", 10, 3, 4);
  INSERT INTO "train"("name", "seat_num", "start_station", "end_station") values("train12", 10, 3, 5);
  INSERT INTO "train"("name", "seat_num", "start_station", "end_station") values("train13", 10, 4, 1);
  INSERT INTO "train"("name", "seat_num", "start_station", "end_station") values("train14", 10, 4, 2);
  INSERT INTO "train"("name", "seat_num", "start_station", "end_station") values("train15", 10, 4, 3);
  INSERT INTO "train"("name", "seat_num", "start_station", "end_station") values("train16", 10, 4, 5);
  INSERT INTO "train"("name", "seat_num", "start_station", "end_station") values("train17", 10, 5, 1);
  INSERT INTO "train"("name", "seat_num", "start_station", "end_station") values("train18", 10, 5, 2);
  INSERT INTO "train"("name", "seat_num", "start_station", "end_station") values("train19", 10, 5, 3);
  INSERT INTO "train"("name", "seat_num", "start_station", "end_station") values("train20", 10, 5, 4);
COMMIT;
