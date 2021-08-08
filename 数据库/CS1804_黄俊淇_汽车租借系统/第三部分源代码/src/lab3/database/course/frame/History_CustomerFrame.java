package lab3.database.course.frame;

import lab3.database.course.dao.Borrow;
import lab3.database.course.dao.Borrowed;
import lab3.database.course.dao.Money;
import lab3.database.course.sqltools.BorrowTools;
import lab3.database.course.sqltools.BorrowedTools;

import javax.swing.*;
import javax.swing.border.EmptyBorder;
import javax.swing.table.DefaultTableModel;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Iterator;
import java.util.List;

public class History_CustomerFrame extends JFrame {
    private static final long serialVersionUID = 1L;
    private JPanel contentPane;
    private JScrollPane borrowScrollPane;

    public JTable borrowJtable;
    private DefaultTableModel defaultModel;

    public History_CustomerFrame(){
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

        borrowScrollPane = new JScrollPane();
        borrowScrollPane.setBounds(293, 253, 658, 332);
        contentPane.add(borrowScrollPane);

        show_data();

        JLabel background1 = new JLabel(new ImageIcon("image/background2.jpg"));
        background1.setBounds(0, 0, 990, 659);
        contentPane.add(background1);
    }

    private void show_data(){
        borrowJtable = new JTable();
        borrowJtable.setAutoResizeMode(JTable.AUTO_RESIZE_SUBSEQUENT_COLUMNS);
        borrowJtable.setRowHeight(54);

        defaultModel = (DefaultTableModel) borrowJtable.getModel();
        defaultModel.setRowCount(0);
        defaultModel.setColumnIdentifiers(new Object[] {"用户ID","车辆ID"," 车辆使用情况","借车时间","截止时间","是否超时","是否已还"});

        borrowJtable.getTableHeader().setReorderingAllowed(false);
        borrowJtable.setModel(defaultModel);

        borrowJtable.getColumnModel().getColumn(0).setPreferredWidth(5);
        borrowJtable.getColumnModel().getColumn(1).setPreferredWidth(10);
        borrowJtable.getColumnModel().getColumn(2).setPreferredWidth(20);
        borrowJtable.getColumnModel().getColumn(3).setPreferredWidth(80);
        borrowJtable.getColumnModel().getColumn(4).setPreferredWidth(80);
        borrowJtable.getColumnModel().getColumn(5).setPreferredWidth(10);
        borrowJtable.getColumnModel().getColumn(6).setPreferredWidth(15);

        BorrowTools borrowTools = new BorrowTools();
        List<Borrow> borrowList = borrowTools.getUsingCar(LoginFrame.userID);

        BorrowedTools borrowedTools = new BorrowedTools();
        List<Borrowed> borrowedList = borrowedTools.getUsedCar(LoginFrame.userID);


        for (Iterator<Borrow> iterator = borrowList.iterator(); iterator.hasNext();){
            Borrow temp = (Borrow) iterator.next();
            defaultModel.addRow(new Object[]{temp.getUserID(),temp.getCarID(),temp.getCarCondition(),
                    temp.getBorrowTime(),temp.getDueTime(),temp.getOverTime(),"未还"});
        }

        for (Iterator<Borrowed> iterator = borrowedList.iterator(); iterator.hasNext();){
            Borrowed temp = (Borrowed) iterator.next();
            defaultModel.addRow(new Object[]{temp.getUserID(),temp.getCarID(),temp.getCarCondition(),
                    temp.getBorrowTime(),temp.getDueTime(),temp.getOverTime(),"已还"});
        }
        borrowScrollPane.setViewportView(borrowJtable);
    }

    public void CloseFrame() {
        super.dispose();
    }
}
