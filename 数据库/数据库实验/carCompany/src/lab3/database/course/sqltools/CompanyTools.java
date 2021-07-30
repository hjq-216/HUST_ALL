package lab3.database.course.sqltools;

import lab3.database.course.database.DatabaseTools;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class CompanyTools {
    public boolean CompanyLogin(String cName, String cPassword) {
        DatabaseTools db = new DatabaseTools();
        Connection conn = db.getConn();
        try {
            String sql = "select cName,cPassword from company where cName='" + cName + "' and cPassword='" + cPassword+"'";
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
}
