package bt;

import java.util.Scanner;
import bt.ai.Routine;
import bt.ai.Routines;

public class Main {

    public static void main(String[] args) {
        Board board = new Board(11, 11);
        Droid droid1 = new Droid("Droid_1", 2, 2, 10, 1, 3);
        Droid droid2 = new Droid("Droid_2", 10, 10, 10, 2, 2);
        Droid droid3 = new Droid("Droid_3", 5, 5, 10, 0, 4);

        board.addDroid(droid1);
        board.addDroid(droid2);
        board.addDroid(droid3);


        Routine brain1 = Routines.sequence(
                Routines.moveTo(5, 10),
                Routines.moveTo(15, 12),
                Routines.moveTo(2, 4)
        );
        droid1.setRoutine(brain1);

        Routine brain2 = Routines.sequence(
            Routines.repeat(Routines.wander(board), 4)
        );
        droid2.setRoutine(brain2);

        Routine brain3 = Routines.sequence(
            Routines.repeat(Routines.flee(board), 8)
        );
        droid3.setRoutine(brain3);

        for (int i = 0; i < 30; i++) {
            System.out.println(droid1.toString());
            System.out.println(droid2.toString());
            System.out.println(droid3.toString());
            droid1.update();
            droid2.update();
            droid3.update();
			board.draw();
			pressAnyKeyToContinue();
        }
    }
	
	 static private void pressAnyKeyToContinue()
 { 
        System.out.println("Press Enter key to continue...");
        try
        {
            System.in.read();
            System.in.read();
        }  
        catch(Exception e)
        {}  
 }
}
