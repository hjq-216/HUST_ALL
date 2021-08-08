package lab3.database.course.frame;

import lab3.database.course.dao.Car;
import lab3.database.course.dao.Customer;
import lab3.database.course.dao.CustomerLevel;
import lab3.database.course.sqltools.BorrowTools;
import lab3.database.course.sqltools.CustomerLevelTools;
import lab3.database.course.sqltools.CustomerTools;

import javax.swing.*;
import javax.swing.border.EmptyBorder;
import javax.swing.table.DefaultTableModel;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Iterator;
import java.util.List;

public class CheckCustomerFrame extends JFrame {
    private static final long serialVersionUID = 1L;
    private JPanel contentPane;

    private JLayeredPane layeredPane;

    private JScrollPane carScrollPane;
    private JTable carJtable;
    private DefaultTableModel defaultModel;

    private JLabel idCustomerLabel;
    private JLabel nameCustomerLabel;
    private JLabel passwordLabel;
    private JLabel levelLabel;
    private JTextField idCustomertextField;

    private JLabel showNameCustomerLabel;
    private JLabel showPasswordLabel;
    private JLabel showLevelLabel;

    public CheckCustomerFrame()
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

        layeredPane = new JLayeredPane();
        layeredPane.setBounds(128, 61, 862, 598);
        contentPane.add(layeredPane);

        idCustomerLabel = new JLabel("卡号");
        idCustomerLabel.setFont(new Font("宋体", Font.PLAIN, 30));
        idCustomerLabel.setBounds(311, 102, 158, 43);
        layeredPane.add(idCustomerLabel);

        nameCustomerLabel = new JLabel("姓名");
        nameCustomerLabel.setFont(new Font("宋体", Font.PLAIN, 30));
        nameCustomerLabel.setBounds(241, 171, 81, 32);
        layeredPane.add(nameCustomerLabel);

        passwordLabel = new JLabel("密码");
        passwordLabel.setFont(new Font("宋体", Font.PLAIN, 30));
        passwordLabel.setBounds(507, 171, 93, 32);
        layeredPane.add(passwordLabel);

        levelLabel = new JLabel("等级");
        levelLabel.setFont(new Font("宋体", Font.PLAIN, 30));
        levelLabel.setBounds(241, 218, 81, 38);
        layeredPane.add(levelLabel);

        idCustomertextField = new JTextField();
        idCustomertextField.setFont(new Font("宋体", Font.PLAIN, 30));
        idCustomertextField.setBounds(491, 102, 146, 43);
        idCustomertextField.setColumns(10);
        layeredPane.add(idCustomertextField);

        showNameCustomerLabel = new JLabel("");
        showNameCustomerLabel.setFont(new Font("宋体", Font.PLAIN, 30));
        showNameCustomerLabel.setBounds(348, 171, 144, 32);
        layeredPane.add(showNameCustomerLabel);

        showPasswordLabel = new JLabel("");
        showPasswordLabel.setFont(new Font("宋体", Font.PLAIN, 30));
        showPasswordLabel.setBounds(604, 170, 137, 33);
        layeredPane.add(showPasswordLabel);

        showLevelLabel = new JLabel("");
        showLevelLabel.setFont(new Font("宋体", Font.PLAIN, 30));
        showLevelLabel.setBounds(355, 218, 137, 38);
        layeredPane.add(showLevelLabel);

        JButton btnNewButton = new JButton(new ImageIcon("image/query.jpg"));
        btnNewButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                show_data();
            }
        });
        btnNewButton.setBounds(401, 540, 105, 43);
        layeredPane.add(btnNewButton);

        carScrollPane = new JScrollPane(carJtable);
        carScrollPane.setBounds(197, 271, 576, 260);
        layeredPane.add(carScrollPane);

        JLabel background1 = new JLabel(new ImageIcon("image/background2.jpg"));
        background1.setBounds(0, 0, 990, 659);
        contentPane.add(background1);
    }

    private void show_data() {

        carJtable = new JTable();
        carJtable.setAutoResizeMode(JTable.AUTO_RESIZE_SUBSEQUENT_COLUMNS);
        carJtable.setRowHeight(54);

        defaultModel = (DefaultTableModel) carJtable.getModel();
        defaultModel.setRowCount(0);
        defaultModel.setColumnIdentifiers(new Object[] { "编号", "车名", "押金", "租金" });

        carJtable.getTableHeader().setReorderingAllowed(false);
        carJtable.setModel(defaultModel);

        carJtable.getColumnModel().getColumn(0).setPreferredWidth(10);
        carJtable.getColumnModel().getColumn(1).setPreferredWidth(80);
        carJtable.getColumnModel().getColumn(2).setPreferredWidth(20);
        carJtable.getColumnModel().getColumn(3).setPreferredWidth(20);

        CustomerTools customerTools = new CustomerTools();
        Customer customer = new Customer();
        BorrowTools borrowtools = new BorrowTools();

        if (idCustomertextField.getText() != null && !"".equals(idCustomertextField.getText())) {
            customer.setUserID(idCustomertextField.getText());
        } else {
            JOptionPane.showMessageDialog(this, "请输入用户编号", "", JOptionPane.WARNING_MESSAGE);
            return;
        }
        java.util.List<Customer> customerList = customerTools.customersData(customer.getUserID());
        List<Car> carList = borrowtools.CarData(customer.getUserID());
        CustomerLevelTools customerLevelTools = new CustomerLevelTools();

        // Check the idReader

        if (customerList.size() == 0) {
            JOptionPane.showMessageDialog(this, "用户编号错误，请输入正确的用户编号 ", "", JOptionPane.WARNING_MESSAGE);
            return;
        } else {
            for (Iterator<Customer> iterator = customerList.iterator(); iterator.hasNext();) {
                Customer temp = (Customer) iterator.next();
                CustomerLevel customerLevel = customerLevelTools.levelData(temp.getUserID());
                showNameCustomerLabel.setText(temp.getUsername());
                showPasswordLabel.setText(temp.getUserPassword());
                showLevelLabel.setText(String.valueOf(customerLevel.getUserLevel()));
            }
            for (Iterator<Car> iterator = carList.iterator(); iterator.hasNext();) {
                Car temp = (Car) iterator.next();
                defaultModel.addRow(new Object[] { temp.getCarID(), temp.getCarName(), temp.getCarPrice() + "元",
                        temp.getBorrowPrice() });
            }
        }
        carScrollPane.setViewportView(carJtable);
    }

    public void CloseFrame() {
        super.dispose();
    }
}
