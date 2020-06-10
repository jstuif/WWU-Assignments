# Display the age of the oldest employee (as an int) in absolute years (assuming they are still working there)

SELECT ROUND(DATEDIFF(CURRENT_DATE, birth_date)/365) FROM employees ORDER BY ROUND(DATEDIFF(CURRENT_DATE, birth_date)/365) DESC Limit 1;
