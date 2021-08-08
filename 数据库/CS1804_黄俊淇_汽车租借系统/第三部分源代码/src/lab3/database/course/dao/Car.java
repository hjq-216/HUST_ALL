package lab3.database.course.dao;

import java.util.Objects;

public class Car {
    private String carID;
    private String carName;
    private String carPrice;
    private String borrowPrice;

    public String getCarID() {
        return carID;
    }

    public void setCarID(String carID) {
        this.carID = carID;
    }

    public String getCarName() {
        return carName;
    }

    public void setCarName(String carName) {
        this.carName = carName;
    }

    public String getCarPrice() {
        return carPrice;
    }

    public void setCarPrice(String carPrice) {
        this.carPrice = carPrice;
    }

    public String getBorrowPrice() {
        return borrowPrice;
    }

    public void setBorrowPrice(String borrowPrice) {
        this.borrowPrice = borrowPrice;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Car)) return false;
        Car car = (Car) o;
        return getCarID().equals(car.getCarID()) && getCarName().equals(car.getCarName()) && getCarPrice().equals(car.getCarPrice()) && getBorrowPrice().equals(car.getBorrowPrice());
    }

    @Override
    public int hashCode() {
        return Objects.hash(getCarID(), getCarName(), getCarPrice(), getBorrowPrice());
    }

    @Override
    public String toString() {
        return "Car{" +
                "carID='" + carID + '\'' +
                ", carName='" + carName + '\'' +
                ", carPrice='" + carPrice + '\'' +
                ", borrowPrice='" + borrowPrice + '\'' +
                '}';
    }
}
