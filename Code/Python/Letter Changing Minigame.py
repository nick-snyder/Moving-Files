def get_index(word):

    while True:
        index_num = int(input("Enter an index (-1 to quit): "))
        if index_num > len(word):
            print ("invalid index")
        elif index_num < -1:
            print ("invalid index")
        else: 
            break
        
    return index_num
            
def get_letter():
    
    while True:
        letter = input("What letter would you like to replace it with? ")
        if len(letter) > 1:
            print ("Must be exactly one character!")
        elif letter.isupper():
            print ("Character must be a lowercase letter!")
        else: 
            break
        
    return letter
        
def switch_it_up(word, index_num, letter):
    
    if len(word) == index_num + 1:
        word = word[:index_num] + letter
    else:
        word = word[:index_num] + letter + word[index_num + 1:]
    
    return word
    
if __name__ == '__main__':
    
    word = input("Enter a word: ")
    while True:
        
        index_num = get_index(word)
        if index_num == -1:
            break
        
        letter = get_letter()
        word = switch_it_up(word, index_num, letter)
        print (word)
