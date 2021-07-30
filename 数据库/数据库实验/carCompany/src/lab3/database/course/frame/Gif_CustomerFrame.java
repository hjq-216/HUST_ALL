package lab3.database.course.frame;

import javax.swing.*;
import java.awt.*;

public class Gif_CustomerFrame extends JFrame implements Runnable {
    private static final long serialVersionUID = 1L;
    public Gif_CustomerFrame() {
        setUndecorated(true);
        setResizable(false);
        setSize(529, 527);
//		JLabel gif_Label = new JLabel(new ImageIcon("image/Reader.gif"));
        JLabel gif_Label = new JLabel(new ImageIcon("image/goodReader.gif"));
        getContentPane().add(gif_Label, BorderLayout.CENTER);
    }

    public void run() {
        Gif_CustomerFrame frame = new Gif_CustomerFrame();
        frame.setVisible(true);
        try {
            Thread.sleep(1800);
        } catch (InterruptedException e) {

            e.printStackTrace();
        }// 睡1800 (即1.8秒)
        frame.setVisible(false);// 隐藏了.
        // 以下那句是响应关闭的,如果在期间不用到关窗口,不用这句也行的.
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.dispose();
        Login_CustomerFrame login_customerFrame = new Login_CustomerFrame();
        login_customerFrame.setVisible(true);

    }
}
