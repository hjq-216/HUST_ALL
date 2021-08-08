-- 1)	编写一个依据人员编号计算其达到所有地点的次数的自定义函数，并利用其查询至少到达过3个地点的人员。
DROP PROCEDURE IF EXISTS Update_Level;
DELIMITER ;;
CREATE PROCEDURE Update_Level(in oldID INT,in oldTime DATE)
READS SQL DATA
DETERMINISTIC
BEGIN
	UPDATE customer_level SET borrowTimes = borrowTimes + 1 WHERE userID = oldID;
	UPDATE customer_level SET overTimes = overTimes + 1 WHERE userID = oldID AND CURRENT_DATE() > oldTime;
	UPDATE customer_level SET userLevel = userLevel+((borrowTimes - overTimes)/100) WHERE userID = oldID;
END;;
DELIMITER ;