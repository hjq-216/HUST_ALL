package lab3.database.course.sqltools;

import lab3.database.course.dao.Borrow;
import lab3.database.course.dao.Borrowed;
import lab3.database.course.database.DatabaseTools;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

public class BorrowedTools {
    public List<Borrowed> getUsedCar(String userID){
        String sql="select * from borrowed where userID='" + userID + "'";
        DatabaseTools db = new DatabaseTools();
        Connection conn = db.getConn();
        ResultSet rs=null;
        List<Borrowed> ls=new ArrayList<Borrowed>();
        try {
            PreparedStatement st =conn.prepareStatement(sql);
            rs=st.executeQuery(sql);
            while(rs.next()){
                Borrowed borrowed=new Borrowed();
                borrowed.setUserID(rs.getString("userID"));
                borrowed.setCarID(rs.getString("carID"));
                borrowed.setCarCondition(rs.getString("carCondition"));
                borrowed.setBorrowTime(rs.getTimestamp("borrowTime"));
                borrowed.setDueTime(rs.getTimestamp("dueTime"));
                borrowed.setOverTime(rs.getString("overTime"));
                ls.add(borrowed);
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
