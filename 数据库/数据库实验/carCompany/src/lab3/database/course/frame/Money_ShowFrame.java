package lab3.database.course.frame;

import lab3.database.course.dao.Customer;
import lab3.database.course.dao.CustomerLevel;
import lab3.database.course.dao.Money;
import lab3.database.course.sqltools.CustomerLevelTools;
import lab3.database.course.sqltools.CustomerTools;
import lab3.database.course.sqltools.MoneyTools;

import javax.swing.*;
import javax.swing.border.EmptyBorder;
import javax.swing.table.DefaultTableModel;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Iterator;
import java.util.List;

public class Money_ShowFrame extends JFrame {
    private static final long serialVersionUID = 1L;
    private JPanel contentPane;
    private JScrollPane moneyScrollPane;
    public JTable readerJtable;
    private DefaultTableModel defaultModel;
    public int row;

    public Money_ShowFrame()
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

        moneyScrollPane = new JScrollPane();
        moneyScrollPane.setBounds(302, 197, 611, 381);
        contentPane.add(moneyScrollPane);

        show_data();

        JLabel background1 = new JLabel(new ImageIcon("image/background2.jpg"));
        background1.setBounds(0, 0, 990, 659);
        contentPane.add(background1);
    }

    private void show_data()
    {
        readerJtable = new JTable();
        readerJtable.setAutoResizeMode(JTable.AUTO_RESIZE_SUBSEQUENT_COLUMNS);
        readerJtable.setRowHeight(54);

        defaultModel = (DefaultTableModel) readerJtable.getModel();
        defaultModel.setRowCount(0);
        defaultModel.setColumnIdentifiers(new Object[] { "记录ID","用户卡号","会员等级","车辆编号","收支时间","收支明细","退还押金","租金","押金"});

        readerJtable.getTableHeader().setReorderingAllowed(false);
        readerJtable.setModel(defaultModel);

        readerJtable.getColumnModel().getColumn(0).setPreferredWidth(5);
        readerJtable.getColumnModel().getColumn(1).setPreferredWidth(10);
        readerJtable.getColumnModel().getColumn(2).setPreferredWidth(5);
        readerJtable.getColumnModel().getColumn(3).setPreferredWidth(10);
        readerJtable.getColumnModel().getColumn(4).setPreferredWidth(80);
        readerJtable.getColumnModel().getColumn(5).setPreferredWidth(80);
        readerJtable.getColumnModel().getColumn(6).setPreferredWidth(15);
        readerJtable.getColumnModel().getColumn(7).setPreferredWidth(15);
        readerJtable.getColumnModel().getColumn(8).setPreferredWidth(15);

        MoneyTools moneyTools = new MoneyTools();
        CustomerLevelTools customerLevelTools = new CustomerLevelTools();
        List<Money> moneyList = moneyTools.moneyData();

        for (Iterator<Money> iterator = moneyList.iterator(); iterator.hasNext();) {
            Money temp = (Money) iterator.next();
            CustomerLevel level = customerLevelTools.levelData(temp.getUserID());
            defaultModel.addRow(new Object[] {temp.getMoneyID(), temp.getUserID(),level.getUserLevel(),temp.getCarID(),
            temp.getMoneyTime(),temp.getMoneyDetail(),temp.getMoneyback(),temp.getPrice(),temp.getBack()});
        }
        moneyScrollPane.setViewportView(readerJtable);
    }

    public void CloseFrame() {
        super.dispose();
    }
}
