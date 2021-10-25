import java.util.Scanner;

public class TIcTacToe {
	
	private Player player1 , player2;
	private Board board;
	
	public void startGame() {
		Scanner sc = new Scanner(System.in);
		//players input
		player1 = takePlayerInput(1);
		player2 = takePlayerInput(2);
		while(player1.getSymbol() == player2.getSymbol()) {
			System.out.println("Symbol Already taken!! Pick Another Symbol");
			char symbol = sc.next().charAt(0);
			player2.setSymbol(symbol);
		}
		
		//create board
		board = new Board(player1.getSymbol(),player2.getSymbol());
		
		//conduct the game
		
			/* 1 - player 1 wins
			 * 2 - player 2 wins
			 * 3 - draw
			 * 4 - incomplete
			 * 5 - innvalid
			 */
		
		boolean player1Turn = true;
		int status = Board.INCOMPLETE;
		while(status==Board.INCOMPLETE || status==Board.INVALID) {
			if(player1Turn) {   //player1 turn
				System.out.println("Player 1 - "+player1.getName()+"'s turn");
				System.out.println("Enter x: ");
				int x = sc.nextInt();
				System.out.println("Enter y: ");
				int y = sc.nextInt();
				status = board.move(player1.getSymbol(),x,y);
				if(status != Board.INVALID) {   //if not out of order or not updating symbol in same block
					//correct move
					player1Turn = false;
					board.print();
				}else {
					System.out.println("Invalid move !! try again!!");
				}
				
			}else {				//player2 turn
				System.out.println("Player 2 - "+player2.getName()+"'s turn");
				System.out.println("Enter x: ");
				int x = sc.nextInt();
				System.out.println("Enter y: ");
				int y = sc.nextInt();
				status = board.move(player2.getSymbol(),x,y);
				if(status != Board.INVALID) {	 //if not out of order or not updating symbol in same block
					//correct move
					player1Turn = true;
					board.print();
				}else {
					System.out.println("Invalid move !! try again!!");
				}
			}
		}
		if(status == Board.PLAYER_1_WINS) {
			System.out.println("Player 1 - "+player1.getName()+" wins!!");
		}else System.out.println("Player 2 - "+player2.getName()+" wins!!");
		if(status == Board.DRAW)
			System.out.println("DRAW !!");
	}
	
	private Player takePlayerInput(int num) {
		Scanner sc = new Scanner(System.in);
		System.out.println("Enter PLayer "+num+" name: ");
		String name = sc.nextLine();
		System.out.println("Enter PLayer "+num+" Symbol: ");
		char symbol = sc.next().charAt(0);
		Player p = new Player(name, symbol);
		return p;
	}
	
	public static void main(String[] args) {
		
		TIcTacToe t = new TIcTacToe();
		t.startGame();
	}
}
