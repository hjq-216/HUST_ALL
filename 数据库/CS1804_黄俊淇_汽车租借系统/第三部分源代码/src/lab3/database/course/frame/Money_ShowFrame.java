package lab3.database.course.frame;

import lab3.database.course.dao.CustomerLevel;
import lab3.database.course.dao.Money;
import lab3.database.course.sqltools.CustomerLevelTools;
import lab3.database.course.sqltools.MoneyTools;
import org.jfree.chart.ChartFactory;
import org.jfree.chart.ChartFrame;
import org.jfree.chart.JFreeChart;
import org.jfree.chart.StandardChartTheme;
import org.jfree.chart.plot.CategoryPlot;
import org.jfree.chart.plot.PlotOrientation;
import org.jfree.data.category.CategoryDataset;
import org.jfree.data.category.DefaultCategoryDataset;

import javax.swing.*;
import javax.swing.border.EmptyBorder;
import javax.swing.table.DefaultTableModel;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;
import java.util.*;
import java.util.List;

public class Money_ShowFrame extends JFrame implements ItemListener {
    private static final long serialVersionUID = 1L;
    private JPanel contentPane;
    private JScrollPane moneyScrollPane;
    public JTable customerJtable;
    private DefaultTableModel defaultModel;
    public int row;
    private JTextField searchtextField;
    private JButton generateYearButton;

    private String searchType = "none";
    private JRadioButton noneButton;
    private JRadioButton dayButton;
    private JRadioButton monthButton;
    private JRadioButton yearButton;
    private ButtonGroup group;


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
        moneyScrollPane.setBounds(293, 253, 611, 381);
        contentPane.add(moneyScrollPane);

//        searchtextField = new JTextField();
//        searchtextField.setFont(new Font("宋体", Font.PLAIN, 18));
//        searchtextField.setBounds(300, 166, 492, 35);
//        contentPane.add(searchtextField);
//        searchtextField.setColumns(10);
//
        generateYearButton = new JButton(new ImageIcon("image/generate.png"));
        generateYearButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                do_generate_year();
            }
        });
        generateYearButton.setBounds(346, 166, 129, 44);
        contentPane.add(generateYearButton);

        noneButton = new JRadioButton("无");
        noneButton.setFont(new Font("宋体", Font.PLAIN, 18));
        noneButton.setBounds(346, 213, 100, 29);
        contentPane.add(noneButton);
        noneButton.setSelected(true);
        noneButton.addItemListener(this);
        noneButton.setContentAreaFilled(false);
        noneButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                show_data();
            }
        });

        dayButton = new JRadioButton("最近7天");
        dayButton.setFont(new Font("宋体", Font.PLAIN, 18));
        dayButton.setBackground(UIManager.getColor("Button.disabledShadow"));
        dayButton.setBounds(446, 213, 150, 29);
        contentPane.add(dayButton);
        dayButton.addItemListener(this);
        dayButton.setContentAreaFilled(false);
        dayButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                show_data();
            }
        });

        monthButton = new JRadioButton("最近一个月");
        monthButton.setFont(new Font("宋体", Font.PLAIN, 12));
        monthButton.setBackground(UIManager.getColor("Button.disabledShadow"));
        monthButton.setBounds(596, 213, 120, 29);
        contentPane.add(monthButton);
        monthButton.addItemListener(this);
        monthButton.setContentAreaFilled(false);
        monthButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                show_data();
            }
        });

        yearButton = new JRadioButton("最近一年");
        yearButton.setFont(new Font("宋体", Font.PLAIN, 18));
        yearButton.setBackground(UIManager.getColor("Button.disabledShadow"));
        yearButton.setBounds(746, 213, 177, 29);
        contentPane.add(yearButton);
        yearButton.addItemListener(this);
        yearButton.setContentAreaFilled(false);
        yearButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                show_data();
            }
        });

        group = new ButtonGroup();
        group.add(noneButton);
        group.add(dayButton);
        group.add(monthButton);
        group.add(yearButton);

        show_data();

        JLabel background1 = new JLabel(new ImageIcon("image/background2.jpg"));
        background1.setBounds(0, 0, 990, 659);
        contentPane.add(background1);
    }

    private void show_data()
    {
        if ("none".equals(searchType)){
            customerJtable = new JTable();
            customerJtable.setAutoResizeMode(JTable.AUTO_RESIZE_SUBSEQUENT_COLUMNS);
            customerJtable.setRowHeight(54);

            defaultModel = (DefaultTableModel) customerJtable.getModel();
            defaultModel.setRowCount(0);
            defaultModel.setColumnIdentifiers(new Object[] { "记录ID","用户卡号","会员等级","车辆编号","收支时间","收支明细","退还押金","租金","押金"});

            customerJtable.getTableHeader().setReorderingAllowed(false);
            customerJtable.setModel(defaultModel);

            customerJtable.getColumnModel().getColumn(0).setPreferredWidth(5);
            customerJtable.getColumnModel().getColumn(1).setPreferredWidth(10);
            customerJtable.getColumnModel().getColumn(2).setPreferredWidth(5);
            customerJtable.getColumnModel().getColumn(3).setPreferredWidth(10);
            customerJtable.getColumnModel().getColumn(4).setPreferredWidth(80);
            customerJtable.getColumnModel().getColumn(5).setPreferredWidth(80);
            customerJtable.getColumnModel().getColumn(6).setPreferredWidth(15);
            customerJtable.getColumnModel().getColumn(7).setPreferredWidth(15);
            customerJtable.getColumnModel().getColumn(8).setPreferredWidth(15);

            MoneyTools moneyTools = new MoneyTools();
            CustomerLevelTools customerLevelTools = new CustomerLevelTools();
            List<Money> moneyList = moneyTools.moneyData();

            for (Iterator<Money> iterator = moneyList.iterator(); iterator.hasNext();) {
                Money temp = (Money) iterator.next();
                CustomerLevel level = customerLevelTools.levelData(temp.getUserID());
                defaultModel.addRow(new Object[] {temp.getMoneyID(), temp.getUserID(),level.getUserLevel(),temp.getCarID(),
                        temp.getMoneyTime(),temp.getMoneyDetail(),temp.getMoneyback(),temp.getPrice(),temp.getBack()});
            }
            moneyScrollPane.setViewportView(customerJtable);
        }
        if ("day".equals(searchType)){
            customerJtable = new JTable();
            customerJtable.setAutoResizeMode(JTable.AUTO_RESIZE_SUBSEQUENT_COLUMNS);
            customerJtable.setRowHeight(54);

            defaultModel = (DefaultTableModel) customerJtable.getModel();
            defaultModel.setRowCount(0);
            defaultModel.setColumnIdentifiers(new Object[] { "记录ID","用户卡号","会员等级","车辆编号","收支时间","收支明细","退还押金","租金","押金"});

            customerJtable.getTableHeader().setReorderingAllowed(false);
            customerJtable.setModel(defaultModel);

            customerJtable.getColumnModel().getColumn(0).setPreferredWidth(5);
            customerJtable.getColumnModel().getColumn(1).setPreferredWidth(10);
            customerJtable.getColumnModel().getColumn(2).setPreferredWidth(5);
            customerJtable.getColumnModel().getColumn(3).setPreferredWidth(10);
            customerJtable.getColumnModel().getColumn(4).setPreferredWidth(80);
            customerJtable.getColumnModel().getColumn(5).setPreferredWidth(80);
            customerJtable.getColumnModel().getColumn(6).setPreferredWidth(15);
            customerJtable.getColumnModel().getColumn(7).setPreferredWidth(15);
            customerJtable.getColumnModel().getColumn(8).setPreferredWidth(15);

            MoneyTools moneyTools = new MoneyTools();
            CustomerLevelTools customerLevelTools = new CustomerLevelTools();
            List<Money> moneyList = moneyTools.money7Day();

            for (Iterator<Money> iterator = moneyList.iterator(); iterator.hasNext();) {
                Money temp = (Money) iterator.next();
                CustomerLevel level = customerLevelTools.levelData(temp.getUserID());
                defaultModel.addRow(new Object[] {temp.getMoneyID(), temp.getUserID(),level.getUserLevel(),temp.getCarID(),
                        temp.getMoneyTime(),temp.getMoneyDetail(),temp.getMoneyback(),temp.getPrice(),temp.getBack()});
            }
            moneyScrollPane.setViewportView(customerJtable);
        }

        if ("month".equals(searchType)){
            customerJtable = new JTable();
            customerJtable.setAutoResizeMode(JTable.AUTO_RESIZE_SUBSEQUENT_COLUMNS);
            customerJtable.setRowHeight(54);

            defaultModel = (DefaultTableModel) customerJtable.getModel();
            defaultModel.setRowCount(0);
            defaultModel.setColumnIdentifiers(new Object[] { "记录ID","用户卡号","会员等级","车辆编号","收支时间","收支明细","退还押金","租金","押金"});

            customerJtable.getTableHeader().setReorderingAllowed(false);
            customerJtable.setModel(defaultModel);

            customerJtable.getColumnModel().getColumn(0).setPreferredWidth(5);
            customerJtable.getColumnModel().getColumn(1).setPreferredWidth(10);
            customerJtable.getColumnModel().getColumn(2).setPreferredWidth(5);
            customerJtable.getColumnModel().getColumn(3).setPreferredWidth(10);
            customerJtable.getColumnModel().getColumn(4).setPreferredWidth(80);
            customerJtable.getColumnModel().getColumn(5).setPreferredWidth(80);
            customerJtable.getColumnModel().getColumn(6).setPreferredWidth(15);
            customerJtable.getColumnModel().getColumn(7).setPreferredWidth(15);
            customerJtable.getColumnModel().getColumn(8).setPreferredWidth(15);

            MoneyTools moneyTools = new MoneyTools();
            CustomerLevelTools customerLevelTools = new CustomerLevelTools();
            List<Money> moneyList = moneyTools.moneyMonth();

            for (Iterator<Money> iterator = moneyList.iterator(); iterator.hasNext();) {
                Money temp = (Money) iterator.next();
                CustomerLevel level = customerLevelTools.levelData(temp.getUserID());
                defaultModel.addRow(new Object[] {temp.getMoneyID(), temp.getUserID(),level.getUserLevel(),temp.getCarID(),
                        temp.getMoneyTime(),temp.getMoneyDetail(),temp.getMoneyback(),temp.getPrice(),temp.getBack()});
            }
            moneyScrollPane.setViewportView(customerJtable);
        }

        if ("year".equals(searchType)){
            customerJtable = new JTable();
            customerJtable.setAutoResizeMode(JTable.AUTO_RESIZE_SUBSEQUENT_COLUMNS);
            customerJtable.setRowHeight(54);

            defaultModel = (DefaultTableModel) customerJtable.getModel();
            defaultModel.setRowCount(0);
            defaultModel.setColumnIdentifiers(new Object[] { "记录ID","用户卡号","会员等级","车辆编号","收支时间","收支明细","退还押金","租金","押金"});

            customerJtable.getTableHeader().setReorderingAllowed(false);
            customerJtable.setModel(defaultModel);

            customerJtable.getColumnModel().getColumn(0).setPreferredWidth(5);
            customerJtable.getColumnModel().getColumn(1).setPreferredWidth(10);
            customerJtable.getColumnModel().getColumn(2).setPreferredWidth(5);
            customerJtable.getColumnModel().getColumn(3).setPreferredWidth(10);
            customerJtable.getColumnModel().getColumn(4).setPreferredWidth(80);
            customerJtable.getColumnModel().getColumn(5).setPreferredWidth(80);
            customerJtable.getColumnModel().getColumn(6).setPreferredWidth(15);
            customerJtable.getColumnModel().getColumn(7).setPreferredWidth(15);
            customerJtable.getColumnModel().getColumn(8).setPreferredWidth(15);

            MoneyTools moneyTools = new MoneyTools();
            CustomerLevelTools customerLevelTools = new CustomerLevelTools();
            List<Money> moneyList = moneyTools.moneyYear();

            for (Iterator<Money> iterator = moneyList.iterator(); iterator.hasNext();) {
                Money temp = (Money) iterator.next();
                CustomerLevel level = customerLevelTools.levelData(temp.getUserID());
                defaultModel.addRow(new Object[] {temp.getMoneyID(), temp.getUserID(),level.getUserLevel(),temp.getCarID(),
                        temp.getMoneyTime(),temp.getMoneyDetail(),temp.getMoneyback(),temp.getPrice(),temp.getBack()});
            }
            moneyScrollPane.setViewportView(customerJtable);
        }
    }

    private void do_generate_year(){
        StandardChartTheme mChartTheme = new StandardChartTheme("CN");
        mChartTheme.setLargeFont(new Font("黑体", Font.BOLD, 20));
        mChartTheme.setExtraLargeFont(new Font("宋体", Font.PLAIN, 15));
        mChartTheme.setRegularFont(new Font("宋体", Font.PLAIN, 15));
        ChartFactory.setChartTheme(mChartTheme);
        CategoryDataset mDataset = GetDatasetYear();
        JFreeChart mChart = ChartFactory.createLineChart(
                "公司年度报表",//图名字
                "年份",//横坐标
                "收入",//纵坐标
                mDataset,//数据集
                PlotOrientation.VERTICAL,
                true, // 显示图例
                true, // 采用标准生成器
                false);// 是否生成超链接

        CategoryPlot mPlot = (CategoryPlot)mChart.getPlot();
        mPlot.setBackgroundPaint(Color.LIGHT_GRAY);
        mPlot.setRangeGridlinePaint(Color.BLUE);//背景底部横虚线
        mPlot.setOutlinePaint(Color.RED);//边界线

        ChartFrame mChartFrame = new ChartFrame("公司年度报表", mChart);
        mChartFrame.pack();
        mChartFrame.setVisible(true);
    }

    private CategoryDataset GetDatasetYear() {
        HashMap<String,String> yearMap = new HashMap<>();
        MoneyTools moneyTools = new MoneyTools();
        List<Money> moneyList = moneyTools.moneyData();
        for(Money money:moneyList){
            Calendar calendar = Calendar.getInstance();
            calendar.setTime(money.getMoneyTime());
            double moneyDetail = Double.parseDouble(money.getMoneyDetail().replace("+",""));
            yearMap.put(String.valueOf(calendar.get(Calendar.YEAR)),
                    String.valueOf(Double.parseDouble(yearMap.getOrDefault(String.valueOf(calendar.get(Calendar.YEAR)),"0"))+moneyDetail));
        }
        DefaultCategoryDataset mDataset = new DefaultCategoryDataset();
        var yearArray = yearMap.keySet().toArray();
        Arrays.sort(yearArray);
        for (Object key:yearArray){
            mDataset.addValue(Double.parseDouble(yearMap.get((String) key)),"year", (String) key);
        }
        return mDataset;
    }


    public void CloseFrame() {
        super.dispose();
    }

    @Override
    public void itemStateChanged(ItemEvent e) {
        if (noneButton.isSelected())
            searchType = "none";
        if (dayButton.isSelected())
            searchType = "day";
        if (monthButton.isSelected())
            searchType = "month";
        if (yearButton.isSelected())
            searchType = "year";
    }
}
