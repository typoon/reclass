import java.io.FileInputStream;
import java.io.FileNotFoundException;

public class ReadFile {
	static public void main(String [] args) {
		try {
			FileInputStream fis = new FileInputStream("file.txt");
		} catch (FileNotFoundException fnfe) {
			System.out.println("File not found");
		} catch (Exception e) {
			System.out.println("Other exception occured");
		}
	}
}
