package lab3.database.course.frame;

import lab3.database.course.dao.Car;
import lab3.database.course.sqltools.BorrowTools;
import lab3.database.course.sqltools.CarTools;

import javax.swing.*;
import javax.swing.border.EmptyBorder;
import javax.swing.table.DefaultTableModel;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;
import java.util.Iterator;
import java.util.List;

public class All_CarFrame extends JFrame implements ItemListener {
    private static final long serialVersionUID = 1L;
    private JPanel contentPane;

    private JScrollPane carScrollPane;
    public JTable carJtable;
    private DefaultTableModel defaultModel;
    public int row;

    private JButton updateButton;
    private JButton deleteButton;
    private JButton searchButton;

    private String searchType = "idCar";
    private JRadioButton nameCarRadioButton;
    private JRadioButton idCarRadioButton;
    private ButtonGroup group;

    private JTextField searchtextField;

    public All_CarFrame()
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

        carScrollPane = new JScrollPane();
        carScrollPane.setBounds(293, 253, 658, 332);
        contentPane.add(carScrollPane);

        deleteButton = new JButton(new ImageIcon("image/delete.jpg"));
        deleteButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                delete_Book();
            }
        });
        deleteButton.setBounds(641, 600, 128, 44);
        contentPane.add(deleteButton);

        searchtextField = new JTextField();
        searchtextField.setFont(new Font("宋体", Font.PLAIN, 18));
        searchtextField.setBounds(300, 166, 492, 35);
        contentPane.add(searchtextField);
        searchtextField.setColumns(10);

        searchButton = new JButton(new ImageIcon("image/search.jpg"));
        searchButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                do_search_car();
            }
        });
        searchButton.setBounds(838, 166, 97, 35);
        contentPane.add(searchButton);

        idCarRadioButton = new JRadioButton("按编号搜索");
        idCarRadioButton.setFont(new Font("宋体", Font.PLAIN, 18));
        idCarRadioButton.setBounds(346, 213, 177, 29);
        contentPane.add(idCarRadioButton);
        idCarRadioButton.setSelected(true);
        idCarRadioButton.addItemListener(this);
        idCarRadioButton.setContentAreaFilled(false);

        nameCarRadioButton = new JRadioButton("按车名搜索");
        nameCarRadioButton.setFont(new Font("宋体", Font.PLAIN, 18));
        nameCarRadioButton.setBackground(UIManager.getColor("Button.disabledShadow"));
        nameCarRadioButton.setBounds(568, 213, 177, 29);
        contentPane.add(nameCarRadioButton);
        nameCarRadioButton.addItemListener(this);
        nameCarRadioButton.setContentAreaFilled(false);

        // 将单选按钮加入到一个组里
        group = new ButtonGroup();
        group.add(this.idCarRadioButton);
        group.add(this.nameCarRadioButton);

        updateButton = new JButton(new ImageIcon("image/update.jpg"));
        updateButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                update_car();
            }
        });
        updateButton.setBounds(437, 600, 128, 44);
        contentPane.add(updateButton);

        // 显示全部图书信息
        show_data();

        JLabel background1 = new JLabel(new ImageIcon("image/background2.jpg"));
        background1.setBounds(0, 0, 990, 659);
        contentPane.add(background1);
    }

    private void delete_Book() {
        row = carJtable.getSelectedRow();
        if (row == -1) {
            JOptionPane.showMessageDialog(this, "请选择车辆", "", JOptionPane.WARNING_MESSAGE);
            return;
        }
        CarTools carTools = new CarTools();
        int i = carTools.DeleteCar(carJtable.getValueAt(row, 0).toString());
        if (i == 1) {
            JOptionPane.showMessageDialog(getContentPane(), "成功删除车辆信息！", "", JOptionPane.WARNING_MESSAGE);
            this.show_data();
            return;
        } else {
            JOptionPane.showMessageDialog(getContentPane(), "删除车辆信息失败！", "", JOptionPane.WARNING_MESSAGE);
            return;
        }
    }

    private void do_search_car() {

        // 这个超级大的if语句用于按“书名”进行搜索

        if ("nameCar".equals(searchType)) {

            carJtable = new JTable();
            carJtable.setAutoResizeMode(JTable.AUTO_RESIZE_SUBSEQUENT_COLUMNS);
            carJtable.setRowHeight(54);

            defaultModel = (DefaultTableModel) carJtable.getModel();
            defaultModel.setRowCount(0);
            defaultModel.setColumnIdentifiers(new Object[] { "编号", "车名", "押金", "租金",  "是否在库" });

            carJtable.getTableHeader().setReorderingAllowed(false);
            carJtable.setModel(defaultModel);

            carJtable.getColumnModel().getColumn(0).setPreferredWidth(10);
            carJtable.getColumnModel().getColumn(1).setPreferredWidth(80);
            carJtable.getColumnModel().getColumn(2).setPreferredWidth(20);
            carJtable.getColumnModel().getColumn(3).setPreferredWidth(20);
            carJtable.getColumnModel().getColumn(4).setPreferredWidth(10);

            CarTools carTools = new CarTools();
            BorrowTools borrowtools = new BorrowTools();

            String keyword = null;
            if (searchtextField.getText() != null && !"".equals(searchtextField.getText())) {
                keyword = searchtextField.getText();
            } else {
                JOptionPane.showMessageDialog(this, "请输入车名", "", JOptionPane.WARNING_MESSAGE);
                return;
            }

            List<Car> carList = carTools.CarData(keyword);

            if (carList.size() == 0) {
                JOptionPane.showMessageDialog(this, "未找到有关车辆 ", "", JOptionPane.WARNING_MESSAGE);
                return;
            } else {
                for (Iterator<Car> iterator = carList.iterator(); iterator.hasNext();) {
                    Car temp = (Car) iterator.next();
                    String whetherInStock = null;
                    if (borrowtools.whetherInStock(temp.getCarID()) == true) {
                        whetherInStock = "在库";
                    } else {
                        whetherInStock = "借出";
                    }
                    defaultModel.addRow(new Object[] { temp.getCarID(), temp.getCarName(), temp.getCarPrice() + "元",
                            temp.getBorrowPrice() + "元", whetherInStock });
                }
                carScrollPane.setViewportView(carJtable);
            }
        }

        // 这个超级大的if语句用于按“书编号”进行搜索

        if ("idCar".equals(searchType)) {
            carJtable = new JTable();
            carJtable.setAutoResizeMode(JTable.AUTO_RESIZE_SUBSEQUENT_COLUMNS);
            carJtable.setRowHeight(54);

            defaultModel = (DefaultTableModel) carJtable.getModel();
            defaultModel.setRowCount(0);
            defaultModel.setColumnIdentifiers(new Object[]{"编号", "车名", "押金", "租金", "是否在库"});

            carJtable.getTableHeader().setReorderingAllowed(false);
            carJtable.setModel(defaultModel);

            carJtable.getColumnModel().getColumn(0).setPreferredWidth(10);
            carJtable.getColumnModel().getColumn(1).setPreferredWidth(80);
            carJtable.getColumnModel().getColumn(2).setPreferredWidth(20);
            carJtable.getColumnModel().getColumn(3).setPreferredWidth(20);
            carJtable.getColumnModel().getColumn(4).setPreferredWidth(10);

            CarTools carTools = new CarTools();
            BorrowTools borrowtools = new BorrowTools();

            String keyword = null;
            if (searchtextField.getText() != null && !"".equals(searchtextField.getText())) {
                keyword = searchtextField.getText();
            } else {
                JOptionPane.showMessageDialog(this, "请输入车名", "", JOptionPane.WARNING_MESSAGE);
                return;
            }

            List<Car> carList = borrowtools.CarData_Search_carID(keyword);

            if (carList.size() == 0) {
                JOptionPane.showMessageDialog(this, "未找到有关车辆 ", "", JOptionPane.WARNING_MESSAGE);
                return;
            } else {
                for (Iterator<Car> iterator = carList.iterator(); iterator.hasNext(); ) {
                    Car temp = (Car) iterator.next();
                    String whetherInStock = null;
                    if (borrowtools.whetherInStock(temp.getCarID()) == true) {
                        whetherInStock = "在库";
                    } else {
                        whetherInStock = "借出";
                    }
                    defaultModel.addRow(new Object[]{temp.getCarID(), temp.getCarName(), temp.getCarPrice() + "元",
                            temp.getBorrowPrice() + "元", whetherInStock});
                }
                carScrollPane.setViewportView(carJtable);
            }
        }
    }

    private void update_car() {

        row = carJtable.getSelectedRow();
        if (row == -1) {
            JOptionPane.showMessageDialog(this, "请选择车辆！", "", JOptionPane.WARNING_MESSAGE);
            return;
        }
        Car_UpdateFrame book_UpdateFrame = new Car_UpdateFrame(All_CarFrame.this);
        book_UpdateFrame.setVisible(true);

    }


    private void show_data() {
        carJtable = new JTable();
        carJtable.setAutoResizeMode(JTable.AUTO_RESIZE_SUBSEQUENT_COLUMNS);
        carJtable.setRowHeight(54);

        defaultModel = (DefaultTableModel) carJtable.getModel();
        defaultModel.setRowCount(0);
        defaultModel.setColumnIdentifiers(new Object[] { "编号", "车名", "押金", "租金",  "是否在库" });

        carJtable.getTableHeader().setReorderingAllowed(false);
        carJtable.setModel(defaultModel);

        carJtable.getColumnModel().getColumn(0).setPreferredWidth(10);
        carJtable.getColumnModel().getColumn(1).setPreferredWidth(80);
        carJtable.getColumnModel().getColumn(2).setPreferredWidth(20);
        carJtable.getColumnModel().getColumn(3).setPreferredWidth(20);
        carJtable.getColumnModel().getColumn(4).setPreferredWidth(10);

        CarTools carTools = new CarTools();
        BorrowTools borrowtools = new BorrowTools();

        List<Car> carList = carTools.CarData();

        for (Iterator<Car> iterator = carList.iterator(); iterator.hasNext();) {
            Car temp = (Car) iterator.next();
            String whetherInStock = null;
            if (borrowtools.whetherInStock(temp.getCarID()) == true) {
                whetherInStock = "在库";
            } else {
                whetherInStock = "借出";
            }
            defaultModel.addRow(new Object[] { temp.getCarID(), temp.getCarName(), temp.getCarPrice() + "元",
                    temp.getBorrowPrice() + "元", whetherInStock });
        }
        carScrollPane.setViewportView(carJtable);
    }

    public void CloseFrame() {
        super.dispose();
    }

    @Override
    public void itemStateChanged(ItemEvent e) {
        if (idCarRadioButton.isSelected()) {
            this.searchType = "idCar";
            // System.out.println(this.searchType);
        }
        if (nameCarRadioButton.isSelected()) {
            this.searchType = "nameCar";
            // System.out.println(this.searchType);
        }
    }
}
