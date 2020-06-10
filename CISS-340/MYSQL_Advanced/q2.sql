# Display the first name and last name as well as department name of all department managers. SORT by department name, last name, first name

SELECT first_name, last_name, dept_name FROM dept_manager NATURAL JOIN departments NATURAL JOIN employees
