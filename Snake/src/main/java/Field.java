import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.util.Random;

public class Field extends JPanel implements ActionListener {
    private final int SIZE = 432;
    private final int DOT_SIZE = 16;
    private final int ALL_DOTS = 512;
    private Image dot;
    private Image dotHeadRight;
    private Image dotHeadLeft;
    private Image dotHeadUp;
    private Image dotHeadDown;

    private Image apple;
    private Image sand;
    private Image snakeDead;

    private int appleX;
    private int appleY;
    private int[] x = new int[ALL_DOTS - 1];
    private int[] y = new int[ALL_DOTS - 1];
    private int dots;
    private Timer timer;
    private boolean left = false;
    private boolean right = true;
    private boolean up = false;
    private boolean down = false;
    private boolean inGame = true;

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        if (inGame) {
            g.drawImage(sand, 0, 0, null);
            g.drawImage(apple, appleX, appleY, this);
            for (int i = 0; i < dots; i++) {
                g.drawImage(dot, x[i], y[i], this);
                if (right) {
                    g.drawImage(dotHeadRight, x[0], y[0], this);
                }
                if (left) {
                    g.drawImage(dotHeadLeft, x[0], y[0], this);
                    ;
                }
                if (up) {
                    g.drawImage(dotHeadUp, x[0], y[0], this);
                    ;
                }
                if (down) {
                    g.drawImage(dotHeadDown, x[0], y[0], this);
                    ;
                }
            }
        } else {
            String s = "Game Over";
            Font f = new Font("Ozymandias", Font.ITALIC, 30);
            g.setColor(Color.red);
            g.setFont(f);
            g.drawImage(snakeDead, 0, 0, null);
            g.drawString(s, 140, 140);
        }
    }

    public Field() {
        setBackground(Color.black);
        loadImages();
        initGame();
        addKeyListener(new FieldKeyListener());
        setFocusable(true);
    }

    public void initGame() {
        dots = 3;
        for (int i = 0; i < dots; i++) {
            x[i] = 48 - i * DOT_SIZE;
            y[i] = 48;
        }
        timer = new Timer(100, this);
        timer.start();
        createApple();
    }

    public void createApple() {
        appleX = new Random().nextInt(20) * DOT_SIZE;
        appleY = new Random().nextInt(20) * DOT_SIZE;
    }

    public void loadImages() {
        ImageIcon iia = new ImageIcon("apple.png");
        apple = iia.getImage();
        ImageIcon iidhr = new ImageIcon("dotheadright.png");
        dotHeadRight = iidhr.getImage();
        ImageIcon iidhl = new ImageIcon("dotheadleft.png");
        dotHeadLeft = iidhl.getImage();
        ImageIcon iidhu = new ImageIcon("dotheadup.png");
        dotHeadUp = iidhu.getImage();
        ImageIcon iidhd = new ImageIcon("dotheaddown.png");
        dotHeadDown = iidhd.getImage();
        ImageIcon iid = new ImageIcon("dot.png");
        dot = iid.getImage();
        ImageIcon iis = new ImageIcon("sand.png");
        sand = iis.getImage();
        ImageIcon iisd = new ImageIcon("snakedead.png");
        snakeDead = iisd.getImage();
    }

    public void move() {
        for (int i = dots; i > 0; i--) {
            x[i] = x[i - 1];
            y[i] = y[i - 1];
        }
        if (left) {
            x[0] -= DOT_SIZE;
        }
        if (right) {
            x[0] += DOT_SIZE;
        }
        if (up) {
            y[0] -= DOT_SIZE;
        }
        if (down) {
            y[0] += DOT_SIZE;
        }
    }

    public void checkApple() {
        if (x[0] == appleX && y[0] == appleY) {
            dots++;
            createApple();
        }
    }

    public void checkCollisions() {
        for (int i = dots; i > 0; i--) {
            if (i > 4 && x[0] == x[i] && y[0] == y[i]) {
                inGame = false;
            }
        }
        if (x[0] > SIZE) {
            inGame = false;
        }
        if (x[0] < 0) {
            inGame = false;
        }
        if (y[0] > SIZE) {
            inGame = false;
        }
        if (y[0] < 0) {
            inGame = false;
        }
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        if (inGame) {
            checkApple();
            checkCollisions();
            move();
        }
        repaint();
    }

    class FieldKeyListener extends KeyAdapter {
        @Override
        public void keyPressed(KeyEvent e) {
            super.keyPressed(e);
            int key = e.getKeyCode();
            if (key == KeyEvent.VK_LEFT && !right) {
                left = true;
                up = false;
                down = false;
            }
            if (key == KeyEvent.VK_RIGHT && !left) {
                right = true;
                up = false;
                down = false;
            }
            if (key == KeyEvent.VK_UP && !down) {
                up = true;
                right = false;
                left = false;
            }
            if (key == KeyEvent.VK_DOWN && !up) {
                down = true;
                right = false;
                left = false;
            }
        }
    }
}


