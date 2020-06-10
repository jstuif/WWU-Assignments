import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.sql.*;

/*
    Joshua Stuifbergen
    5/18/19
    CISS 340
    MySQLJava
*/

class mysqlJava {

    public static void main(String[] args) throws Exception{

        //Below works if a text file is not used for the path
        //String url = "jdbc:mysql://localhost/employees?useUnicode=true&useJDBCCompliantTimezoneShift=true&useLegacyDatetimeCode=false&serverTimezone=UTC";
        //Connection con = DriverManager.getConnection(url, "guest2", "password");

        //I used Dylan's method to grab to string from the credentials.txt file
        Path varFile = Paths.get("credentials.txt");
        String varString = Files.lines(varFile).findFirst().get();
        Connection con = DriverManager.getConnection(varString);
        Statement pst = con.createStatement();
        try {
                //function to show all employees of a specified department
                if (args[0].equals("show") && args[1].equals("employees") && args[2].equals("departments")) {
                    ResultSet rs = pst.executeQuery("SELECT emp_no, first_name, last_name FROM employees NATURAL JOIN departments NATURAL JOIN dept_emp WHERE dept_name = \"" + args[3] + "\" ");
                    while (rs.next()) {
                        System.out.printf("%-22s%-22s%-22s\n", rs.getInt(1), rs.getString(2), rs.getString(3));
                    }
                    //This function adds a new employee with multiple pieces of information into the tables: employees,
                    //salaries, and dept_emp.
                } else if(args[0].equals("add") && args[1].equals("employee")) {
                    //Grabbing the highest emp_no and adding 1 to it for the new employee
                    ResultSet rs = pst.executeQuery("SELECT emp_no FROM employees ORDER BY emp_no DESC LIMIT 1");
                    rs.next();
                    int tempNum = rs.getInt(1) + 1;

                    //insert into employees table
                    String query = " insert into employees (birth_date, emp_no, first_name, gender, hire_date, last_name)"
                            + " values (?, ?, ?, ?, ?, ?)";

                    PreparedStatement preparedStmt = con.prepareStatement(query);
                    preparedStmt.setString(1 , args[5]);
                    preparedStmt.setInt(2, tempNum);
                    preparedStmt.setString (3, args[2]);
                    preparedStmt.setString (4, args[6]);
                    preparedStmt.setDate(5, new java.sql.Date(System.currentTimeMillis()));
                    preparedStmt.setString (6, args[3]);

                    preparedStmt.execute();

                    // insert into salaries table
                    String query2 = " insert into salaries (emp_no, from_date, salary, to_date)"
                            + " values (?, ?, ?, ?)";

                    PreparedStatement preparedStmt2 = con.prepareStatement(query2);
                    preparedStmt2.setInt(1, tempNum);
                    preparedStmt2.setDate(2, new java.sql.Date(System.currentTimeMillis()));
                    preparedStmt2.setString (3, args[7]);
                    preparedStmt2.setString(4, "9999-01-01");

                    preparedStmt2.execute();

                    //grabbing the department number by using the department name
                    ResultSet rs3 = pst.executeQuery("SELECT dept_no FROM departments WHERE dept_name =\"" + args[4] + "\"");
                    rs3.next();
                    String deptNum = rs3.getString(1);

                    //insert into dept_emp table
                    String query3 = " insert into dept_emp (dept_no, emp_no, from_date, to_date)"
                            + " values (?, ?, ?, ?)";

                    PreparedStatement preparedStmt3 = con.prepareStatement(query3);
                    preparedStmt3.setString(1, deptNum);
                    preparedStmt3.setInt(2, tempNum);
                    preparedStmt3.setDate(3, new java.sql.Date(System.currentTimeMillis()));
                    preparedStmt3.setString(4, "9999-01-01");

                    preparedStmt3.execute();

                    //printout message for added employee
                    ResultSet rs2 = pst.executeQuery("SELECT first_name, last_name FROM employees ORDER BY emp_no DESC LIMIT 1");
                    rs2.next();
                    System.out.print("Employee ");
                    System.out.printf("%-12s%-12s%-12s\n", rs2.getString(1), rs2.getString(2), " added!");

                    //Delete an employee
                } else if (args[0].equals("delete") && args[1].equals("employee")){

                    //printout message for deleting employee
                    ResultSet rs = pst.executeQuery("SELECT emp_no FROM employees WHERE emp_no =\"" + args[2] + "\"");
                    rs.next();
                    System.out.print("Employee ");
                    System.out.printf("%-8s%-12s\n", rs.getInt(1), " deleted!");

                    //Deletes employee data from employees table
                    String query = "DELETE FROM employees WHERE emp_no = ?";
                    PreparedStatement preparedStmt = con.prepareStatement(query);
                    preparedStmt.setString(1, args[2]);
                    preparedStmt.execute();

                    //Deletes employee data from salaries table
                    String query2 = "DELETE FROM salaries WHERE emp_no = ?";
                    PreparedStatement preparedStmt2 = con.prepareStatement(query2);
                    preparedStmt2.setString(1, args[2]);
                    preparedStmt2.execute();

                    //Deletes employee data from dept_emp table
                    String query3 = "DELETE FROM dept_emp WHERE emp_no = ?";
                    PreparedStatement preparedStmt3 = con.prepareStatement(query3);
                    preparedStmt3.setString(1, args[2]);
                    preparedStmt3.execute();

                    //The total sum of salaries from all employee from the most recent year (9999-01-01)
                    //***I noticed that the total sum was way smaller than other peoples. It is because I
                    //had a smaller pool of salaries to pull from, which I'm not sure why that happened.
                } else if(args[0].equals("show") && args[1].equals("salaries") && args[2].equals("sum")){
                        long sum = 0;
                        String query = "SELECT salary FROM salaries WHERE to_date=\"9999-01-01\"";
                        ResultSet rs = pst.executeQuery(query);

                    while (rs.next()) {
                        sum += rs.getInt(1);
                    }
                    System.out.print("$");
                    System.out.println(sum);
                }

        } catch (SQLException ex) {
            System.out.println(ex);
        }
    }
}
