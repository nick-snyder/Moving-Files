public class Igpay {
    public static boolean isVowel(String letter) {letter = letter.toLowerCase(); if (letter.equals("a") || letter.equals("e") || letter.equals("i") || letter.equals("o") || letter.equals("u")) return true ; return false;}
    public static String letterAt(String word, int index) {return word.substring(index, index + 1);}
    public static int firstVowel(String word) {for (int i = 0; i < word.length(); i++) if (isVowel(letterAt(word, i))) return i; return -1;}
    public static String translateWord(String word) {if (firstVowel(word) == 0) {if (letterAt(word, word.length()-1).equals("w")) return word += "ay" ; return word += "way";} else {String firstHalf = word.substring(0, firstVowel(word)); String secondHalf = word.substring(firstVowel(word), word.length()); String newWord = secondHalf + firstHalf + "ay"; return newWord.toLowerCase();}}
    public static void main(String[] args) {
        System.out.println(translateWord("Apple"));
    }
}