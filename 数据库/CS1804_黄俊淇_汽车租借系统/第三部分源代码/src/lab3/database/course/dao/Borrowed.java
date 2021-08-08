package lab3.database.course.dao;

import java.util.Date;
import java.util.Objects;

public class Borrowed {
    private String userID;
    private String carID;
    private String carCondition;
    private Date borrowTime;
    private Date dueTime;
    private String overTime;

    public String getUserID() {
        return userID;
    }

    public void setUserID(String userID) {
        this.userID = userID;
    }

    public String getCarID() {
        return carID;
    }

    public void setCarID(String carID) {
        this.carID = carID;
    }

    public String getCarCondition() {
        return carCondition;
    }

    public void setCarCondition(String carCondition) {
        this.carCondition = carCondition;
    }

    public Date getBorrowTime() {
        return borrowTime;
    }

    public void setBorrowTime(Date borrowTime) {
        this.borrowTime = borrowTime;
    }

    public Date getDueTime() {
        return dueTime;
    }

    public void setDueTime(Date dueTime) {
        this.dueTime = dueTime;
    }

    public String getOverTime() {
        return overTime;
    }

    public void setOverTime(String overTime) {
        this.overTime = overTime;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Borrowed)) return false;
        Borrowed borrowed = (Borrowed) o;
        return getUserID().equals(borrowed.getUserID()) && getCarID().equals(borrowed.getCarID()) && getCarCondition().equals(borrowed.getCarCondition()) && getBorrowTime().equals(borrowed.getBorrowTime()) && getDueTime().equals(borrowed.getDueTime()) && getOverTime().equals(borrowed.getOverTime());
    }

    @Override
    public int hashCode() {
        return Objects.hash(getUserID(), getCarID(), getCarCondition(), getBorrowTime(), getDueTime(), getOverTime());
    }

    @Override
    public String toString() {
        return "Borrowed{" +
                "userID='" + userID + '\'' +
                ", carID='" + carID + '\'' +
                ", carCondition='" + carCondition + '\'' +
                ", borrowTime=" + borrowTime +
                ", dueTime=" + dueTime +
                ", overTime='" + overTime + '\'' +
                '}';
    }
}
