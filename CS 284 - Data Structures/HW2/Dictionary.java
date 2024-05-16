package CS284Homework;
// Yash Yagnik
// I pledge my honor that I have abided by the Stevens Honor System.


import java.util.ArrayList;
import java.util.InputMismatchException;
import java.util.Scanner;
import java.io.File;
import java.io.FileNotFoundException;

public class Dictionary {

    ArrayList<DictionaryItem> dictArrayList = new ArrayList<DictionaryItem>();
    ArrayList<String> wordList = new ArrayList<String>();
    // Constructor that initializes both arraylists and calls read file with ionDictionary.txt
    public Dictionary(){
        System.out.println("Welcome to the Ion Dictionary! This dictionary is created from the book Ion by Plato!");
        ArrayList<DictionaryItem> dictArrayList = new ArrayList<DictionaryItem>(1300);
        ArrayList<String> wordList = new ArrayList<String>(1300);
        readFile("ionDictionary.txt");
    }

    // Constructor that initializes both arraylists and calls read file with file being an input by the user
    public Dictionary(String fileName){
        System.out.println("Welcome to the Ion Dictionary! This dictionary is created from the book Ion by Plato!");
        ArrayList<DictionaryItem> dictArrayList = new ArrayList<DictionaryItem>(1300);
        ArrayList<String> wordList = new ArrayList<String>(1300);
        readFile(fileName);
    }

    // Reads the file that is inputted and sends each line in the file to split store line
    public void readFile(String fileName){
        File userFile = new File(fileName);
        try {
            if (userFile.exists()) {
                Scanner read = new Scanner(userFile);
                read.nextLine();
                read.nextLine();
                read.nextLine();
                while (read.hasNextLine()) {
                    String data = read.nextLine();
                    splitStoreLine(read);
                }
                read.close();
            }
            printMenu();

        }

        catch (FileNotFoundException e) {
            System.out.println("File was not found, please make sure it is available");
            throw new RuntimeException();
        }

    }

    // Gets rid of all the white spaces in the formatting of the dictionary and then adds the word and count to their respective arraylists splitting them at "|"
    public void splitStoreLine(Scanner scan) {
        while (scan.hasNextLine()) {
            String line = scan.nextLine();
            String[] item = line.split("\\|");
            item[0] = item[0].trim();
            item[1] = item[1].trim();
            int count = Integer.parseInt(item[1]);
            dictArrayList.add(new DictionaryItem(item[0], count));
            wordList.add(item[0]);
        }
    }
    // Prints all the words in the dictionary
    public void printDictionary() {
        System.out.println("All the words mentioned in the Ion book!\nWords\n-----");
        for (String x: wordList) {
            System.out.println(x);
        }
    }

    // Returns the count of the word that the user inputs
    public int searchDictionary(String userWord){
        int index = binarySearch(userWord, 0, wordList.size()-1);
        if (index != -1){
            return dictArrayList.get(index).getCount();
        }
        else {
            System.out.println("The word '" + userWord + "' does not exist in the Ion dictionary!");
            return 0;
        }
    }

    // Returns the index that the user's word is at by cutting the arraylist wordlist in half every iteration
    public int binarySearch(String word, int low, int high) {

        while (low <= high) {
            int mid = low  + ((high - low) / 2);
            String cur_word = wordList.get(mid);
            if (word.compareTo(wordList.get(mid)) > 0 ) {
                low = mid + 1;
            }
            else if (word.compareTo(wordList.get(mid)) < 0) {
                high = mid - 1;
            }
            else {
                return mid;
            }
        }
        return -1;
    }

    // Prints the menu and asks the user for their action choice> It will return an "error" if the input is not a number
    public void printMenu() {
        Scanner userObj = new Scanner(System.in);
        boolean x = true;
        int userChoice = 0;
        while (x) {
            System.out.println("Please choose one of the following menu items indicated with 1-3\n"
                    + "1: To print all the words in the dictionary, choose 1\n"
                    + "2: To search a word in the dictionary, choose 2\n"
                    + "3: To quit the program, choose 3");
            try {
                userChoice = Integer.parseInt(userObj.nextLine());
            }
            catch (IllegalArgumentException e){
                System.out.println("ERROR! Please enter a number.");
                continue;
            }
            x = processMenuItem(userChoice, userObj);
        }
    }

    // Returns true for every input other than 1,2 and any other number. 3 ends the loop exiting the program. Depending on the number different methods are called
    public boolean processMenuItem(int menuitem, Scanner scan) {
        Scanner userObj = new Scanner(System.in);
        if (menuitem == 1) {
            printDictionary();
            return true;
        }
        else if (menuitem == 2) {
            System.out.println("Please enter the word you would like to search:");
            //String userWord = scan.nextLine();
            String userWord2 = scan.nextLine();
            int CountOfWord = searchDictionary(userWord2);
            if (CountOfWord != 0){
                System.out.println("The word '" + userWord2 + "' occurred " + searchDictionary(userWord2) + " times in the book!");
                return true;
            }
            else{
                return true;
            }
        }
        else if (menuitem == 3){
            System.out.println("Thanks for using Ion Dictionary! Bye!");
            return false;
        }

        else{
            System.out.println("ERROR! Please enter a number between 1 and 3.");
            return true;
        }
    }

}





