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