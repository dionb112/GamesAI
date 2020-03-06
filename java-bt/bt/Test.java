package bt;

import bt.ai.Repeat;
import bt.ai.Routine;
import bt.ai.Wander;

public class Test {

    public static void main(String[] args) {
        // Setup
        Board board = new Board(10, 10);

        Droid droid = new Droid("MyDroid", 5, 5, 10, 1, 2);
        board.addDroid(droid);

        Routine routine = new Repeat((new Wander(board)));
        droid.setRoutine(routine);
        System.out.println(droid);
		Repeat repeat = (Repeat)droid.routine;
		Wander wander = (Wander)repeat.routine;
        System.out.println("Move to: " + wander.moveTo.getdestX() + ", " + wander.moveTo.getdestY());

        for (int i = 0; i < 10; i++) {
            droid.update();
            System.out.println(droid);
			board.draw();
        }
    }
}
