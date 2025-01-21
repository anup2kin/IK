-- 1. Fetch the names of all venues in the city of 'Washington,' arranging them
-- 	alphabetically using the venue table.
select *
from venue
order by venuename asc

-- 2. Craft an SQL query to identify and rank the top 10 events with the highest
--	attendance (assume each sold ticket is an attendance count).
--	Utilize the event table to extract key details, including event names and attendance
--	figures, presenting them in descending order based on attendance.
select S.eventid, E.eventname, SUM(S.qtysold) AS attendance,
	RANK() OVER (ORDER BY SUM(S.qtysold) DESC) as rnk
from sales S
INNER JOIN event E ON E.eventid = S.eventid
GROUP BY S.eventid, E.eventname
ORDER BY SUM(S.qtysold) DESC
LIMIT 10

-- 3. Construct an SQL query to retrieve events that occurred on a specific date say ‘2008-08-21’,
--	leveraging both the event and date tables.
--	The query should extract event details, including names and start times, associated with the specified date.
SELECT E.eventname, E.starttime, D.year,
	D.month,
	D.day
FROM event E
INNER JOIN date D ON D.dateid = E.dateid
WHERE CAST(EXTRACT(YEAR FROM CAST(E.starttime AS DATE)) AS INTEGER) = D.year
  AND CAST(TO_CHAR(CAST(E.starttime AS DATE), 'MON') AS VARCHAR(255)) = D.month
  AND CAST(SUBSTRING(TRIM(' ' FROM TO_CHAR(CAST(E.starttime AS DATE), 'DAY')), 0, 3) AS VARCHAR(255)) = D.day;

-- 4. Identify the seller who has listed the highest number of tickets utilizing the listing table.
SELECT L.sellerid, SUM(L.numtickets) AS total_tickets_listed
FROM listing L
GROUP BY L.sellerid
ORDER BY total_tickets_listed DESC
LIMIT 1;

-- 5. Create an SQL query to list categories alongside the total number of events in each category.
--	Utilize the category and event tables to extract and aggregate relevant information.
SELECT C.catid, C.catname, COUNT(E.eventid) AS total_num_events
FROM category C
INNER JOIN event E ON E.catid = C.catid
GROUP BY C.catid, C.catname

-- 6. Formulate an SQL query to calculate the total commission earned by all sellers combined for all
--	events in a specific city, for instance, 'Kansas City’ utilizing the sales, event and venue tables
--	to extract relevant information required.
SELECT S.sellerid, V.venuecity, SUM(S.commission) AS total_commision
FROM sales S
INNER JOIN event E ON E.eventid = S.eventid
INNER JOIN venue V ON V.venueid = E.venueid
GROUP BY S.sellerid, V.venuecity
ORDER BY S.sellerid

-- 7. Devise an SQL query to calculate the average ticket price for each event category.
--	Utilizing the category, event, and sales tables, extract relevant information and compute the average
--	ticket price by considering the ratio of total price paid* to the quantity sold for each event.
--	* Interpret for each individual row ‘pricepaid’ as total price paid for ‘qtysold’ number of tickets
SELECT C.catId, C.catname, (SUM(S.pricepaid) / SUM(S.qtysold)) AS avg_ticket_price
FROM category C
INNER JOIN event E ON E.catid = C.catid
INNER JOIN sales S ON S.eventid = E.eventid
GROUP BY C.catid, C.catname




