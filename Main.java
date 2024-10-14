import java.io.*;
import java.nio.file.*;

public class Main {
    public static void main(String[] args) {
        String fileName = "test/t3.decaf";
        String srcCode = readFile(fileName);
        
        LexicalAnalyzer lexer = new LexicalAnalyzer(srcCode);
        lexer.printTokens();
    }

    private static String readFile(String fileName) {
        try {
            return new String(Files.readAllBytes(Paths.get(fileName)));
        } catch (IOException e) {
            System.err.println("Error opening \"" + fileName + "\"");
            return "";
        }
    }
}