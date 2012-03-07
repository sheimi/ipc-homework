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

DROP TABLE IF EXISTS "sell_log";
CREATE TABLE "sell_log" (
  id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
  user_id INTEGER NOT NULL,
  seat_id INTEGER NOT NULL,
  buy_date DATETIME NOT NULL,
  start_station INTEGER NOT NULL,
  end_station   INTEGER NOT NULL,
  FOREIGN KEY(user_id) REFERENCES "user"(id),
  FOREIGN KEY(start_station) REFERENCES "station"(id),
  FOREIGN KEY(end_station) REFERENCES "station"(id),
  FOREIGN KEY(seat_id) REFERENCES "seat"(id)
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
  INSERT INTO "station"("name") values("station6");
  INSERT INTO "station"("name") values("station7");
  INSERT INTO "station"("name") values("station8");
  INSERT INTO "station"("name") values("station9");
  INSERT INTO "station"("name") values("station10");
  INSERT INTO "station"("name") values("station11");
  INSERT INTO "station"("name") values("station12");
  INSERT INTO "station"("name") values("station13");
  INSERT INTO "station"("name") values("station14");
  INSERT INTO "station"("name") values("station15");
  INSERT INTO "station"("name") values("station16");
  INSERT INTO "station"("name") values("station17");
  INSERT INTO "station"("name") values("station18");
  INSERT INTO "station"("name") values("station19");
  INSERT INTO "station"("name") values("station20");
  /*train*/
  INSERT INTO "train"("name", "seat_num") values("train1", 10);
  INSERT INTO "train"("name", "seat_num") values("train2", 10);
  /*seat*/
  INSERT INTO "seat"("num", "train_id") values(1, 1);
  INSERT INTO "seat"("num", "train_id") values(2, 1);
  INSERT INTO "seat"("num", "train_id") values(3, 1);
  INSERT INTO "seat"("num", "train_id") values(4, 1);
  INSERT INTO "seat"("num", "train_id") values(5, 1);
  INSERT INTO "seat"("num", "train_id") values(6, 1);
  INSERT INTO "seat"("num", "train_id") values(7, 1);
  INSERT INTO "seat"("num", "train_id") values(8, 1);
  INSERT INTO "seat"("num", "train_id") values(9, 1);
  INSERT INTO "seat"("num", "train_id") values(10, 1);
  INSERT INTO "seat"("num", "train_id") values(1, 2);
  INSERT INTO "seat"("num", "train_id") values(2, 2);
  INSERT INTO "seat"("num", "train_id") values(3, 2);
  INSERT INTO "seat"("num", "train_id") values(4, 2);
  INSERT INTO "seat"("num", "train_id") values(5, 2);
  INSERT INTO "seat"("num", "train_id") values(6, 2);
  INSERT INTO "seat"("num", "train_id") values(7, 2);
  INSERT INTO "seat"("num", "train_id") values(8, 2);
  INSERT INTO "seat"("num", "train_id") values(9, 2);
  INSERT INTO "seat"("num", "train_id") values(10, 2);
COMMIT;
