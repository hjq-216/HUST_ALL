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
    CALL Update_Level(old.userID,old.dueTime);
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


INSERT INTO borrow VALUES('004','021','良好','2021-05-31','2021-06-03',DEFAULT);
DELETE FROM borrow WHERE carID = '021';
INSERT INTO borrow VALUES('005','022','未加满油','2021-05-31','2021-06-02',DEFAULT);
DELETE FROM borrow WHERE carID = '022';
INSERT INTO borrow VALUES('006','023','交通违规','2021-05-31','2021-06-03',DEFAULT);
DELETE FROM borrow WHERE carID = '023';

