-- 观察性实验1
DROP TABLE IF EXISTS observe1;
CREATE TABLE observe1(
	name CHAR(20) NOT NULL,
	FOREIGN KEY(name) REFERENCES person(fullname)
);