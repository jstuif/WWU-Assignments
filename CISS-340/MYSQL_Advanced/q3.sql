#  Which employee got the largest salary increase since they started working in the company? (display emp_no, salary increase in percentage rounded in 2 decimal places, e.g., 100%)

SELECT emp_no, ROUND((((MAX(salary) / MIN(salary))) * 100.0), 2) AS percent FROM salaries GROUP BY emp_no ORDER BY percent DESC LIMIT 1
