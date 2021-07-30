package lab3.database.course.frame;

import lab3.database.course.dao.Customer;
import lab3.database.course.dao.CustomerLevel;
import lab3.database.course.sqltools.CustomerLevelTools;
import lab3.database.course.sqltools.CustomerTools;

import javax.swing.*;
import javax.swing.border.EmptyBorder;
import javax.swing.table.DefaultTableModel;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Iterator;
import java.util.List;

public class All_CustomerFrame extends JFrame {
    private static final long serialVersionUID = 1L;
    private JPanel contentPane;

    private JScrollPane customerScrollPane;
    public JTable customerJtable;
    private DefaultTableModel defaultModel;
    public int row;

    private JButton updateButton;
    private JButton deleteButton;

    public All_CustomerFrame()
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

        customerScrollPane = new JScrollPane();
        customerScrollPane.setBounds(302, 197, 611, 381);
        contentPane.add(customerScrollPane);

        updateButton = new JButton(new ImageIcon("image/update.jpg"));
        updateButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                update_Customer();
            }
        });
        updateButton.setBounds(417, 604, 123, 40);
        contentPane.add(updateButton);

        deleteButton = new JButton(new ImageIcon("image/delete.jpg"));
        deleteButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                delete_data();
            }
        });
        deleteButton.setBounds(628, 604, 123, 40);
        contentPane.add(deleteButton);

        show_data();

        JLabel background1 = new JLabel(new ImageIcon("image/background2.jpg"));
        background1.setBounds(0, 0, 990, 659);
        contentPane.add(background1);
    }

    private void update_Customer() {
        row = customerJtable.getSelectedRow();
        if (row == -1) {
            JOptionPane.showMessageDialog(this, "请选择用户！", "", JOptionPane.WARNING_MESSAGE);
            return;
        }
        Customer_UpdateFrame customer_updateFrame = new Customer_UpdateFrame(All_CustomerFrame.this);
        customer_updateFrame.setVisible(true);
    }

    private void delete_data() {
        int row = customerJtable.getSelectedRow();
        if (row == -1) {
            JOptionPane.showMessageDialog(this, "请选择用户", "", JOptionPane.WARNING_MESSAGE);
            return;
        }
        CustomerTools customerTools = new CustomerTools();
        CustomerLevelTools customerLevelTools = new CustomerLevelTools();
        int j = customerLevelTools.DeleteCustomerLevel(customerJtable.getValueAt(row,0).toString());
        int i = customerTools.DeleteCustomer(customerJtable.getValueAt(row, 0).toString());

        if (i == 1 || j==1) {
            JOptionPane.showMessageDialog(getContentPane(), "成功删除用户信息！", "", JOptionPane.WARNING_MESSAGE);
            this.show_data();
            return;
        } else {
            JOptionPane.showMessageDialog(getContentPane(), "删除用户信息失败！", "", JOptionPane.WARNING_MESSAGE);
            return;
        }
    }

    private void show_data() {

        customerJtable = new JTable();
        customerJtable.setAutoResizeMode(JTable.AUTO_RESIZE_SUBSEQUENT_COLUMNS);
        customerJtable.setRowHeight(54);

        defaultModel = (DefaultTableModel) customerJtable.getModel();
        defaultModel.setRowCount(0);
        defaultModel.setColumnIdentifiers(new Object[] { "卡号", "姓名","密码" ,"等级"});

        customerJtable.getTableHeader().setReorderingAllowed(false);
        customerJtable.setModel(defaultModel);

        customerJtable.getColumnModel().getColumn(0).setPreferredWidth(10);
        customerJtable.getColumnModel().getColumn(1).setPreferredWidth(80);
        customerJtable.getColumnModel().getColumn(2).setPreferredWidth(10);
        customerJtable.getColumnModel().getColumn(3).setPreferredWidth(10);

        CustomerTools customerTools = new CustomerTools();
        List<Customer> customerList = customerTools.customersData();
        CustomerLevelTools customerLevelTools = new CustomerLevelTools();

        for (Iterator<Customer> iterator = customerList.iterator(); iterator.hasNext();) {
            Customer temp = (Customer) iterator.next();
            CustomerLevel level = customerLevelTools.levelData(temp.getUserID());
            defaultModel.addRow(new Object[] { temp.getUserID(), temp.getUsername(),
                    temp.getUserPassword(),level.getUserLevel() });
        }
        customerScrollPane.setViewportView(customerJtable);
    }

    public void CloseFrame() {
        super.dispose();
    }
}
