-- 1)	编写一个依据人员编号计算其达到所有地点的次数的自定义函数，并利用其查询至少到达过3个地点的人员。
DROP FUNCTION IF EXISTS Count_Records;
DELIMITER ;;
CREATE FUNCTION Count_Records(a int)
RETURNS INT
READS SQL DATA
DETERMINISTIC
BEGIN
	DECLARE c INT;
	SELECT count(*) INTO c FROM itinerary WHERE p_id = a;
	RETURN c;
END;;
DELIMITER ;

/*
(2) 利用创建的函数，仅用一条SQL语句查询在行程表中至少有3条行程记录的人员信息，查询结果依人员编号排序。*/

SELECT * FROM person WHERE Count_Records(id)>=3;

-- 2)	尝试编写DBMS的存储过程，建立每个隔离点的人数统计表，并通过存储过程更新该表。
DROP TABLE IF EXISTS location_count;
CREATE TABLE location_count(
	loc_id INT PRIMARY KEY NOT NULL,
	times INT NOT NULL,
	FOREIGN KEY(loc_id) REFERENCES isolation_location(id)
);

DROP PROCEDURE IF EXISTS sumLocId;
DELIMITER ;;
CREATE PROCEDURE sumLocId()
BEGIN
	INSERT INTO location_count SELECT isol_loc_id,COUNT(*) FROM isolation_record GROUP BY isolation_record.isol_loc_id;
END;;

CALL sumLocId();