# You will two queries for this one. It can be done in one but too much copying.
# Using the previous query, create a view (this will help you from copy pasting it) and display the ratio of women to men for each department. Display department and ratio rounded in 2 decimals points.
# For the view use: CREATE OR REPLACE VIEW
# Otherwise scripts will fail if a view exists

CREATE OR REPLACE VIEW genRatio 
	AS SELECT dept_name, gender, count(gender) as genCount 
    	FROM employees NATURAL JOIN departments NATURAL JOIN dept_emp 
        	GROUP BY dept_name, gender;

SELECT Female.dept_name, ROUND((Female.genCount) / (Male.genCount), 2) AS genRatio
	FROM genRatio Female, genRatio Male
    	WHERE Female.gender = "F" and Male.gender = "M" and Female.dept_name = Male.dept_name
        	GROUP BY Male.dept_name
