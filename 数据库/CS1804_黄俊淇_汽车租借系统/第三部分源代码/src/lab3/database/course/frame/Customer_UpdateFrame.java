package lab3.database.course.frame;

import lab3.database.course.dao.Customer;
import lab3.database.course.sqltools.CustomerTools;

import javax.swing.*;
import javax.swing.border.EmptyBorder;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class Customer_UpdateFrame extends JFrame {
    private static final long serialVersionUID = 1L;
    private JPanel contentPane;


    private JTextField nameCustomertextField;
    private JTextField passwordtextField;

    private JLabel idCustomer_showLable;
    private JLabel idCustomerLabel;
    private JLabel nameCustomerLabel;
    private JLabel passwordLabel;

    private JButton updateButton;

    public Customer_UpdateFrame(All_CustomerFrame all_customerFrame)
    {
        setResizable(false);
        setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        setBounds(100, 100, 996, 699);
        contentPane = new JPanel();
        contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
        setContentPane(contentPane);
        contentPane.setLayout(null);

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

        idCustomer_showLable = new JLabel();
        idCustomer_showLable.setFont(new Font("宋体", Font.PLAIN, 30));
        idCustomer_showLable.setForeground(Color.WHITE);
        idCustomer_showLable.setBounds(640, 180, 156, 38);
        contentPane.add(idCustomer_showLable);
        idCustomer_showLable.setText(all_customerFrame.customerJtable.getValueAt(all_customerFrame.row,0).toString());

        nameCustomertextField = new JTextField();
        nameCustomertextField.setFont(new Font("宋体", Font.PLAIN, 30));
        nameCustomertextField.setBounds(640, 320, 137, 47);
        contentPane.add(nameCustomertextField);
        nameCustomertextField.setColumns(10);
        nameCustomertextField.setText(all_customerFrame.customerJtable.getValueAt(all_customerFrame.row, 1).toString());

        passwordtextField = new JTextField();
        passwordtextField.setFont(new Font("宋体", Font.PLAIN, 30));
        passwordtextField.setBounds(640, 463, 139, 47);
        contentPane.add(passwordtextField);
        passwordtextField.setColumns(10);
        passwordtextField.setText(all_customerFrame.customerJtable.getValueAt(all_customerFrame.row,2).toString());

        updateButton = new JButton(new ImageIcon("image/update.jpg"));
        updateButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                do_UpdateButton_UpdateCustomer();
            }
        });
        updateButton.setBounds(555, 545, 106, 47);
        contentPane.add(updateButton);

        JLabel background1 = new JLabel(new ImageIcon("image/updateReaderbackground.jpg"));
        background1.setBounds(0, 0, 990, 659);
        contentPane.add(background1);
    }

    protected void do_UpdateButton_UpdateCustomer() {

        CustomerTools customerTools = new CustomerTools();
        Customer customer = new Customer();

        if (idCustomer_showLable.getText() != null && !"".equals(idCustomer_showLable.getText())
                && nameCustomertextField.getText() != null && !"".equals(nameCustomertextField.getText())
                && passwordtextField.getText() != null && !"".equals(passwordtextField.getText())) {
            customer.setUserID(idCustomer_showLable.getText());
            customer.setUsername(nameCustomertextField.getText());
            customer.setUserPassword(passwordtextField.getText());
            int i = customerTools.UpdateCustomer(customer);
            if (i == 1) {
                JOptionPane.showMessageDialog(getContentPane(), "成功更新客户信息！", "", JOptionPane.WARNING_MESSAGE);
                return;
            } else {
                JOptionPane.showMessageDialog(getContentPane(), "更新客户信息失败！", "", JOptionPane.WARNING_MESSAGE);
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
