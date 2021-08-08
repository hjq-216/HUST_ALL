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
import java.util.Iterator;
import java.util.List;

public class Search_CarFrame extends JFrame {
    private static final long serialVersionUID = 1L;

    private JPanel contentPane;

    private JScrollPane carScrollPane;
    public JTable carJtable;
    private DefaultTableModel defaultModel;
    public static int row;

    private JLabel messageLabel;
    private JTextField nameCarField;
    private JButton searchButton;
    private JButton borrowButton;

    public Search_CarFrame(){
        setResizable(false);
        setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        setBounds(100, 100, 996, 699);
        contentPane = new JPanel();
        contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
        setContentPane(contentPane);
        contentPane.setLayout(null);

        JButton borrow_Button = new JButton("借车");
        borrow_Button.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                Search_CarFrame search_carFrame = new Search_CarFrame();
                search_carFrame.setVisible(true);
                CloseFrame();
            }
        });
        borrow_Button.setBounds(77, 288, 123, 29);
        contentPane.add(borrow_Button);

        JButton history_Button = new JButton("租借历史");
        history_Button.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                History_CustomerFrame history_customerFrame = new History_CustomerFrame();
                history_customerFrame.setVisible(true);
                CloseFrame();
            }
        });
        history_Button.setBounds(77,380,123,29);
        contentPane.add(history_Button);

        JButton self_info_Button = new JButton("还车");
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

        messageLabel = new JLabel("车名搜索");
        messageLabel.setFont(new Font("宋体", Font.PLAIN, 30));
        messageLabel.setBounds(539, 155, 123, 41);
        contentPane.add(messageLabel);

        nameCarField = new JTextField();
        nameCarField.setFont(new Font("宋体", Font.PLAIN, 30));
        nameCarField.setBounds(370, 209, 292, 37);
        contentPane.add(nameCarField);
        nameCarField.setColumns(10);

        searchButton = new JButton(new ImageIcon("image/search.jpg"));
        searchButton.setFont(new Font("宋体", Font.PLAIN, 30));
        searchButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                do_search_car();
            }
        });
        searchButton.setBounds(712, 209, 123, 41);
        contentPane.add(searchButton);

        carScrollPane = new JScrollPane(carJtable);
        carScrollPane.setBounds(283, 261, 692, 323);
        contentPane.add(carScrollPane);

        borrowButton = new JButton(new ImageIcon("image/borrow.jpg"));
        borrowButton.setFont(new Font("宋体", Font.PLAIN, 30));
        borrowButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                do_borrow_car();
            }
        });
        borrowButton.setBounds(539, 603, 123, 41);
        contentPane.add(borrowButton);

        // 显示全部图书信息
        show_data();

        JLabel background1 = new JLabel(new ImageIcon("image/background2.jpg"));
        background1.setBounds(0, 0, 990, 659);
        contentPane.add(background1);
    }

    private void do_search_car() {

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
        if (nameCarField.getText() != null && !"".equals(nameCarField.getText())) {
            keyword = nameCarField.getText();
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

    private void do_borrow_car() {

        row = carJtable.getSelectedRow();
        if (row == -1) {
            JOptionPane.showMessageDialog(this, "请选择车辆", "", JOptionPane.WARNING_MESSAGE);
            return;
        }
        if ("借出".equals(carJtable.getValueAt(row, 4).toString())) {
            JOptionPane.showMessageDialog(this, "车辆已被借出", "", JOptionPane.WARNING_MESSAGE);
            return;
        } else {
            BorrowTools borrowtools = new BorrowTools();
            String userID = LoginFrame.userID;
            String carID = carJtable.getValueAt(row, 0).toString();
            int i = borrowtools.BorrowCar(userID, carID);
            if (i == 1) {
                JOptionPane.showMessageDialog(this, "借车成功", "", JOptionPane.WARNING_MESSAGE);
                return;
            } else {
                JOptionPane.showMessageDialog(this, "借车失败", "", JOptionPane.WARNING_MESSAGE);
                return;
            }
        }
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

        List<Car> carList = carTools.CarData();
        BorrowTools borrowtools = new BorrowTools();

        for (Iterator<Car> iterator = carList.iterator(); iterator.hasNext();) {
            Car temp = (Car) iterator.next();
            // Check the idReader
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
}
