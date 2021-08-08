package lab3.database.course.database;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public class DatabaseTools {
    public Connection conn=null;

    public Connection getConn() {
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");					//定义MySQL的数据库驱动程序
            String DBURL= "jdbc:mysql://localhost:3306/carCompany?useUnicode=true&characterEncoding=utf-8&useSSL=false";		//定义MySQL的数据库连接地址
            String DBUSER = "root";										//MySQL数据库的连接用户名
            String DBPASS = "hjq216HJQ";										//MySQL数据库的连接密码
            conn= DriverManager.getConnection(DBURL, DBUSER, DBPASS);
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return conn;
    }
}
