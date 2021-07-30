package lab3.database.course.frame;

import lab3.database.course.dao.Company;
import lab3.database.course.dao.Customer;
import lab3.database.course.sqltools.CompanyTools;
import lab3.database.course.sqltools.CustomerTools;

import javax.swing.*;
import javax.swing.border.EmptyBorder;
import java.awt.*;
import java.awt.event.*;

public class LoginFrame extends JFrame implements ItemListener {
    private static final long serialVersionUID = 1L;
    private JPanel contentPane;

    private boolean customerLogin = true;
    private boolean companyLogin = false;
    private Company company;
    private Customer customer;

    private JTextField nameUserTextField;
    private JPasswordField passwordField;
    private JButton loginButton;
    private JButton view_Password_Button;

    private JRadioButton customerRadioButton;
    private JRadioButton companyRadioButton;
    private ButtonGroup group;

    private JLabel userNameLabel;
    private JLabel passwordLabel;

    public static String userID;
    public static String username;
    public static String cName;

    public LoginFrame()
    {
        setResizable(false);
        setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        setBounds(100, 100, 389, 560);
        contentPane = new JPanel();
        contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
        setContentPane(contentPane);
        contentPane.setLayout(null);

        userNameLabel = new JLabel("用户名");
        userNameLabel.setForeground(Color.BLACK);
        userNameLabel.setFont(new Font("Dialog", Font.BOLD, 15));
        userNameLabel.setBounds(64, 188, 55, 20);
        contentPane.add(userNameLabel);

        passwordLabel = new JLabel("密码");
        passwordLabel.setForeground(Color.BLACK);
        passwordLabel.setFont(new Font("Dialog", Font.BOLD, 15));
        passwordLabel.setBounds(64, 267, 55, 18);
        contentPane.add(passwordLabel);

        nameUserTextField = new JTextField();
        nameUserTextField.setFont(new Font("Dialog", Font.PLAIN, 15));
        nameUserTextField.setBounds(128, 188, 167, 22);
        contentPane.add(nameUserTextField);
        nameUserTextField.setColumns(10);

        passwordField = new JPasswordField();
        passwordField.setFont(new Font("Dialog", Font.PLAIN, 15));
        passwordField.setBounds(128, 265, 167, 22);
        contentPane.add(passwordField);

        loginButton = new JButton(new ImageIcon("image/loginbutton.jpg"));
        loginButton.setFont(new Font("Dialog", Font.BOLD, 17));
        loginButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                check_login();
            }
        });
        loginButton.setBounds(129, 386, 98, 36);
        contentPane.add(loginButton);

        // 为单选按钮JRadioButton加上事件监听，默认选中readerRadioButton
        customerRadioButton = new JRadioButton("客户");
        customerRadioButton.setForeground(Color.BLACK);
        customerRadioButton.setBounds(57, 323, 121, 26);
        contentPane.add(customerRadioButton);
        customerRadioButton.addItemListener(this);
        customerRadioButton.setSelected(true);
        customerRadioButton.setContentAreaFilled(false);

        companyRadioButton = new JRadioButton("管理员");
        companyRadioButton.setForeground(Color.BLACK);
        companyRadioButton.setBounds(198, 323, 121, 26);
        contentPane.add(companyRadioButton);
        companyRadioButton.addItemListener(this);
        companyRadioButton.setContentAreaFilled(false);

        // 将单选按钮加入到一个组里
        group = new ButtonGroup();
        group.add(this.customerRadioButton);
        group.add(this.companyRadioButton);

        view_Password_Button = new JButton(new ImageIcon("image/review.jpg"));
        view_Password_Button.setBounds(302, 267, 31, 20);
        view_Password_Button.addMouseListener(new MouseAdapter(){
            char echoChar=passwordField.getEchoChar();
            public void mousePressed(MouseEvent e){
                passwordField.setEchoChar((char)0);
            }
            public void mouseReleased(MouseEvent e){
                passwordField.setEchoChar(echoChar);
                passwordField.requestFocus();
            }
        });
        contentPane.add(view_Password_Button);

        JLabel background1 = new JLabel(new ImageIcon("image/login2.jpg"));
        background1.setBounds(0, 0, 383, 520);
        contentPane.add(background1);
    }

    private void check_login()
    {
        if (this.customerLogin == true) {
            CustomerTools rTools = new CustomerTools();
            customer = new Customer();
            customer.setUserID(nameUserTextField.getText());
            customer.setUserPassword(new String(passwordField.getPassword()));
            if (nameUserTextField.getText() != null && !"".equals(nameUserTextField.getText())
                    && passwordField.getPassword() != null && !("".equals(new String(passwordField.getPassword())))) {

                boolean whether_login = rTools.customerLogin(customer.getUserID(), customer.getUserPassword());
                username = rTools.customersData(customer.getUserID()).get(0).getUsername();
                if (whether_login == true) {
                    userID = customer.getUserID();

                    Gif_CustomerFrame frame = new Gif_CustomerFrame();
                    new Thread(frame,"Reader线程").start();

                    CloseFrame();
                    return;
                } else {
                    JOptionPane.showMessageDialog(this, "用户名或密码错误", "", JOptionPane.WARNING_MESSAGE);
                    return;
                }

            } else {
                JOptionPane.showMessageDialog(this, "请填写用户名和密码", "", JOptionPane.WARNING_MESSAGE);
                return;
            }

        }
        if (this.companyLogin == true) {
            CompanyTools companyTools = new CompanyTools();
            company = new Company();
            company.setcName(nameUserTextField.getText());
            company.setcPassword(new String(passwordField.getPassword()));
            if (nameUserTextField.getText() != null && !"".equals(nameUserTextField.getText())
                    && passwordField.getPassword() != null && !("".equals(new String(passwordField.getPassword())))) {

                boolean whether_login = companyTools.CompanyLogin(company.getcName(), company.getcPassword());
                if (whether_login == true) {
                    cName = company.getcName();

                    Gif_CompanyFrame frame = new Gif_CompanyFrame();
                    new Thread(frame,"Reader线程").start();

                    CloseFrame();
                    return;
                } else {
                    JOptionPane.showMessageDialog(this, "用户名或密码错误", "", JOptionPane.WARNING_MESSAGE);
                    return;
                }

            } else {
                JOptionPane.showMessageDialog(this, "请填写用户名和密码", "", JOptionPane.WARNING_MESSAGE);
                return;
            }
        }
    }

    @Override
    public void itemStateChanged(ItemEvent e) {
        if (e.getSource() == customerRadioButton) {
            this.customerLogin = true;
            this.companyLogin = false;
        } else {
            this.customerLogin = false;
            this.companyLogin = true;
        }
    }
    public void CloseFrame() {
        super.dispose();
    }
}
