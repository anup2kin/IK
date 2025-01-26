-- SQL first ASSIGNMENT
-- 1. Fetch the names of all venues in the city of 'Washington,' arranging them
-- 	alphabetically using the venue table.
select *
from venue
WHERE venue.venuecity = 'Washington'
order by venuename asc;

-- 2. Craft an SQL query to identify and rank the top 10 events with the highest
--	attendance (assume each sold ticket is an attendance count).
--	Utilize the event table to extract key details, including event names and attendance
--	figures, presenting them in descending order based on attendance.
select E.eventname,
	SUM(S.qtysold) AS attendance
from sales S
INNER JOIN event E ON E.eventid = S.eventid
GROUP BY E.eventname
ORDER BY attendance DESC
LIMIT 10;

-- 3. Construct an SQL query to retrieve events that occurred on a specific date say ‘2008-08-21’,
--	leveraging both the event and date tables.
--	The query should extract event details, including names and start times, associated with the specified date.
SELECT E.eventname, E.starttime,
	D.year, D.month, D.day
FROM event E
INNER JOIN date D ON D.dateid = E.dateid
WHERE CAST(EXTRACT(YEAR FROM CAST(E.starttime AS DATE)) AS INTEGER) = D.year
  AND CAST(TO_CHAR(CAST(E.starttime AS DATE), 'MON') AS VARCHAR(255)) = D.month
  AND CAST(SUBSTRING(TRIM(' ' FROM TO_CHAR(CAST(E.starttime AS DATE), 'DAY')), 0, 3) AS VARCHAR(255)) = D.day;

SELECT E.eventname, E.starttime, D.caldate
FROM event E
INNER JOIN date D ON D.dateid = E.dateid
WHERE D.caldate = '2008-08-21';
  
-- 4. Identify the seller who has listed the highest number of tickets utilizing the listing table.
SELECT L.sellerid, 
	SUM(L.numtickets) AS total_tickets_listed
FROM listing L
GROUP BY L.sellerid
ORDER BY total_tickets_listed DESC
LIMIT 1;

-- 5. Create an SQL query to list categories alongside the total number of events in each category.
--	Utilize the category and event tables to extract and aggregate relevant information.
SELECT C.catname, 
	COUNT(E.eventid) AS total_num_events
FROM category C
LEFT JOIN event E ON E.catid = C.catid
GROUP BY C.catname;

-- 6. Formulate an SQL query to calculate the total commission earned by all sellers combined for all
--	events in a specific city, for instance, 'Kansas City’ utilizing the sales, event and venue tables
--	to extract relevant information required.
SELECT SUM(S.commission) AS total_comission
FROM sales S
INNER JOIN event E ON E.eventid = S.eventid
INNER JOIN venue V ON V.venueid = E.venueid
WHERE V.venuecity = 'Kansas City';


SELECT S.sellerid, V.venuecity, 
	SUM(S.commission) AS total_commision
FROM sales S
INNER JOIN event E ON E.eventid = S.eventid
INNER JOIN venue V ON V.venueid = E.venueid
GROUP BY S.sellerid, V.venuecity
ORDER BY S.sellerid;

-- 7. Devise an SQL query to calculate the average ticket price for each event category.
--	Utilizing the category, event, and sales tables, extract relevant information and compute the average
--	ticket price by considering the ratio of total price paid* to the quantity sold for each event.
--	* Interpret for each individual row ‘pricepaid’ as total price paid for ‘qtysold’ number of tickets
SELECT C.catname, 
	AVG(S.pricepaid / S.qtysold) AS avg_ticket_price
FROM category C
INNER JOIN event E ON E.catid = C.catid
INNER JOIN sales S ON S.eventid = E.eventid
WHERE S.qtysold IS NOT NULL OR S.qtysold <> 0
GROUP BY C.catname;


-- 8. Determine the total sales and average commission for each event category by creating an SQL subquery
--	using ‘WITH’. Make use of the category, event, and sales tables strategically to calculate both total
--	sales and average commission.
WITH sales_data_per_cat_id AS
(
	SELECT E.catid,
		COUNT(S.salesid) as total_sales,
		AVG(S.commission) as avg_comission
	FROM sales S
	LEFT JOIN event E ON E.eventid = S.eventid
	GROUP BY E.catid
)

SELECT *
FROM Category C
LEFT JOIN sales_data_per_cat_id S ON S.catid = C.catid
WHERE S.catid IS NOT NULL;

-- 9. Generate an SQL query to create a view that displays events with a total revenue exceeding 50,000.
--	using the sales table and appropriate grouping and conditions.
CREATE VIEW high_revenue_events AS
	SELECT E.eventname, SUM(S.pricepaid) AS total_revenue 
	FROM event E
	INNER JOIN sales S ON E.eventid = S.eventid
	GROUP BY E.eventname
	HAVING SUM(S.pricepaid) > 50000;

SELECT * FROM high_revenue_events;


-- 10. Devise an SQL query to compare the total tickets sold on each day with the previous day. Utilize
--	the sales table, strategically grouping and employing functions like 'LAG' to compute the difference 
--	in total tickets sold between consecutive days. Display the list of date ids ordered and the
--	corresponding totalson that current date and the previous date.
SELECT dateid, 
	SUM(qtysold) AS total_day_sales,
	LAG(SUM(qtysold)) OVER (ORDER BY dateid) AS previous_day_total_sales
FROM sales
GROUP BY dateid
ORDER BY dateid;

