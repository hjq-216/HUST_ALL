-- 1) 查询累计人流量大于30的地点名称和累计人流量，累积人流量请用visitors作标题名称。
--    查询结果按照人流量从高到低排序，人流量相同时，依地点名称的字典顺序排序。
--    （注意：同一人多次逛同一地点，去几次算几次）
--    请用一条SQL语句实现该查询：
select *
from (
    select location_name,count(loc_id) as visitors
    from location,itinerary
    where location.id = itinerary.loc_id
    group by location.id
    having count(loc_id)>30
) tmp
order by visitors desc,location_name;

-- 2) 查询每个隔离地及该地正在进行隔离的人数，以number为隔离人数的标题.
--    查询结果依隔离人数由多到少排序。人数相同时，依隔离地点名排序。
--    请用一条SQL语句实现该查询：

select *
from(
    select location_name,count(p_id) as number
    from isolation_record,isolation_location
    where isolation_location.id = isolation_record.isol_loc_id
    and state = 1
    group by isolation_location.id
) tmp
order by number desc,location_name;

-- 3) 查询行程表中所有属于同一个人的接续行程信息。输出内容包括：
-- 人员编号,姓名,重合时间,起始地点id,起始地点,结束地点id,结束地点。
-- 查询结果依人员编号排序。
-- 请用一条SQL语句实现该查询：
select person.id,
       person.fullname,
       person.telephone,
       t1.e_time        as reclosing_time,
       t1.loc_id        as loc1,
       l1.location_name as address1,
       t2.loc_id        as loc2,
       l2.location_name as address2
from person,
     location l1,
     location l2,
     itinerary t1,
     itinerary t2
where person.id > 30
  and person.id = t1.p_id
  and l1.id = t1.loc_id
  and l2.id = t2.loc_id
  and t1.p_id = t2.p_id
  and t1.e_time = t2.s_time
order by person.id, reclosing_time;
-- 4) 查询充珉瑶和贾涵山的行程情况。查询结果包括：姓名、电话、到过什么地方（地名），何时到达，何时离开 。
--  列名原样列出，不必用别名。查询结果依人员编号降序排序。
select a.fullname,a.telephone,tmp.location_name,tmp.s_time,tmp.e_time
from person a left join(
    select b.fullname,location.location_name,s_time,e_time
    from person b,location,itinerary
    where b.id = itinerary.p_id 
    and itinerary.loc_id = location.id
) tmp
on a.fullname = tmp.fullname
where a.fullname in ("充珉瑶","贾涵山")
order by a.id desc,s_time;
-- 5) 查询地名中带有‘店’字的地点编号和名称。查询结果按地点编号排序。
--    请用一条SQL语句实现该查询：

select id, location_name
from location
where location_name like "%店%"
order by id;

-- 6) 新发现一位确诊者，已知他在2021.2.2日20:05:40到21:25:40之间在“活动中心”逗留，
--    凡在此间在同一地点逗留过的，视为接触者，请查询接触者的姓名和电话。查询结果按姓名排序.
--    请用一条SQL语句实现该查询：
select fullname, telephone
from person,
     itinerary,
     location
where person.id = itinerary.p_id
  and itinerary.loc_id = location.id
  and location_name = "活动中心"
  and (itinerary.s_time between "2021-02-02 20:05:40" and "2021-02-02 21:25:40"
    or itinerary.e_time between "2021-02-02 20:05:40" and "2021-02-02 21:25:40"
    or "2021-02-02 20:05:40" between itinerary.s_time and itinerary.e_time)
order by fullname;

-- 7) 查询正在使用的隔离点名,查询结果按隔离点的编号排序。
--    请用一条SQL语句实现该查询：
# 查询仍在使用的隔离点名称。注意，隔离记录里如果只有隔离结束或确诊转院的记录，
# 表明该隔离点已暂时停用，只要还有一个人在此处隔离，
# 表明该隔离点仍在使用。查询结果按隔离点编号排序。
select location_name 
from isolation_location 
where exists(
    select *
    from isolation_record
    where isolation_location.id = isolation_record.isol_loc_id
    and state = 1
)
order by id;

-- 8) 用一条带exists关键字的SQL语句查询前30位有出行记录的人员姓名和电话。查询结果按照人员编号排序。
--    请用一条SQL语句实现该查询：
select fullname, telephone
from person
where exists(
              select *
              from itinerary
              where person.id = itinerary.p_id
          )
order by person.id
limit 30
;

-- 9) 写一条带NOT EXISTS 子查询的SQL语句实现下述查询要求：
--   查询人员表中没有去过地点“Today便利店”的人数。请给统计出的人数命名为number。
--   请用一条SQL语句实现该查询：
select count(person.id) as number
from person
where not exists(
        select *
        from itinerary,
             location
        where person.id = itinerary.p_id
          and itinerary.loc_id = location.id
          and location.location_name = "Today便利店"
    );

-- 10) 查询人员表中去过所有地点的人员姓名。查询结果依人员姓名的字典顺序排序。
--    请用一条SQL语句实现该查询：

select fullname
from person
where not exists(
        select *
        from location
        where location.id not in (
            select itinerary.loc_id
            from itinerary
            where itinerary.loc_id = location.id
              and person.id = itinerary.p_id
        )
    )
order by fullname;

-- 11) 建立反映所有隔离点现状的视图isolation_location_status。
-- 内容包括：地点编号，隔离地点名，房间容量，已占用量
-- 请保持原列名不变，已占用量由统计函籹计算得出，该列命名为occupied。
-- 正在隔离的人占用着隔离点的位置，隔离结束或已转院的人不占用位置。

create view isolation_location_status as
select l.id, l.location_name, l.capacity, ifnull(tmp.cut, 0) as occupied
from isolation_location l left join (
    select r.isol_loc_id, count(r.isol_loc_id) as cut
    from isolation_record r
    where r.state = 1
    group by r.isol_loc_id
) tmp
on l.id = tmp.isol_loc_id;

-- 12) 从视图isolation_location_status中查询各隔离点的剩余空房间的数目。
--    需要列出的数据项：隔离点名称，剩余房间数。其中剩余房间数为计算得出，请给该列命名为available_rooms
--    查询结果依隔离点编号排序。
--    请用一条SQL语句实现该查询：
select location_name, capacity - occupied as available_rooms
from isolation_location_status
order by id;

-- 13) 筛查发现，靳宛儿为无症状感染者。现需查询其接触者姓名名单和电话，以便通知并安排隔离。查询结题按姓名排序。
--    凡行程表中，在同一地点逗留时间与靳宛儿有交集的，均视为接触者。
--    请用一条SQL语句实现该查询：
select fullname, telephone
from person,
     itinerary,
     (
         select i.loc_id, i.s_time, i.e_time
         from person p,
              itinerary i
         where p.id = i.p_id
           and p.fullname = "靳宛儿"
     ) tmp
where person.fullname <> "靳宛儿"
  and person.id = itinerary.p_id
  and itinerary.loc_id = tmp.loc_id
  and (
        itinerary.s_time between tmp.s_time and tmp.e_time
        or itinerary.e_time between tmp.s_time and tmp.e_time
        or tmp.s_time between itinerary.s_time and itinerary.e_time
        or tmp.e_time between itinerary.s_time and itinerary.e_time
    )
order by fullname;
-- 14) 依据密切接触表的内容查询每个地点的密切接触者的数量，列出内容包括：地点名称，密接者人数。
--     人数由统计获得，列名命名为close_contact_number.查询结果依密接者人数降序排列。
--     密接者人数相同时，依地点名称排序。
--    请用一条SQL语句实现该查询：
select *
from (
         select location_name, count(loc_id) as close_contact_number
         from location,
              close_contact
         where location.id = close_contact.loc_id
         group by close_contact.loc_id
     ) tmp
order by close_contact_number desc, location_name;
-- 15) 查询感染人数最多的人员编号，姓名，和被其感染的人数。
--     感染人数由统计所得，命名为infected_number.
--    请用一条SQL语句实现该查询：
select case_p_id, fullname, count(case_p_id) as infected_number
from close_contact,
     person
where person.id = close_contact.case_p_id
group by case_p_id
order by infected_number desc
limit 1;
-- 16) 查询2021-02-02 10:00:00到14:00:00期间，行程记录最频繁的3个人的姓名及行程记录条数。
--     记录条数命名为record_number. 记录数并列的，按姓名顺序排列。
--    请用一条SQL语句实现该查询：
select *
from (
         select fullname, count(p_id) as record_number
         from person,
              itinerary
         where person.id = itinerary.p_id
           and (itinerary.s_time between "2021-02-02 10:00:00" and "2021-02-02 14:00:00"
             or itinerary.e_time between "2021-02-02 10:00:00" and "2021-02-02 14:00:00"
             or "2021-02-02 10:00:00" between itinerary.s_time and itinerary.e_time)
         group by itinerary.p_id) tmp
order by record_number desc, fullname
limit 3;
-- 17 查询隔离点中，房间数第二多的隔离点名称和房间数。
--    请用一条SQL语句实现该查询：
select location_name, capacity
from isolation_location
where capacity = (select distinct capacity
                  from isolation_location
                  order by capacity desc
                  limit 1,1);