package lab3.database.course.sqltools;

import lab3.database.course.dao.Customer;
import lab3.database.course.dao.Money;
import lab3.database.course.database.DatabaseTools;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

public class MoneyTools {
    public List<Money> moneyData(){
        String sql="select * from money";
        DatabaseTools db = new DatabaseTools();
        Connection conn = db.getConn();
        ResultSet rs=null;
        List<Money> ls=new ArrayList<Money>();
        try {
            PreparedStatement st =conn.prepareStatement(sql);
            rs=st.executeQuery(sql);
            while(rs.next()){
                Money money=new Money();
                money.setMoneyID(rs.getString("moneyID"));
                money.setUserID(rs.getString("userID"));
                money.setCarID(rs.getString("carID"));
                money.setMoneyTime(rs.getTimestamp("moneyTime"));
                money.setMoneyDetail(rs.getString("moneyDetail"));
                money.setMoneyback(rs.getString("moneyback"));
                money.setPrice(rs.getString("price"));
                money.setBack(rs.getString("back"));
                ls.add(money);
            }
            rs.close();
            st.close();
            conn.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return ls;
    }
    public List<Money> money7Day(){
        String sql="select * from money where date_sub(CURDATE(),INTERVAL 7 DAY) <= DATE(moneyTime)";
        DatabaseTools db = new DatabaseTools();
        Connection conn = db.getConn();
        ResultSet rs=null;
        List<Money> ls=new ArrayList<Money>();
        try {
            PreparedStatement st =conn.prepareStatement(sql);
            rs=st.executeQuery(sql);
            while(rs.next()){
                Money money=new Money();
                money.setMoneyID(rs.getString("moneyID"));
                money.setUserID(rs.getString("userID"));
                money.setCarID(rs.getString("carID"));
                money.setMoneyTime(rs.getTimestamp("moneyTime"));
                money.setMoneyDetail(rs.getString("moneyDetail"));
                money.setMoneyback(rs.getString("moneyback"));
                money.setPrice(rs.getString("price"));
                money.setBack(rs.getString("back"));
                ls.add(money);
            }
            rs.close();
            st.close();
            conn.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return ls;
    }
    public List<Money> moneyMonth(){
        String sql="select * from money where date_sub(CURDATE(),INTERVAL 30 DAY) <= DATE(moneyTime)";
        DatabaseTools db = new DatabaseTools();
        Connection conn = db.getConn();
        ResultSet rs=null;
        List<Money> ls=new ArrayList<Money>();
        try {
            PreparedStatement st =conn.prepareStatement(sql);
            rs=st.executeQuery(sql);
            while(rs.next()){
                Money money=new Money();
                money.setMoneyID(rs.getString("moneyID"));
                money.setUserID(rs.getString("userID"));
                money.setCarID(rs.getString("carID"));
                money.setMoneyTime(rs.getTimestamp("moneyTime"));
                money.setMoneyDetail(rs.getString("moneyDetail"));
                money.setMoneyback(rs.getString("moneyback"));
                money.setPrice(rs.getString("price"));
                money.setBack(rs.getString("back"));
                ls.add(money);
            }
            rs.close();
            st.close();
            conn.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return ls;
    }
    public List<Money> moneyYear(){
        String sql="select * from money where moneyTime between date_sub(now(),interval 12 month) and now()";
        DatabaseTools db = new DatabaseTools();
        Connection conn = db.getConn();
        ResultSet rs=null;
        List<Money> ls=new ArrayList<Money>();
        try {
            PreparedStatement st =conn.prepareStatement(sql);
            rs=st.executeQuery(sql);
            while(rs.next()){
                Money money=new Money();
                money.setMoneyID(rs.getString("moneyID"));
                money.setUserID(rs.getString("userID"));
                money.setCarID(rs.getString("carID"));
                money.setMoneyTime(rs.getTimestamp("moneyTime"));
                money.setMoneyDetail(rs.getString("moneyDetail"));
                money.setMoneyback(rs.getString("moneyback"));
                money.setPrice(rs.getString("price"));
                money.setBack(rs.getString("back"));
                ls.add(money);
            }
            rs.close();
            st.close();
            conn.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return ls;
    }
}
