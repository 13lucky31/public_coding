import javax.swing.*;

public class Window extends JFrame {
    public Window(){
        setTitle("Welcome to the Snake Game");
        setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        setSize(432,457);
        setLocation(512,512);
        add(new Field());
        setVisible(true);
    }

    public static void main(String[] args) {
        Window w = new Window();
    }
}
