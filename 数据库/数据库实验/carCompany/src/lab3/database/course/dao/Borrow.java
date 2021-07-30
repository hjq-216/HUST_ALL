package lab3.database.course.dao;

import java.util.Date;
import java.util.Objects;

public class Borrow {
    private String recordID;
    private String userID;
    private String carID;
    private String carCondition;
    private Date borrowTime;
    private Date dueTime;
    private String overTime;

    public String getRecordID() {
        return recordID;
    }

    public void setRecordID(String recordID) {
        this.recordID = recordID;
    }

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
        if (!(o instanceof Borrow)) return false;
        Borrow borrow = (Borrow) o;
        return getRecordID().equals(borrow.getRecordID()) && getUserID().equals(borrow.getUserID()) && getCarID().equals(borrow.getCarID()) && getCarCondition().equals(borrow.getCarCondition()) && getBorrowTime().equals(borrow.getBorrowTime()) && getDueTime().equals(borrow.getDueTime()) && getOverTime().equals(borrow.getOverTime());
    }

    @Override
    public int hashCode() {
        return Objects.hash(getRecordID(), getUserID(), getCarID(), getCarCondition(), getBorrowTime(), getDueTime(), getOverTime());
    }

    @Override
    public String toString() {
        return "Borrow{" +
                "recordID='" + recordID + '\'' +
                ", userID='" + userID + '\'' +
                ", carID='" + carID + '\'' +
                ", carCondition='" + carCondition + '\'' +
                ", borrowTime=" + borrowTime +
                ", dueTime=" + dueTime +
                ", overTime='" + overTime + '\'' +
                '}';
    }
}
