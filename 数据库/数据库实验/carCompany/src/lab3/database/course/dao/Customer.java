package lab3.database.course.dao;

import java.util.Objects;

public class Customer {
    private String userID;
    private String username;
    private String userPassword;

    public String getUserID() {
        return userID;
    }

    public void setUserID(String userID) {
        this.userID = userID;
    }

    public String getUsername() {
        return username;
    }

    public void setUsername(String username) {
        this.username = username;
    }

    public String getUserPassword() {
        return userPassword;
    }

    public void setUserPassword(String userPassword) {
        this.userPassword = userPassword;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Customer)) return false;
        Customer customer = (Customer) o;
        return getUserID().equals(customer.getUserID()) && getUsername().equals(customer.getUsername()) && getUserPassword().equals(customer.getUserPassword());
    }

    @Override
    public int hashCode() {
        return Objects.hash(getUserID(), getUsername(), getUserPassword());
    }

    @Override
    public String toString() {
        return "Customer{" +
                "userID='" + userID + '\'' +
                ", username='" + username + '\'' +
                ", userPassword='" + userPassword + '\'' +
                '}';
    }
}
