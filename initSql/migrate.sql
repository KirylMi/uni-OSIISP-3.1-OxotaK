-- SQLINES DEMO *** sktop version to convert large SQL scripts,
-- SQLINES DEMO *** ny issues with Online conversion.

-- SQLINES DEMO *** act us at support@sqlines.com-- MySQL Script generated by MySQL Workbench
-- SQLINES DEMO *** 53 2020
-- SQLINES DEMO ***    Version: 1.0
-- SQLINES DEMO *** orward Engineering

/* SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0; */
/* SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0; */
/* SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION'; */

-- SQLINES DEMO *** ------------------------------------
-- Schema "oxotaK"
-- SQLINES DEMO *** ------------------------------------

-- SQLINES DEMO *** ------------------------------------
-- Schema "oxotaK"
-- SQLINES DEMO *** ------------------------------------
CREATE SCHEMA "oxotaK";

-- SQLINES DEMO *** ------------------------------------
-- SQLINES DEMO *** sers`
-- SQLINES DEMO *** ------------------------------------
 CREATE SEQUENCE "oxotaK".users_seq;

CREATE TABLE IF NOT EXISTS "oxotaK".users (
  id INT NOT NULL DEFAULT NEXTVAL ('"oxotaK".users_seq'),
  username VARCHAR(45) NOT NULL,
  name VARCHAR(45) NOT NULL,
  password VARCHAR(45) NOT NULL,
  is_active SMALLINT NOT NULL DEFAULT 0,
  description TEXT NOT NULL,
  PRIMARY KEY (id),
  UNIQUE (username ) ,
  UNIQUE  (name ) ,
  UNIQUE  (id )
);


-- SQLINES DEMO *** ------------------------------------
-- SQLINES DEMO *** rinks_type`
-- SQLINES DEMO *** ------------------------------------
CREATE SEQUENCE "oxotaK".drinks_type_seq;

CREATE TABLE IF NOT EXISTS "oxotaK".drinks_type (
  id INT NOT NULL DEFAULT NEXTVAL ('"oxotaK".drinks_type_seq'),
  type VARCHAR(45) NOT NULL,
  PRIMARY KEY (id),
  UNIQUE (id ) ,
  UNIQUE  (type )
);


-- SQLINES DEMO *** ------------------------------------
-- SQLINES DEMO *** rinks`
-- SQLINES DEMO *** ------------------------------------
CREATE SEQUENCE "oxotaK".drinks_seq;

CREATE TABLE IF NOT EXISTS "oxotaK".drinks (
  id INT NOT NULL DEFAULT NEXTVAL ('"oxotaK".drinks_seq'),
  name VARCHAR(45) NOT NULL,
  photo BYTEA NOT NULL,
  info TEXT NOT NULL,
  drinks_type_id INT NOT NULL references "oxotaK".drinks_type (id),
  PRIMARY KEY (id),
  UNIQUE (id ) ,
  UNIQUE (name ) ,
  UNIQUE (info )
  --foreign key (drinks_type_id) references "oxotaK".drinks_type (id)
  );
  --CONSTRAINT fk_drinks_drinks_type
  --  FOREIGN KEY (drinks_type_id)
  --  REFERENCES "oxotaK".drinks_type (id)
  --  ON DELETE CASCADE
  --  ON UPDATE CASCADE)
--alter table "oxotaK".drinks
--	add constraint fk_drinks_drinks_types
--	foreign key (drinks_type_id)
--	REFERENCES "oxotaK".drinks_type (id);


-- SQLINES DEMO *** ------------------------------------
-- SQLINES DEMO *** pproval`
-- SQLINES DEMO *** ------------------------------------
CREATE TABLE IF NOT EXISTS "oxotaK".approval (
  new_user_id INT NOT NULL REFERENCES "oxotaK".users (id),
  approval_id INT NOT NULL REFERENCES "oxotaK".users (id),
  UNIQUE(new_user_id,approval_id)
--  CONSTRAINT fk_approval_users1
--    FOREIGN KEY (new_user_id)
--    REFERENCES "oxotaK".users (id)
--    ON DELETE CASCADE
--    ON UPDATE CASCADE,
--  CONSTRAINT fk_approval_users2
--    FOREIGN KEY (approval_id)
--    REFERENCES "oxotaK".users (id)
--    ON DELETE CASCADE
--    ON UPDATE CASCADE)
);


-- SQLINES DEMO *** ------------------------------------
-- SQLINES DEMO *** eviews`
-- SQLINES DEMO *** ------------------------------------
CREATE TABLE IF NOT EXISTS "oxotaK".reviews (
  users_id INT NOT NULL REFERENCES "oxotaK".users (id),
  drinks_id INT NOT NULL REFERENCES "oxotaK".drinks (id) ON DELETE CASCADE,
  comment TEXT NOT NULL,
  mark INT NOT NULL,
  PRIMARY KEY (users_id, drinks_id)
--  CONSTRAINT fk_users_has_drinks_users1
--    FOREIGN KEY (users_id)
--    REFERENCES "oxotaK".users (id)
--    ON DELETE CASCADE
--    ON UPDATE CASCADE,
--  CONSTRAINT fk_users_has_drinks_drinks1
--    FOREIGN KEY (drinks_id)
--    REFERENCES "oxotaK".drinks (id)
--    ON DELETE NO ACTION
--    ON UPDATE NO ACTION)
);

INSERT INTO "oxotaK".users(
	username, name, password, is_active, description)
	VALUES ('Dendel228', 'C0K01', '098f6bcd4621d373cade4e832627b4f6', 1, 'Foundation member');

INSERT INTO "oxotaK".drinks_type(
	type)
	VALUES ('Soda'), ('Beer'), ('Vodka');

/* SET SQL_MODE=@OLD_SQL_MODE; */
/* SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS; */
/* SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS; */
