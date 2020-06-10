# Display the first and last name of the employee that has a first name 'Elvis' and is the oldest employee

SELECT first_name, last_name FROM employees WHERE first_name = 'Elvis' ORDER BY birth_date LIMIT 1;
