package bt;

import bt.ai.Repeat;
import bt.ai.Routine;
import bt.ai.Wander;
import bt.ai.MoveTo;

public class Test2 {

    public static void main(String[] args) {
        // Setup
        Board board = new Board(10, 10);
 
        Droid droid = new Droid("MyDroid", 5, 5, 10, 1, 2);
        board.addDroid(droid);
 
        Routine routine = new Wander(board);
        droid.setRoutine(routine);
        System.out.println(droid);
		Wander wander = (Wander)droid.routine;
        System.out.println("Move to: " + wander.moveTo.getdestX() + ", " + wander.moveTo.getdestY());
 
        for (int i = 0; i < 5; i++) {
            droid.update();
            System.out.println(droid);
			board.draw();
        }
    }
}