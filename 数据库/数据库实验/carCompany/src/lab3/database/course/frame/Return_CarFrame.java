package lab3.database.course.frame;

import lab3.database.course.dao.Car;
import lab3.database.course.dao.Customer;
import lab3.database.course.sqltools.BorrowTools;
import lab3.database.course.sqltools.CustomerTools;

import javax.swing.*;
import javax.swing.border.EmptyBorder;
import javax.swing.table.DefaultTableModel;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Iterator;
import java.util.List;

public class Return_CarFrame extends JFrame{
    private static final long serialVersionUID = 1L;
    private JPanel contentPane;
    private JLayeredPane layeredPane;

    private JScrollPane bookScrollPane;
    private JTable bookJtable;
    private DefaultTableModel defaultModel;
    public static int row;

    private JLabel idReaderLabel;
    private JLabel nameReaderLabel;
    private JLabel typeLabel;
    private JLabel sexLabel;
    private JLabel passwordLabel;

    private JLabel showidReaderLabel;
    private JLabel showNameReaderLabel;
    private JLabel showPasswordLabel;

    private JButton return_BookButton;

    public Return_CarFrame() {
        setResizable(false);
        setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        setBounds(100, 100, 996, 699);
        contentPane = new JPanel();
        contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
        setContentPane(contentPane);
        contentPane.setLayout(null);

        JButton borrow_Button = new JButton("借书");
        borrow_Button.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                Search_CarFrame search_carFrame = new Search_CarFrame();
                search_carFrame.setVisible(true);
                CloseFrame();
            }
        });
        borrow_Button.setBounds(77, 288, 123, 29);
        contentPane.add(borrow_Button);

        JButton self_info_Button = new JButton("还书");
        self_info_Button.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {

                Return_CarFrame return_carFrame = new Return_CarFrame();
                return_carFrame.setVisible(true);
                CloseFrame();
            }
        });
        self_info_Button.setBounds(77, 474, 123, 29);
        contentPane.add(self_info_Button);

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

        idReaderLabel = new JLabel("卡号");
        idReaderLabel.setFont(new Font("宋体", Font.PLAIN, 30));
        idReaderLabel.setBounds(311, 102, 158, 43);
        layeredPane.add(idReaderLabel);

        nameReaderLabel = new JLabel("姓名");
        nameReaderLabel.setFont(new Font("宋体", Font.PLAIN, 30));
        nameReaderLabel.setBounds(241, 171, 81, 32);
        layeredPane.add(nameReaderLabel);

        passwordLabel = new JLabel("密码");
        passwordLabel.setFont(new Font("宋体", Font.PLAIN, 30));
        passwordLabel.setBounds(241, 218, 81, 38);
        layeredPane.add(passwordLabel);

        showidReaderLabel = new JLabel();
        showidReaderLabel.setFont(new Font("宋体", Font.PLAIN, 30));
        showidReaderLabel.setBounds(491, 102, 146, 43);
        layeredPane.add(showidReaderLabel);
        showidReaderLabel.setText(LoginFrame.userID);

        showNameReaderLabel = new JLabel("");
        showNameReaderLabel.setFont(new Font("宋体", Font.PLAIN, 30));
        showNameReaderLabel.setBounds(348, 171, 144, 32);
        layeredPane.add(showNameReaderLabel);

        showPasswordLabel = new JLabel("");
        showPasswordLabel.setFont(new Font("宋体", Font.PLAIN, 30));
        showPasswordLabel.setBounds(348, 218, 144, 32);
        layeredPane.add(showPasswordLabel);

        bookScrollPane = new JScrollPane(bookJtable);
        bookScrollPane.setBounds(197, 271, 576, 249);
        layeredPane.add(bookScrollPane);

        return_BookButton = new JButton(new ImageIcon("image/return.jpg"));
        return_BookButton.setBounds(401, 540, 123, 43);
        return_BookButton.setFont(new Font("宋体", Font.PLAIN, 30));
        return_BookButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                do_borrow_car();
            }
        });
        layeredPane.add(return_BookButton);

        show_data();

        JLabel background1 = new JLabel(new ImageIcon("image/background2.jpg"));
        background1.setBounds(0, 0, 990, 659);
        contentPane.add(background1);
    }

    private void do_borrow_car() {

        row = bookJtable.getSelectedRow();
        if (row == -1) {
            JOptionPane.showMessageDialog(this, "请选择书籍", "", JOptionPane.WARNING_MESSAGE);
            return;
        }
        BorrowTools borrowtools = new BorrowTools();
        String idbook = bookJtable.getValueAt(row, 0).toString();
        int i = borrowtools.ReturnCar(idbook);
        if (i == 1) {
            JOptionPane.showMessageDialog(this, "还车成功", "", JOptionPane.WARNING_MESSAGE);
            show_data();
            return;
        } else {
            JOptionPane.showMessageDialog(this, "还车失败", "", JOptionPane.WARNING_MESSAGE);
            show_data();
            return;
        }
    }

    private void show_data() {

        bookJtable = new JTable();
        bookJtable.setAutoResizeMode(JTable.AUTO_RESIZE_SUBSEQUENT_COLUMNS);
        bookJtable.setRowHeight(54);

        defaultModel = (DefaultTableModel) bookJtable.getModel();
        defaultModel.setRowCount(0);
        defaultModel.setColumnIdentifiers(new Object[] { "编号", "车名", "押金", "租金"});
        bookJtable.getTableHeader().setReorderingAllowed(false);
        bookJtable.setModel(defaultModel);

        bookJtable.getColumnModel().getColumn(0).setPreferredWidth(10);
        bookJtable.getColumnModel().getColumn(1).setPreferredWidth(80);
        bookJtable.getColumnModel().getColumn(2).setPreferredWidth(20);
        bookJtable.getColumnModel().getColumn(3).setPreferredWidth(20);

        CustomerTools customerTools = new CustomerTools();
        Customer customer = new Customer();
        BorrowTools borrowtools = new BorrowTools();

        if (showidReaderLabel.getText() != null && !"".equals(showidReaderLabel.getText())) {
            customer.setUserID(showidReaderLabel.getText());
        } else {
            JOptionPane.showMessageDialog(this, "请输入客户编号", "", JOptionPane.WARNING_MESSAGE);
            return;
        }
        java.util.List<Customer> customerList = customerTools.customersData(customer.getUserID());
        List<Car> carList = borrowtools.CarData(customer.getUserID());

        // Check the idReader

        if (customerList.size() == 0) {
            JOptionPane.showMessageDialog(this, "客户编号错误，请输入正确的客户编号 ", "", JOptionPane.WARNING_MESSAGE);
            return;
        } else {
            for (Iterator<Customer> iterator = customerList.iterator(); iterator.hasNext();) {
                Customer temp = (Customer) iterator.next();
                showNameReaderLabel.setText(temp.getUsername());
                showPasswordLabel.setText(temp.getUserPassword());
            }
            for (Iterator<Car> iterator = carList.iterator(); iterator.hasNext();) {
                Car temp = (Car) iterator.next();
                defaultModel.addRow(new Object[] { temp.getCarID(), temp.getCarName(), temp.getCarPrice() + "元",
                        temp.getBorrowPrice() + "元" });
            }
        }
        bookScrollPane.setViewportView(bookJtable);
    }

    public void CloseFrame() {
        super.dispose();
    }
}
