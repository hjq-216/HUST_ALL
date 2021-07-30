package lab3.database.course.frame;

import lab3.database.course.dao.Customer;
import lab3.database.course.sqltools.CustomerTools;

import javax.swing.*;
import javax.swing.border.EmptyBorder;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class Customer_RegisterFrame extends JFrame {
    private static final long serialVersionUID = 1L;
    private JPanel contentPane;

    private JTextField idCustomertextField;
    private JTextField nameCustomertextField;
    private JTextField passwordtextField;

    private JLabel idCustomerLabel;
    private JLabel nameCustomerLabel;
    private JLabel passwordLabel;

    private JButton insertButton;

    public Customer_RegisterFrame()
    {
        setResizable(false);
        setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        setBounds(100, 100, 996, 699);
        contentPane = new JPanel();
        contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
        setContentPane(contentPane);
        contentPane.setLayout(null);

        JButton reader_Registerbutton = new JButton("客户注册");
        reader_Registerbutton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                Customer_RegisterFrame customer_registerFrame = new Customer_RegisterFrame();
                customer_registerFrame.setVisible(true);
                CloseFrame();
            }
        });
        reader_Registerbutton.setBounds(60, 197, 123, 29);
        contentPane.add(reader_Registerbutton);

        JButton book_Registerbutton = new JButton("车辆入库");
        book_Registerbutton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                Car_RegisterFrame car_registerFrame = new Car_RegisterFrame();
                car_registerFrame.setVisible(true);
                CloseFrame();
            }
        });
        book_Registerbutton.setBounds(60, 277, 123, 29);
        contentPane.add(book_Registerbutton);

        JButton all_Readerbutton = new JButton("客户管理");
        all_Readerbutton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                All_CustomerFrame all_customerFrame = new All_CustomerFrame();
                all_customerFrame.setVisible(true);
                CloseFrame();
            }
        });
        all_Readerbutton.setBounds(60, 357, 123, 29);
        contentPane.add(all_Readerbutton);

        JButton all_Bookbutton = new JButton("车辆管理");
        all_Bookbutton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                All_CarFrame all_carFrame = new All_CarFrame();
                all_carFrame.setVisible(true);
                CloseFrame();
            }
        });
        all_Bookbutton.setBounds(60, 437, 123, 29);
        contentPane.add(all_Bookbutton);

        JButton checkReader_button = new JButton("租赁管理");
        checkReader_button.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                CheckCustomerFrame checkCustomerFrame = new CheckCustomerFrame();
                checkCustomerFrame.setVisible(true);
                CloseFrame();
            }
        });
        checkReader_button.setBounds(60, 517, 123, 29);
        contentPane.add(checkReader_button);

        JButton monetShow_button = new JButton("收支查询");
        monetShow_button.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                Money_ShowFrame money_showFrame = new Money_ShowFrame();
                money_showFrame.setVisible(true);
                CloseFrame();
            }
        });
        monetShow_button.setBounds(60, 597, 123, 29);
        contentPane.add(monetShow_button);

        JButton log_out_Button = new JButton("登出");
        log_out_Button.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                LoginFrame loginframe = new LoginFrame();
                loginframe.setVisible(true);
                CloseFrame();
            }
        });
        log_out_Button.setBounds(817, 102, 85, 29);
        contentPane.add(log_out_Button);

        idCustomerLabel = new JLabel("卡号");
        idCustomerLabel.setFont(new Font("宋体", Font.PLAIN, 30));
        idCustomerLabel.setBounds(445, 180, 149, 55);
        contentPane.add(idCustomerLabel);

        nameCustomerLabel = new JLabel("姓名");
        nameCustomerLabel.setFont(new Font("宋体", Font.PLAIN, 30));
        nameCustomerLabel.setBounds(470, 320, 113, 34);
        contentPane.add(nameCustomerLabel);

        passwordLabel = new JLabel("登录密码");
        passwordLabel.setFont(new Font("宋体", Font.PLAIN, 30));
        passwordLabel.setBounds(445, 459, 120, 55);
        contentPane.add(passwordLabel);

        idCustomertextField = new JTextField();
        idCustomertextField.setFont(new Font("宋体", Font.PLAIN, 30));
        idCustomertextField.setBounds(640, 184, 139, 47);
        contentPane.add(idCustomertextField);
        idCustomertextField.setColumns(10);

        nameCustomertextField = new JTextField();
        nameCustomertextField.setFont(new Font("宋体", Font.PLAIN, 30));
        nameCustomertextField.setBounds(640, 320, 137, 47);
        contentPane.add(nameCustomertextField);
        nameCustomertextField.setColumns(10);

        passwordtextField = new JTextField();
        passwordtextField.setFont(new Font("宋体", Font.PLAIN, 30));
        passwordtextField.setBounds(640, 463, 139, 47);
        contentPane.add(passwordtextField);
        passwordtextField.setColumns(10);

        insertButton = new JButton(new ImageIcon("image/register.jpg"));
        insertButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                do_insertButton_AddCustomer();
            }
        });
        insertButton.setBounds(555, 545, 106, 47);
        contentPane.add(insertButton);

        JLabel background1 = new JLabel(new ImageIcon("image/background2.jpg"));
        background1.setBounds(0, 0, 990, 659);
        contentPane.add(background1);
    }

    protected void do_insertButton_AddCustomer() {

        CustomerTools customerTools = new CustomerTools();
        Customer customer = new Customer();

        if (idCustomertextField.getText() != null && !"".equals(idCustomertextField.getText())
                && nameCustomertextField.getText() != null && !"".equals(nameCustomertextField.getText())
                && passwordtextField.getText() != null && !"".equals(passwordtextField.getText())) {
            customer.setUserID(idCustomertextField.getText());
            customer.setUsername(nameCustomertextField.getText());
            customer.setUserPassword(passwordtextField.getText());
            int i = customerTools.AddCustomer(customer);
            if (i == 1) {
                JOptionPane.showMessageDialog(getContentPane(), "成功新增客户信息！", "", JOptionPane.WARNING_MESSAGE);
                return;
            } else {
                JOptionPane.showMessageDialog(getContentPane(), "新增客户信息失败！", "", JOptionPane.WARNING_MESSAGE);
                return;
            }
        } else {
            JOptionPane.showMessageDialog(getContentPane(), "请输入完整资料", "", JOptionPane.WARNING_MESSAGE);
            return;
        }
    }

    public void CloseFrame() {
        super.dispose();
    }
}
