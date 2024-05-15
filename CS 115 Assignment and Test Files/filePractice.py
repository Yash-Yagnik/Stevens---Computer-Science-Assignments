# File I/O
#age = input("What is your age?")
#open(filename, mode)


def write_file(string, filename):
    myfile = open(filename, "w")
    myfile.write(string)
    myfile.close()
    

def read_file(filename):
    myfile = open(filename, "r")
    contents = myfile.read()
    myfile.close()
    return contents

def read_file_v2(filename):
    with open(filename, "r") as myfile:
        return myfile.read()

def read_file_v3(filename):
    with open(filename, "r") as f:
        return myfile.readlines()

def read_file_v4(filename):
    with open(filename, "r") as f:
        for line in f:
            print(line.strip())

def read_preferences(filename):
    dictionary = {}
    with open(filename, "r") as f:
        for line in f:
            [username, artists] = line.strip().split(":")
            atristList = artists.split(",")
            dictionary[username] = artistList
    return dictonary

write_file("Welcome to CS115 by Yash Yagnik\nHello All\nHoware you?", "text1.txt")
#read_file_v4("text.txt")
#print(read_preferences("recsys.txt"))
