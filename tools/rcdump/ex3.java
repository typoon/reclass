import java.io.*;


public class ex3 {
	public static void main(String[] args) {
        int i = 10;
        BufferedReader br;
        
        try {
            br = new BufferedReader(new FileReader("bla.txt"));

            i+=3;

            for(i = 0; i < 10; i++)
                System.out.println("Oie!" + br.readLine());
        } catch (Exception e) {
        }
		bla();
	}

	public static void bla() {
		System.out.println("Oie do bla!");
	}

    private static String[] doNothing(int a, int b, boolean c, double d[]) {
        return new String[10];
    }
}
