package lab3.database.course.frame;

import lab3.database.course.dao.Car;
import lab3.database.course.sqltools.CarTools;

import javax.swing.*;
import javax.swing.border.EmptyBorder;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class Car_UpdateFrame extends JFrame {
    private static final long serialVersionUID = 1L;
    private JPanel contentPane;

    private JTextField nameCartextField;
    private JTextField priceField;
    private JTextField backtextField;

    private JLabel idCar_showLabel;
    private JLabel nameCarLabel;
    private JLabel priceLabel;
    private JLabel backLabel;
    private JButton updateButton;

    public Car_UpdateFrame(All_CarFrame all_carFrame)
    {
        setResizable(false);
        this.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        setBounds(100, 100, 608, 743);
        contentPane = new JPanel();
        contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
        setContentPane(contentPane);
        contentPane.setLayout(null);

        idCar_showLabel = new JLabel("车辆编号");
        idCar_showLabel.setForeground(Color.WHITE);
        idCar_showLabel.setFont(new Font("宋体", Font.PLAIN, 30));
        idCar_showLabel.setBounds(137, 111, 137, 39);
        contentPane.add(idCar_showLabel);

        nameCarLabel = new JLabel("车名");
        nameCarLabel.setForeground(Color.WHITE);
        nameCarLabel.setFont(new Font("宋体", Font.PLAIN, 30));
        nameCarLabel.setBounds(137, 190, 103, 39);
        contentPane.add(nameCarLabel);

        priceLabel = new JLabel("押金");
        priceLabel.setForeground(Color.WHITE);
        priceLabel.setFont(new Font("宋体", Font.PLAIN, 30));
        priceLabel.setBounds(137, 256, 81, 39);
        contentPane.add(priceLabel);

        backLabel = new JLabel("租金");
        backLabel.setForeground(Color.WHITE);
        backLabel.setFont(new Font("宋体", Font.PLAIN, 30));
        backLabel.setBounds(137, 335, 81, 39);
        contentPane.add(backLabel);


        idCar_showLabel = new JLabel();
        idCar_showLabel.setFont(new Font("宋体", Font.PLAIN, 20));
        idCar_showLabel.setForeground(Color.WHITE);
        idCar_showLabel.setBounds(307, 112, 117, 37);
        contentPane.add(idCar_showLabel);
        idCar_showLabel.setText(all_carFrame.carJtable.getValueAt(all_carFrame.row, 0).toString());

        nameCartextField = new JTextField();
        nameCartextField.setFont(new Font("宋体", Font.PLAIN, 20));
        nameCartextField.setBounds(307, 191, 113, 37);
        contentPane.add(nameCartextField);
        nameCartextField.setColumns(10);
        nameCartextField.setText(all_carFrame.carJtable.getValueAt(all_carFrame.row, 1).toString());

        priceField = new JTextField();
        priceField.setFont(new Font("宋体", Font.PLAIN, 20));
        priceField.setBounds(307, 256, 117, 39);
        contentPane.add(priceField);
        priceField.setColumns(10);
        priceField.setText(all_carFrame.carJtable.getValueAt(all_carFrame.row, 2).toString());

        backtextField = new JTextField();
        backtextField.setFont(new Font("宋体", Font.PLAIN, 20));
        backtextField.setBounds(307, 336, 117, 37);
        contentPane.add(backtextField);
        backtextField.setColumns(10);
        backtextField.setText(all_carFrame.carJtable.getValueAt(all_carFrame.row, 3).toString());

        updateButton = new JButton(new ImageIcon("image/update.jpg"));
        updateButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                do_updateButton_UpdateCar();
            }
        });
        updateButton.setBounds(209, 602, 106, 37);
        contentPane.add(updateButton);

        JLabel background = new JLabel(new ImageIcon("image/updatebackground.jpg"));
        background.setBounds(0, 0, 602, 703);
        contentPane.add(background);
    }

    protected void do_updateButton_UpdateCar() {

        CarTools carTools = new CarTools();
        Car car = new Car();

        if (idCar_showLabel.getText() != null && !"".equals(idCar_showLabel.getText())
                && nameCartextField.getText() != null && !"".equals(nameCartextField.getText())
                && priceField.getText() != null && !"".equals(priceField.getText()) && backtextField.getText() != null
                && !"".equals(backtextField.getText()) ) {
            car.setCarID(idCar_showLabel.getText());
            car.setCarName(nameCartextField.getText());
            car.setCarPrice(priceField.getText());
            car.setBorrowPrice(backtextField.getText());
            int i = carTools.UpdateCar(car);
            if (i == 1) {
                JOptionPane.showMessageDialog(getContentPane(), "成功更新车辆信息！", "", JOptionPane.WARNING_MESSAGE);
                return;
            } else {
                JOptionPane.showMessageDialog(getContentPane(), "更新车辆信息失败！", "", JOptionPane.WARNING_MESSAGE);
                return;
            }
        } else {
            JOptionPane.showMessageDialog(getContentPane(), "请输入完整资料", "", JOptionPane.WARNING_MESSAGE);
            return;
        }
    }
    public void CloseFrame(){
        super.dispose();
    }
}
