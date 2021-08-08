package lab3.database.course.sqltools;

import lab3.database.course.dao.Customer;
import lab3.database.course.database.DatabaseTools;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

public class CustomerTools {
    public List<Customer> customersData(String userID) {
        String sql="select * from customer where userID ='" + userID + "'";
        DatabaseTools db = new DatabaseTools();
        Connection conn = db.getConn();
        ResultSet rs=null;
        List<Customer> ls=new ArrayList<Customer>();
        try {
            PreparedStatement st =conn.prepareStatement(sql);
            rs=st.executeQuery(sql);
            while(rs.next()){
                Customer customer=new Customer();
                customer.setUserID(rs.getString("userID"));
                customer.setUsername(rs.getString("username"));
                customer.setUserPassword(rs.getString("userPassword"));
                ls.add(customer);
            }
            rs.close();
            st.close();
            conn.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return ls;
    }
    public List<Customer> customersData() {
        String sql="select * from customer";
        DatabaseTools db = new DatabaseTools();
        Connection conn = db.getConn();
        ResultSet rs=null;
        List<Customer> ls=new ArrayList<Customer>();
        try {
            PreparedStatement st =conn.prepareStatement(sql);
            rs=st.executeQuery(sql);
            while(rs.next()){
                Customer customer=new Customer();
                customer.setUserID(rs.getString("userID"));
                customer.setUsername(rs.getString("username"));
                customer.setUserPassword(rs.getString("userPassword"));
                ls.add(customer);
            }
            rs.close();
            st.close();
            conn.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return ls;
    }

    public boolean customerLogin(String userID, String userPassword) {
        DatabaseTools db = new DatabaseTools();
        Connection conn = db.getConn();
        try {
            String sql = "select userID,userPassword from customer where userID='" + userID + "' and userPassword='" + userPassword+"'";
            PreparedStatement st =conn.prepareStatement(sql);
            ResultSet rs = st.executeQuery(sql);
            if (rs.next()) {
                return true;
            }
            st.close();
            conn.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return false;
    }

    public int AddCustomer(Customer c) {
        int i=0;
        String sql="insert into customer (userID,username,userPassword)values(?,?,?)";
        DatabaseTools db = new DatabaseTools();
        Connection conn = db.getConn();
        try {
            PreparedStatement st = conn.prepareStatement(sql);
            st.setString(1, c.getUserID());
            st.setString(2, c.getUsername());
            st.setString(3, c.getUserPassword());
            i=st.executeUpdate();
            st.close();
            conn.close();
        }catch (SQLException e) {
            e.printStackTrace();
        }
        return i;
    }

    public int UpdateCustomer(Customer customer) {
        int i=0;
        String sql="update customer set userID=?,username=?,userPassword=? where userID=?";
        DatabaseTools db = new DatabaseTools();
        Connection conn = db.getConn();
        try {
            PreparedStatement st = conn.prepareStatement(sql);
            st.setString(1, customer.getUserID());
            st.setString(2, customer.getUsername());
            st.setString(3, customer.getUserPassword());
            st.setString(4, customer.getUserID());
            i=st.executeUpdate();
            st.close();
            conn.close();
        }catch (SQLException e) {
            e.printStackTrace();
        }
        return i;
    }

    public int DeleteCustomer(String userID) {
        int i=0;
        String sql="delete from customer where userID=?";
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
