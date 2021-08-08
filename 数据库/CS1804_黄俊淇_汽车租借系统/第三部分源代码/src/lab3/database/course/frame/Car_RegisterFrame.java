package lab3.database.course.frame;

import lab3.database.course.dao.Car;
import lab3.database.course.sqltools.CarTools;

import javax.swing.*;
import javax.swing.border.EmptyBorder;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class Car_RegisterFrame extends JFrame{
    private static final long serialVersionUID = 1L;
    private JPanel contentPane;

    private JTextField idCartextField;
    private JTextField nameCartextField;
    private JTextField priceField;
    private JTextField backtextField;

    private JLabel idCarLabel;
    private JLabel nameCarLabel;
    private JLabel priceLabel;
    private JLabel backLabel;

    private JButton insertButton;

    public Car_RegisterFrame()
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

        idCarLabel = new JLabel("车辆编号");
        idCarLabel.setFont(new Font("宋体", Font.PLAIN, 30));
        idCarLabel.setBounds(448, 163, 131, 51);
        contentPane.add(idCarLabel);

        nameCarLabel = new JLabel("车名");
        nameCarLabel.setFont(new Font("宋体", Font.PLAIN, 30));
        nameCarLabel.setBounds(469, 229, 81, 51);
        contentPane.add(nameCarLabel);

        priceLabel = new JLabel("租金");
        priceLabel.setFont(new Font("宋体", Font.PLAIN, 30));
        priceLabel.setBounds(469, 292, 81, 51);
        contentPane.add(priceLabel);

        backLabel = new JLabel("押金");
        backLabel.setFont(new Font("宋体", Font.PLAIN, 30));
        backLabel.setBounds(469, 358, 81, 44);
        contentPane.add(backLabel);

        idCartextField = new JTextField();
        idCartextField.setFont(new Font("宋体", Font.PLAIN, 30));
        idCartextField.setBounds(594, 168, 131, 41);
        contentPane.add(idCartextField);
        idCartextField.setColumns(10);

        nameCartextField = new JTextField();
        nameCartextField.setFont(new Font("宋体", Font.PLAIN, 30));
        nameCartextField.setBounds(594, 236, 131, 37);
        contentPane.add(nameCartextField);
        nameCartextField.setColumns(10);

        priceField = new JTextField();
        priceField.setFont(new Font("宋体", Font.PLAIN, 30));
        priceField.setBounds(594, 299, 131, 37);
        contentPane.add(priceField);
        priceField.setColumns(10);

        backtextField = new JTextField();
        backtextField.setFont(new Font("宋体", Font.PLAIN, 30));
        backtextField.setBounds(594, 367, 131, 37);
        contentPane.add(backtextField);
        backtextField.setColumns(10);

        insertButton = new JButton(new ImageIcon("image/new.jpg"));
        insertButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                do_insertButton_AddCar();
            }
        });
        insertButton.setBounds(544, 582, 106, 44);
        contentPane.add(insertButton);

        JLabel background1 = new JLabel(new ImageIcon("image/background2.jpg"));
        background1.setBounds(0, 0, 990, 659);
        contentPane.add(background1);
    }

    protected void do_insertButton_AddCar() {

        CarTools carTools = new CarTools();
        Car car = new Car();


        if (idCartextField.getText() != null && !"".equals(idCartextField.getText())
                && nameCartextField.getText() != null && !"".equals(nameCartextField.getText())
                && priceField.getText() != null && !"".equals(priceField.getText()) && backtextField.getText() != null
                && !"".equals(backtextField.getText()) ) {
            car.setCarID(idCartextField.getText());
            car.setCarName(nameCartextField.getText());
            car.setCarPrice(priceField.getText());
            car.setBorrowPrice(backtextField.getText());
            int i = carTools.AddCar(car);
            if (i == 1) {
                JOptionPane.showMessageDialog(getContentPane(), "成功新增车辆信息！", "", JOptionPane.WARNING_MESSAGE);
                return;
            } else {
                JOptionPane.showMessageDialog(getContentPane(), "新增车辆信息失败！", "", JOptionPane.WARNING_MESSAGE);
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
