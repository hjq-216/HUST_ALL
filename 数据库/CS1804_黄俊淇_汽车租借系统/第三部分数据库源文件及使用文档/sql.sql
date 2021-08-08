DROP TABLE IF EXISTS company CASCADE;
CREATE TABLE company(
	cName VARCHAR(20) NOT NULL PRIMARY KEY,
	cPassword VARCHAR(20) NOT NULL
);
INSERT INTO company VALUES('root','root');
INSERT INTO company VALUES('admin','root');

DROP TABLE IF EXISTS customer_level CASCADE;
DROP TABLE if EXISTS borrow; 
DROP TABLE if EXISTS borrowed;
DROP TABLE IF EXISTS customer;
CREATE TABLE customer(
	userID VARCHAR(20) NOT NULL PRIMARY KEY,
	username VARCHAR(20) NOT NULL,
	userPassword VARCHAR(20) NOT NULL
);
INSERT INTO customer VALUES('001','a','user');
INSERT INTO customer VALUES('002','b','user');
INSERT INTO customer VALUES('003','c','user');
INSERT INTO customer VALUES('004','d','user');
INSERT INTO customer VALUES('005','e','user');
INSERT INTO customer VALUES('006','f','user');
INSERT INTO customer VALUES('007','g','user');
INSERT INTO customer VALUES('008','h','user');
INSERT INTO customer VALUES('009','i','user');
INSERT INTO customer VALUES('010','j','user');
INSERT INTO customer VALUES('011','k','user');
INSERT INTO customer VALUES('012','l','user');
INSERT INTO customer VALUES('013','m','user');
INSERT INTO customer VALUES('014','n','user');
INSERT INTO customer VALUES('015','o','user');
INSERT INTO customer VALUES('016','p','user');
INSERT INTO customer VALUES('017','q','user');
INSERT INTO customer VALUES('018','r','user');
INSERT INTO customer VALUES('019','s','user');
INSERT INTO customer VALUES('020','t','user');

CREATE TABLE customer_level(
	userID VARCHAR(20) NOT NULL,
	borrowTimes INT NOT NULL DEFAULT 0,
	overTimes INT NOT NULL DEFAULT 0,
	userLevel INT NOT NULL DEFAULT 1,
	FOREIGN KEY(userID) REFERENCES customer(userID)
);
INSERT INTO customer_level VALUES('001',DEFAULT,DEFAULT,DEFAULT);
INSERT INTO customer_level VALUES('002',DEFAULT,DEFAULT,DEFAULT);
INSERT INTO customer_level VALUES('003',DEFAULT,DEFAULT,DEFAULT);
INSERT INTO customer_level VALUES('004',DEFAULT,DEFAULT,2);
INSERT INTO customer_level VALUES('005',DEFAULT,DEFAULT,2);
INSERT INTO customer_level VALUES('006',DEFAULT,DEFAULT,2);
INSERT INTO customer_level VALUES('007',DEFAULT,DEFAULT,DEFAULT);
INSERT INTO customer_level VALUES('008',DEFAULT,DEFAULT,DEFAULT);
INSERT INTO customer_level VALUES('009',DEFAULT,DEFAULT,DEFAULT);
INSERT INTO customer_level VALUES('010',DEFAULT,DEFAULT,DEFAULT);
INSERT INTO customer_level VALUES('011',DEFAULT,DEFAULT,DEFAULT);
INSERT INTO customer_level VALUES('012',DEFAULT,DEFAULT,DEFAULT);
INSERT INTO customer_level VALUES('013',DEFAULT,DEFAULT,DEFAULT);
INSERT INTO customer_level VALUES('014',DEFAULT,DEFAULT,DEFAULT);
INSERT INTO customer_level VALUES('015',DEFAULT,DEFAULT,DEFAULT);
INSERT INTO customer_level VALUES('016',DEFAULT,DEFAULT,DEFAULT);
INSERT INTO customer_level VALUES('017',DEFAULT,DEFAULT,DEFAULT);
INSERT INTO customer_level VALUES('018',DEFAULT,DEFAULT,DEFAULT);
INSERT INTO customer_level VALUES('019',DEFAULT,DEFAULT,DEFAULT);
INSERT INTO customer_level VALUES('020',DEFAULT,DEFAULT,DEFAULT);

DROP TABLE IF EXISTS car;
CREATE TABLE car(
	carID VARCHAR(20) NOT NULL PRIMARY KEY,
	carName VARCHAR(20) NOT NULL,
	carPrice VARCHAR(20) NOT NULL,
	borrowPrice VARCHAR(20) NOT NULL
);

INSERT INTO car VALUES('001','阿斯顿马丁','20000','500');
INSERT INTO car VALUES('002','法拉利','10000','400');
INSERT INTO car VALUES('003','奔驰','30000','300');
INSERT INTO car VALUES('004','宝马','40000','200');
INSERT INTO car VALUES('005','特斯拉','50000','100');
INSERT INTO car VALUES('006','阿斯顿马丁','20000','500');
INSERT INTO car VALUES('007','阿斯顿马丁','20000','500');
INSERT INTO car VALUES('008','阿斯顿马丁','20000','500');
INSERT INTO car VALUES('009','阿斯顿马丁','20000','500');
INSERT INTO car VALUES('010','阿斯顿马丁','20000','500');
INSERT INTO car VALUES('011','阿斯顿马丁','20000','500');
INSERT INTO car VALUES('012','阿斯顿马丁','20000','500');
INSERT INTO car VALUES('013','阿斯顿马丁','20000','500');
INSERT INTO car VALUES('014','阿斯顿马丁','20000','500');
INSERT INTO car VALUES('015','阿斯顿马丁','20000','500');
INSERT INTO car VALUES('016','阿斯顿马丁','20000','500');
INSERT INTO car VALUES('017','阿斯顿马丁','20000','500');
INSERT INTO car VALUES('018','阿斯顿马丁','20000','500');
INSERT INTO car VALUES('019','阿斯顿马丁','20000','500');
INSERT INTO car VALUES('020','阿斯顿马丁','20000','500');
INSERT INTO car VALUES('021','阿斯顿马丁','20000','500');
INSERT INTO car VALUES('022','阿斯顿马丁','20000','500');
INSERT INTO car VALUES('023','阿斯顿马丁','20000','500');
INSERT INTO car VALUES('024','阿斯顿马丁','20000','500');
INSERT INTO car VALUES('025','阿斯顿马丁','20000','500');
INSERT INTO car VALUES('026','阿斯顿马丁','20000','500');
INSERT INTO car VALUES('027','阿斯顿马丁','20000','500');
INSERT INTO car VALUES('028','阿斯顿马丁','20000','500');
INSERT INTO car VALUES('029','阿斯顿马丁','20000','500');
INSERT INTO car VALUES('030','阿斯顿马丁','20000','500');

CREATE TABLE borrow(
	userID VARCHAR(20) NOT NULL,
	carID VARCHAR(20) NOT NULL,
	carCondition VARCHAR(20) NOT NULL,
	borrowTime DATE NOT NULL,
	dueTime DATE NOT NULL,
	overTime VARCHAR(20) NOT NULL DEFAULT '否',
	FOREIGN KEY(userID) REFERENCES customer(userID),
	FOREIGN KEY(carID) REFERENCES car(carID)
);
INSERT INTO borrow VALUES('001','002','良好','2021-06-01','2021-06-03',DEFAULT);
INSERT INTO borrow VALUES('002','006','交通违规','2021-06-01','2021-06-03',DEFAULT);
INSERT INTO borrow VALUES('003','020','未加满油','2021-06-01','2021-06-03',DEFAULT);
INSERT INTO borrow VALUES('004','010','良好','2021-04-01','2021-04-03',DEFAULT);
INSERT INTO borrow VALUES('005','011','未加满油','2021-05-01','2021-05-03',DEFAULT);
INSERT INTO borrow VALUES('005','012','交通违规','2021-03-29','2021-03-31',DEFAULT);

CREATE TABLE borrowed(
	userID VARCHAR(20) NOT NULL,
	carID VARCHAR(20) NOT NULL,
	carCondition VARCHAR(20) NOT NULL,
	borrowTime DATE NOT NULL,
	dueTime DATE NOT NULL,
	overTime VARCHAR(20) NOT NULL DEFAULT '否',
	FOREIGN KEY(userID) REFERENCES customer(userID),
	FOREIGN KEY(carID) REFERENCES car(carID)
);
INSERT INTO borrow VALUES('001','003','良好','2021-06-01','2021-06-03',DEFAULT);
INSERT INTO borrow VALUES('002','009','交通违规','2021-06-01','2021-06-03',DEFAULT);

DROP TABLE IF EXISTS money;
CREATE TABLE money(
	moneyID INT NOT NULL PRIMARY KEY auto_increment,
	userID VARCHAR(20) NOT NULL,
	carID VARCHAR(20) NOT NULL,
	moneyTime DATE,
	moneyDetail VARCHAR(20),
	moneyback VARCHAR(20),
	price VARCHAR(20),
	back VARCHAR(20)
)auto_increment=1;
INSERT INTO money(userID,carID,moneyTime,moneyDetail,moneyback,price,back) VALUES('001','001','2020-12-31','+500','20000','500','20000');
INSERT INTO money(userID,carID,moneyTime,moneyDetail,moneyback,price,back) VALUES('002','002','2021-05-24','+1000','20000','500','20000');
INSERT INTO money(userID,carID,moneyTime,moneyDetail,moneyback,price,back) VALUES('003','003','2020-06-01','+1500','20000','500','20000');
INSERT INTO money(userID,carID,moneyTime,moneyDetail,moneyback,price,back) VALUES('004','004','2021-06-01','+500','20000','500','20000');
INSERT INTO money(userID,carID,moneyTime,moneyDetail,moneyback,price,back) VALUES('005','020','2019-06-01','+1000','20000','500','20000');
INSERT INTO money(userID,carID,moneyTime,moneyDetail,moneyback,price,back) VALUES('005','031','2019-06-01','+500','20000','500','20000');


-- 在用户注册后自动产生等级表

DROP TRIGGER IF EXISTS customer_trigger;
delimiter ;;
CREATE TRIGGER customer_trigger
AFTER INSERT ON customer
FOR EACH ROW
BEGIN
    INSERT INTO customer_level VALUES(new.userID,DEFAULT,DEFAULT,DEFAULT);
END;;
delimiter ;

-- 在还车后更新用户等级以及插入收支明细

DROP TRIGGER IF EXISTS borrow_trigger;
delimiter ;;
CREATE TRIGGER borrow_trigger
BEFORE DELETE ON borrow
FOR EACH ROW
BEGIN
    UPDATE customer_level SET borrowTimes = borrowTimes + 1 WHERE userID = old.userID;
		UPDATE customer_level SET overTimes = overTimes + 1 WHERE userID = old.userID AND CURRENT_DATE() > old.dueTime;
		UPDATE customer_level SET userLevel = userLevel+((borrowTimes - overTimes)/100) WHERE userID = old.userID;
		INSERT INTO borrowed VALUES(old.userID,old.carID,old.carCondition,old.borrowTime,old.dueTime,old.overTime);
		IF(old.carCondition = '良好')
    THEN 
		BEGIN
			DECLARE price1 VARCHAR(20);
			DECLARE back1 VARCHAR(20);
			DECLARE level1 INT;
			SET price1 = (SELECT borrowPrice FROM car WHERE carID = old.carID);
			SET back1 = (SELECT carPrice FROM car WHERE carID = old.carID);
			SET level1 = (SELECT userLevel FROM customer_level WHERE userID = old.userID);
			INSERT INTO money(userID,carID,moneyTime,moneyDetail,moneyback,price,back) VALUES(old.userID,old.carID,CURRENT_DATE()
				,CONCAT('+',CONVERT(CONVERT(TO_DAYS(CURRENT_DATE())-TO_DAYS(old.borrowTime),UNSIGNED)*CONVERT(price1,UNSIGNED)/level1,CHAR(20)))
				,back1,price1,back1) ;
		END;
		END IF;
		IF(old.carCondition = '未加满油')
    THEN 
		BEGIN
			DECLARE price1 VARCHAR(20);
			DECLARE back1 VARCHAR(20);
			DECLARE level1 INT;
			SET price1 = (SELECT borrowPrice FROM car WHERE carID = old.carID);
			SET back1 = (SELECT carPrice FROM car WHERE carID = old.carID);
			SET level1 = (SELECT userLevel FROM customer_level WHERE userID = old.userID);
			INSERT INTO money(userID,carID,moneyTime,moneyDetail,moneyback,price,back) VALUES(old.userID,old.carID,CURRENT_DATE()
				,CONCAT('+',CONVERT(CONVERT(TO_DAYS(CURRENT_DATE())-TO_DAYS(old.borrowTime),UNSIGNED)*CONVERT(price1,UNSIGNED)/level1+100,CHAR(20)))
				,CONVERT(CONVERT(back1,UNSIGNED)-100,char(20)),price1,back1) ;
		END;
		END IF;
		IF(old.carCondition = '交通违规')
    THEN 
		BEGIN
			DECLARE price1 VARCHAR(20);
			DECLARE back1 VARCHAR(20);
			DECLARE level1 INT;
			SET price1 = (SELECT borrowPrice FROM car WHERE carID = old.carID);
			SET back1 = (SELECT carPrice FROM car WHERE carID = old.carID);
			SET level1 = (SELECT userLevel FROM customer_level WHERE userID = old.userID);
			INSERT INTO money(userID,carID,moneyTime,moneyDetail,moneyback,price,back) VALUES(old.userID,old.carID,CURRENT_DATE()
				,CONCAT('+',CONVERT(CONVERT(TO_DAYS(CURRENT_DATE())-TO_DAYS(old.borrowTime),UNSIGNED)*CONVERT(price1,UNSIGNED)/level1+CONVERT(back1,UNSIGNED),CHAR(20)))
				,'0',price1,back1) ;
		END;
		END IF;
END;;