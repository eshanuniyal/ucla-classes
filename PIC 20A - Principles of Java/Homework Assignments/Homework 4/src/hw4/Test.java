package hw4;

import java.util.Scanner;
import hw4.CFPlayer;
import hw4.RandomAI;
import hw4.EshanAI;
import hw4.ConsoleCF;
import hw4.GUICF;


public class Test {
    public static void main(String[] args) {

        Scanner reader = new Scanner (System.in);
        int gameMode = reader.nextInt();

        if (gameMode==1) {
            new GUICF(new RandomAI(), new RandomAI());
        } else if (gameMode==2) {
            CFPlayer ai1 = new EshanAI();
            CFPlayer ai2 = new RandomAI();
            int n = 10000;
            int winCount = 0;
            for (int i =0; i < n ; i++) {
                ConsoleCF game = new ConsoleCF(ai1, ai2);
                game.playOut();
                if(game.getWinner() == ai1.getName())
                    winCount++;
            }
            System.out.println(((double) winCount)/n);
        } else {
            ConsoleCF game = new ConsoleCF(new EshanAI());
            game.playOut();
            System.out.println(game.getWinner() + " has won.");
        }
        CFPlayer ai1 = new RandomAI();
        CFPlayer ai2 = new RandomAI();
        int n = 1000;
        int winCount = 0;
        for (int i=0; i<n; i++) {
            ConsoleCF game = new ConsoleCF(ai1, ai2);
            game.playOut();
            String winner = game.getWinner();
            if (winner == ai1.getName()) {
                winCount++;
            }
            System.out.println(winner);
        }
        System.out.println(((double) winCount) / n);
    }
}
