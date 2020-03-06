package bt.ai;

import bt.Board;
import bt.Droid;

import java.util.Random;

public class Flee extends Routine {

    private static Random random = new Random();
    private final Board board;
    public MoveTo moveTo;	// Making this public so we can see where it is supposed to be going.

    @Override
    public void start() {
        super.start();
        this.moveTo.start();
    }

    public void reset() {
        this.moveTo = new MoveTo(random.nextInt(board.getWidth())+1, random.nextInt(board.getHeight())+1);
    }

    public Flee(Board board) {
        super();
        this.board = board;
        this.moveTo = new MoveTo(random.nextInt(board.getWidth())+1, random.nextInt(board.getHeight())+1);
    }

    @Override
    public void act(Droid droid, Board board) {
        if (!moveTo.isRunning()) {
            return;
        }
        this.moveTo.act(droid, board);
        if (this.moveTo.isSuccess()) {
            succeed();
        } else if (this.moveTo.isFailure()) {
            fail();
        }
    }
}
