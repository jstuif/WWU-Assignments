# How many women and how many men are working on each department. Display dept name, gender and number of people working

SELECT dept_name, gender, count(gender) as genCount FROM employees NATURAL JOIN departments NATURAL JOIN dept_emp GROUP BY dept_name, gender
