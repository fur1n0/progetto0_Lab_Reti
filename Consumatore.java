package reties0;


	
	import java.io.BufferedReader;
import java.io.FileNotFoundException;
	import java.io.FileReader;
	import java.io.IOException;

	// Consumatore e' un filtro
	public class Consumatore {
		public static void main(String[] args) throws FileNotFoundException {
			FileReader r = null;
			char carattere;
			int x;
			String str;
			BufferedReader in= new BufferedReader(new FileReader(args[1]));
			
		
			if (args.length != 1 && args.length != 2){
				System.out.println("Utilizzo: consumatore <inputFilename>");
				System.exit(0);
			}
		  str = args[0];
			
			try {
				//in= new BufferedReader(new FileReader(args[1]));
				r = new FileReader(args[1]);
				
			} catch(FileNotFoundException e){
				System.out.println("File non trovato");
				System.exit(1);
			}
			
			try {
				
				
				while ((x = r.read()) >= 0) {
					carattere = (char) x;
					if(!str.contains(String.format("%c",carattere)))
						System.out.print(carattere);
				}
				r.close();
			} catch(IOException ex){
				System.out.println("Errore di input");
				System.exit(2);
			}
	}
	}

