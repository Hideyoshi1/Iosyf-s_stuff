package ca.vanzeben.game;

import java.awt.BorderLayout;
import java.awt.Canvas;
import java.awt.Dimension;

import javax.swing.JFrame;

public class Game extends Canvas implements Runnable{

	private static final long serialVersionUID = 1L;

	public static final int WIDTH = 160;
	public static final int HEIGHT = WIDTH/12*9;
	public static final int SCALE =3;
	public static final String NAME = "TUES THE GAME";
	
	private JFrame frame;
	
	public boolean running = false;
	
	public Game(){
		setMinimumSize(new Dimension(WIDTH*SCALE,HEIGHT*SCALE));
		setMaximumSize(new Dimension(WIDTH*SCALE,HEIGHT*SCALE));
		setPreferredSize(new Dimension(WIDTH*SCALE,HEIGHT*SCALE));
		
		frame=new JFrame (NAME);
		
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setLayout(new BorderLayout());
		
		frame.add(this, BorderLayout.CENTER);
		frame.pack();
		
		frame.setResizable(false);
		frame.setLocationRelativeTo(null);
		frame.setVisible(true);
	}
	
	public synchronized void start() {
		running =true;
		new Thread(this).start();
	}
	
	public synchronized void stop() {
		running = false;
	}
	
	public void run() {
		long lastTime=System.nanoTime();
		double nsPerTick=1000000000D/60D;
		
		int frames = 0;
		int ticks = 0;
		
		long lastTimer = System.currentTimeMillis();
		double delta =0;
		
		while(running)
		{
			long now = System.nanoTime();
			delta +=(now - lastTime)/nsPerTick;
			lastTime=now;
			
			while(delta>=1){
				ticks++;
				tick();
				delta-=1;
			}
			frames++;
			render();
			if (System.currentTimeMillis() - lastTimer >= 1000){
				lastTimer += 1000;
				System.out.println(frames+","+ticks);
				frames=0;
				ticks=0;
			}
		}
	}
	
	public void tick(){
		
	}
	
	public void render(){
		
	}
	
	public static void main(String[] args){
		new Game().start();
	}
	
}
