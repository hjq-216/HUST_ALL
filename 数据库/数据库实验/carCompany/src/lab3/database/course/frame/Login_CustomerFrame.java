package lab3.database.course.frame;

import javax.swing.*;
import javax.swing.border.EmptyBorder;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class Login_CustomerFrame extends JFrame {
    private static final long serialVersionUID = 1L;
    private JPanel contentPane;

    /*	*//**
     * Launch the application.
     */
/*	public static void main(String[] args) {
		try {
			Login_ReaderFrame frame = new Login_ReaderFrame();
			frame.setVisible(true);
		} catch (Exception e) {
			e.printStackTrace();
		}
	}*/

    /**
     * Create the frame.
     */
    public Login_CustomerFrame() {
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

        JLabel background1 = new JLabel(new ImageIcon("image/background2.jpg"));
        background1.setBounds(0, 0, 990, 659);
        contentPane.add(background1);
    }

    public void CloseFrame() {
        super.dispose();
    }
}
