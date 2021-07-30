package lab3.database.course.sqltools;

import lab3.database.course.dao.Car;
import lab3.database.course.database.DatabaseTools;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

public class CarTools {
    public List<Car> CarData() {
        String sql="select * from car";
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

    public List<Car> CarData(String carName) {
        String sql="select * from car where carName like'%" + carName + "%'";
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

    public Car Search_Car(String carID) {
        String sql="select * from car where carID='" + carID + "'";
        DatabaseTools db = new DatabaseTools();
        Connection conn = db.getConn();
        ResultSet rs=null;
        Car car = null;
        try {
            PreparedStatement st =conn.prepareStatement(sql);
            rs=st.executeQuery(sql);
            while(rs.next()){
                car=new Car();
                car.setCarID(rs.getString("carID"));
                car.setCarName(rs.getString("carName"));
                car.setCarPrice(rs.getString("carPrice"));
                car.setBorrowPrice(rs.getString("borrowPrice"));
            }
            rs.close();
            st.close();
            conn.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return car;
    }

    public int AddCar(Car car) {
        int i=0;
        String sql="insert into car (carID,carName,carPrice,borrowPrice)values(?,?,?,?)";
        DatabaseTools db = new DatabaseTools();
        Connection conn = db.getConn();
        try {
            PreparedStatement st = conn.prepareStatement(sql);
            st.setString(1, car.getCarID());
            st.setString(2, car.getCarName());
            st.setString(3, car.getCarPrice());
            st.setString(4, car.getBorrowPrice());
            i=st.executeUpdate();
            st.close();
            conn.close();
        }catch (SQLException e) {
            e.printStackTrace();
        }
        return i;
    }

    public int UpdateCar(Car car) {
        int i=0;
        String sql="update car set carID=?,carName=?,carPrice=?,borrowPrice=? where carID=?";
        DatabaseTools db = new DatabaseTools();
        Connection conn = db.getConn();
        try {
            PreparedStatement st = conn.prepareStatement(sql);
            st.setString(1, car.getCarID());
            st.setString(2, car.getCarName());
            st.setString(3, car.getCarPrice());
            st.setString(4, car.getBorrowPrice());
            st.setString(5, car.getCarID());
            i=st.executeUpdate();
            st.close();
            conn.close();
        }catch (SQLException e) {
            e.printStackTrace();
        }
        return i;
    }

    public int DeleteCar(String carID) {
        int i=0;
        String sql="delete from car where carID=?";
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
