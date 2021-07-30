package lab3.database.course.frame;

import javax.swing.*;
import java.awt.*;

public class Gif_CompanyFrame extends JFrame implements Runnable {
    public Gif_CompanyFrame() {
        setUndecorated(true);
        setResizable(false);
        setSize(520, 402);
        JLabel gif_Label = new JLabel(new ImageIcon("image/FINAL FANTASY.gif"));
//		JLabel gif_Label = new JLabel(new ImageIcon("image/GoodLibrarian.gif"));
        getContentPane().add(gif_Label, BorderLayout.CENTER);
    }


    public void run() {
        Gif_CompanyFrame frame = new Gif_CompanyFrame();
        frame.setVisible(true);
        try {
            Thread.sleep(4200);
        } catch (InterruptedException e) {

            e.printStackTrace();
        } // 睡4200 (即4.2秒)
        frame.setVisible(false);// 隐藏了.
        // 以下那句是响应关闭的,如果在期间不用到关窗口,不用这句也行的.
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.dispose();
        Login_CompanyFrame login_companyFrame = new Login_CompanyFrame();
        login_companyFrame.setVisible(true);

    }
}
