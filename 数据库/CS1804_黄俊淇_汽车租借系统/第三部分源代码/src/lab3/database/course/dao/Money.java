package lab3.database.course.dao;

import java.util.Date;
import java.util.Objects;

public class Money {
    private String moneyID;
    private String userID;
    private String carID;
    private Date moneyTime;
    private String moneyDetail;
    private String moneyback;
    private String price;
    private String back;

    public String getMoneyID() {
        return moneyID;
    }

    public void setMoneyID(String moneyID) {
        this.moneyID = moneyID;
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

    public Date getMoneyTime() {
        return moneyTime;
    }

    public void setMoneyTime(Date moneyTime) {
        this.moneyTime = moneyTime;
    }

    public String getMoneyDetail() {
        return moneyDetail;
    }

    public void setMoneyDetail(String moneyDetail) {
        this.moneyDetail = moneyDetail;
    }

    public String getMoneyback() {
        return moneyback;
    }

    public void setMoneyback(String moneyback) {
        this.moneyback = moneyback;
    }

    public String getPrice() {
        return price;
    }

    public void setPrice(String price) {
        this.price = price;
    }

    public String getBack() {
        return back;
    }

    public void setBack(String back) {
        this.back = back;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Money)) return false;
        Money money = (Money) o;
        return getMoneyID().equals(money.getMoneyID()) && getUserID().equals(money.getUserID()) && getCarID().equals(money.getCarID()) && getMoneyTime().equals(money.getMoneyTime()) && getMoneyDetail().equals(money.getMoneyDetail()) && getMoneyback().equals(money.getMoneyback()) && getPrice().equals(money.getPrice()) && getBack().equals(money.getBack());
    }

    @Override
    public int hashCode() {
        return Objects.hash(getMoneyID(), getUserID(), getCarID(), getMoneyTime(), getMoneyDetail(), getMoneyback(), getPrice(), getBack());
    }

    @Override
    public String toString() {
        return "Money{" +
                "moneyID='" + moneyID + '\'' +
                ", userID='" + userID + '\'' +
                ", carID='" + carID + '\'' +
                ", moneyTime=" + moneyTime +
                ", moneyDetail='" + moneyDetail + '\'' +
                ", moneyback='" + moneyback + '\'' +
                ", price='" + price + '\'' +
                ", back='" + back + '\'' +
                '}';
    }
}
