package lab3.database.course.dao;

import java.util.Objects;

public class Company {
    private String cName;
    private String cPassword;

    public String getcName() {
        return cName;
    }

    public void setcName(String cName) {
        this.cName = cName;
    }

    public String getcPassword() {
        return cPassword;
    }

    public void setcPassword(String cPassword) {
        this.cPassword = cPassword;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Company)) return false;
        Company company = (Company) o;
        return getcName().equals(company.getcName()) && getcPassword().equals(company.getcPassword());
    }

    @Override
    public int hashCode() {
        return Objects.hash(getcName(), getcPassword());
    }

    @Override
    public String toString() {
        return "Company{" +
                "cName='" + cName + '\'' +
                ", cPassword='" + cPassword + '\'' +
                '}';
    }
}
