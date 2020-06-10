# Display the sex and counts of employees for each sex

SELECT gender, COUNT(*) AS amount FROM employees GROUP BY gender HAVING amount > 1;
