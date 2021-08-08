-- 2批处理
DROP TABLE IF EXISTS location_record_2;
CREATE TABLE location_record_2 AS(
	SELECT * FROM itinerary
	WHERE loc_id = 2
);

-- 4观察性实验
DROP TABLE IF EXISTS observe2;
CREATE TABLE observe2(
	a INT,
	b INT
);
INSERT INTO observe2(a,b) VALUES(1,1);
INSERT INTO observe2(a,b) VALUES(1,1);
INSERT INTO observe2(a,b) VALUES(1,1);

-- 5触发器
delimiter ;;
DROP TRIGGER IF EXISTS mytrigger1;
CREATE TRIGGER mytrigger1
AFTER UPDATE ON diagnose_record
FOR EACH ROW
BEGIN
    UPDATE isolation_record SET state = 3 WHERE(p_id = new.p_id AND new.result = 1);
END;;

delimiter ;;
DROP TRIGGER IF EXISTS mytrigger2;
CREATE TRIGGER mytrigger2
AFTER INSERT ON diagnose_record
FOR EACH ROW
BEGIN
		IF(new.result = 1)
    THEN 
		BEGIN
			INSERT INTO isolation_record VALUES(new.id,new.p_id,NULL,NULL,3,3);
		END;
		ELSE INSERT INTO isolation_record VALUES(new.id,new.p_id,NULL,NULL,3,1);
		END IF;
END;;

-- INSERT INTO diagnose_record VALUES(11,3,NULL,1);
-- UPDATE diagnose_record set result = 3 WHERE id = 11;
-- UPDATE isolation_record set state = 1 WHERE id = 11;
UPDATE diagnose_record set result = 1 WHERE id = 11;
