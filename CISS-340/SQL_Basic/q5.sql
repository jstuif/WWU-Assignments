# Display the first name, last name and rounded years worked of all employees sorted in a desceding order based on the rounded years

SELECT first_name, last_name, ROUND(DATEDIFF(CURRENT_DATE, hire_date)/365) FROM employees ORDER BY ROUND(DATEDIFF(CURRENT_DATE, hire_date)/365) DESC;
