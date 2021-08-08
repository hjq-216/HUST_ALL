package lab3.database.course.dao;

import java.util.Objects;

public class CustomerLevel {
    private String userID;
    private int borrowTimes;
    private int overTimes;
    private int userLevel;

    public String getUserID() {
        return userID;
    }

    public void setUserID(String userID) {
        this.userID = userID;
    }

    public int getBorrowTimes() {
        return borrowTimes;
    }

    public void setBorrowTimes(int borrowTimes) {
        this.borrowTimes = borrowTimes;
    }

    public int getOverTimes() {
        return overTimes;
    }

    public void setOverTimes(int overTimes) {
        this.overTimes = overTimes;
    }

    public int getUserLevel() {
        return userLevel;
    }

    public void setUserLevel(int userLevel) {
        this.userLevel = userLevel;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof CustomerLevel)) return false;
        CustomerLevel that = (CustomerLevel) o;
        return getBorrowTimes() == that.getBorrowTimes() && getOverTimes() == that.getOverTimes() && getUserLevel() == that.getUserLevel() && getUserID().equals(that.getUserID());
    }

    @Override
    public int hashCode() {
        return Objects.hash(getUserID(), getBorrowTimes(), getOverTimes(), getUserLevel());
    }

    @Override
    public String toString() {
        return "CustomerLevel{" +
                "userID='" + userID + '\'' +
                ", borrowTimes=" + borrowTimes +
                ", overTimes=" + overTimes +
                ", userLevel=" + userLevel +
                '}';
    }
}
