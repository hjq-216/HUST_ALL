package lab3.database.course.sqltools;

import lab3.database.course.dao.Customer;
import lab3.database.course.dao.CustomerLevel;
import lab3.database.course.database.DatabaseTools;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

public class CustomerLevelTools {
    public CustomerLevel levelData(String userID) {
        String sql="select userLevel from customer_level where userID ='" + userID + "'";
        DatabaseTools db = new DatabaseTools();
        Connection conn = db.getConn();
        ResultSet rs=null;
        CustomerLevel customerLevel = new CustomerLevel();
        try {
            PreparedStatement st =conn.prepareStatement(sql);
            rs=st.executeQuery(sql);
            while (rs.next())
            {
                customerLevel.setUserLevel(Integer.parseInt(rs.getString("userLevel")));
            }
            rs.close();
            st.close();
            conn.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return customerLevel;
    }

    public int DeleteCustomerLevel(String userID) {
        int i=0;
        String sql="delete from customer_level where userID=?";
        DatabaseTools db = new DatabaseTools();
        Connection conn = db.getConn();
        try {
            PreparedStatement st = conn.prepareStatement(sql);
            st.setString(1, userID);
            i=st.executeUpdate();
            st.close();
            conn.close();
        }catch (SQLException e) {
            e.printStackTrace();
        }
        return i;
    }
}
