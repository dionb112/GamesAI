package bt;

import java.util.ArrayList;
import java.util.List;

public class Board {

    final int width;
    final int height;

    private List<Droid> droids = new ArrayList<Droid>();

    public Board(int width, int height) {
        this.width = width;
        this.height = height;
    }

    public int getWidth() {
        return width;
    }

    public int getHeight() {
        return height;
    }

    public void addDroid(Droid droid) {
        if (isTileWalkable(droid.getX(), droid.getY())) {
            droids.add(droid);
            droid.setBoard(this);
        }
    }

    public boolean isTileWalkable(int x, int y) {
        for (Droid droid : droids) {
            if (droid.getX() == x && droid.getY() == y) {
                return false;
            }
        }
        return true;
    }

    public List<Droid> getDroids() {
        return droids;
    }
    public void draw() 
	{
		boolean occupied = false;
		int d = 0;

        System.out.print("   ");
		for (int t = 1; t <= width; t++)
		{
			System.out.print(" " + t);				
		}
        System.out.println();

        for (int h = 1; h <= height; h++)
		{
			if (h > 9) System.out.print(h + " ");
			else System.out.print(h + "  ");
		
			for (int w = 1; w <= width; w++)
			{
				occupied = false;
				
				if (w > 9) System.out.print(" ");
					
				for (Droid droid : droids) 
				{
					if (droid.getX() == w && droid.getY() == h) 
					{
						d++;
						System.out.print(" " + d);
						occupied = true;
					}
				}
				if (occupied == false)
					System.out.print(" _");
			}
			System.out.println();
		}
		System.out.println();

    }
}
