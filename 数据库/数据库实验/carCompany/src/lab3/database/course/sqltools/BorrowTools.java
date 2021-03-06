package lab3.database.course.sqltools;

import lab3.database.course.dao.Car;
import lab3.database.course.database.DatabaseTools;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

public class BorrowTools {
    public List<Car> CarData(String userID) {
        String sql="select car.carID,car.carName,car.carPrice,car.borrowPrice from customer,borrow,car "
                + "where car.carID = borrow.carID and customer.userID = borrow.userID "
                + "and  customer.userID= '" + userID + "'";
        DatabaseTools db = new DatabaseTools();
        Connection conn = db.getConn();
        ResultSet rs=null;
        List<Car> ls=new ArrayList<Car>();
        try {
            PreparedStatement st =conn.prepareStatement(sql);
            rs=st.executeQuery(sql);
            while(rs.next()){
                Car car=new Car();
                car.setCarID(rs.getString("carID"));
                car.setCarName(rs.getString("carName"));
                car.setCarPrice(rs.getString("carPrice"));
                car.setBorrowPrice(rs.getString("borrowPrice"));
                ls.add(car);
            }
            rs.close();
            st.close();
            conn.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return ls;
    }

    public List<Car> CarData_Search_carID(String carID) {
        String sql="select * from car where carID = '" + carID + "'";
        DatabaseTools db = new DatabaseTools();
        Connection conn = db.getConn();
        ResultSet rs=null;
        List<Car> ls=new ArrayList<Car>();
        try {
            PreparedStatement st =conn.prepareStatement(sql);
            rs=st.executeQuery(sql);
            while(rs.next()){
                Car car=new Car();
                car.setCarID(rs.getString("carID"));
                car.setCarName(rs.getString("carName"));
                car.setCarPrice(rs.getString("carPrice"));
                car.setBorrowPrice(rs.getString("borrowPrice"));
                ls.add(car);
            }
            rs.close();
            st.close();
            conn.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return ls;
    }

    public boolean whetherInStock(String carID) {
        DatabaseTools db = new DatabaseTools();
        Connection conn = db.getConn();
        String sql = "select * from borrow ";
        try {
            PreparedStatement st =conn.prepareStatement(sql);
            ResultSet rs = st.executeQuery(sql);
            while (rs.next()) {
                if(rs.getString("carID")!=null){
                    if(rs.getString("carID").equals(carID)){
                        return false;
                    }
                }
            }
            st.close();
            conn.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return true;
    }

    public int BorrowCar(String userID,String carID) {
        int i=0;
        String sql="insert into borrow (userID,carID,carCondition,borrowTime,dueTime,overtime)values(?,?,'??????',"
                + "CURRENT_DATE(),DATE_ADD(CURRENT_DATE(),INTERVAL 2 DAY),'???')";
        DatabaseTools db = new DatabaseTools();
        Connection conn = db.getConn();
        try {
            PreparedStatement st = conn.prepareStatement(sql);
            st.setString(1, userID);
            st.setString(2, carID);
            i=st.executeUpdate();
            st.close();
            conn.close();
        }catch (SQLException e) {
            e.printStackTrace();
        }
        return i;
    }

    public int ReturnCar(String carID) {
        int i=0;
        String sql="delete from borrow where carID=?";
        DatabaseTools db = new DatabaseTools();
        Connection conn = db.getConn();
        try {
            PreparedStatement st = conn.prepareStatement(sql);
            st.setString(1, carID);
            i=st.executeUpdate();
            st.close();
            conn.close();
        }catch (SQLException e) {
            e.printStackTrace();
        }
        return i;
    }
}
