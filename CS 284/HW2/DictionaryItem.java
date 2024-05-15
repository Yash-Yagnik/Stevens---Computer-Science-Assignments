package CS284Homework;
// Yash Yagnik
// I pledge my honor that I have abided by the Stevens Honor System.

public class DictionaryItem {
    public String word;
    public int count;

    // DictionaryItem constructor initializing the word as a string and teh count as a int both which are inputs from the user
    public DictionaryItem(String word, int count){
        this.word = word;
        this.count = count;
    }

    // Returns the DictionaryItem object word
    public String getWord() {

        return word;
    }

    // Sets the DictionaryItem object word
    public void setWord(String word) {

        this.word = word;
    }

    // Returns the DictionaryItem object count
    public int getCount() {
        return count;
    }

    // Sets the DictionaryItem object count
    public void setCount(int count) {
        this.count = count;
    }
}
