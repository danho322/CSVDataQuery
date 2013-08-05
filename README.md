Mobile Programming Challenge - Like DB

Objective

You are working on the next hot mobile-social startup and you've been asked to 

answer some questions about the data you've collected in the form of CSV files. Each

CSV file is very large, (a few MB each.)

One of the CSV files has a bunch of user data in it, including a name, phone number, 

gender and current position on a fictional coordinate system for each user. The 

second CSV has a mapping of user names to various things that they like.

The coordinate system is defined to be a rectangle of arbitrary dimensions. You 

should determine the dimensions based on the data in the users.csv.

You want to be able to answer the following questions:

Show me all users within DISTANCE radius of (X, Y) that like LIKE

Let's call this the TARGETED_LIKES query

Get all GENDER users that are within DISTANCE of each other

Call this one the NEARBY_GENDER query

Building

You have a few options for building your code. Whichever method you choose to go 

with, note that we will expect it to work on a fresh install of Xcode/VisualStudio/

linux. So, remember to remove any absolute paths, erroneous library references/

includes/directories, etc...

Xcode project

Visual Studio solution

Makefile or command line for building using g++ 4.0+

Packaging

You may only use what's available in the standard library and don't include source 

code you did not write.

Also, please include a quick paragraph in a README.txt file explaining your solution 

and any extra features you decided to include. 

Zip/tar your solution into a file named FIRSTNAME-LASTNAME.lumos-takehome.zip/tar.

To recap, your solution should at least contain these files: 

README.txt

Makefile

likedb.cpp

users.csv    // We'll also use some of our own CSV files as input

likes.csv

Lastly, we'd like to ask that you do not post this question or your solution online for

others to use.

CSV Files

users.csv

Format: name, phone_number, x, y, gender

e.g.

"Cory Virok", "555-223-2121", 37, 122, "male"

"Alice Cooper", "123-666-0101", 21, 102, "female"

"Bo Jangles", "", 11, 0, "male"

likes.csv

Format: user, like

e.g. 

"Cory Virok", "pizza"

"Alice Cooper", "Lumos Labs"

"Cory Virok", "roller coasters"

"Alice Cooper", "puppies"

Parameters

Your program should take the query descriptor and all necessary parameter values 

on the command line. You can assume the users.csv and likes.csv files are in the 

current directory.

e.g. 

$> ./likedb -q targeted_likes distance=5 x=27 y=127 like="pizza"

Output

All output should go to stdout and should be parseable as CSV data. Any errors that 

occur should go to stderr.

Your program's output will depend on the query descriptor used.

TARGETED_LIKES

Output format: user, phone_number, x, y, gender

$>./likedb -q targeted_likes distance=5 x=27 y=127 like="pizza"

"Cory Virok", "555-223-2121", 37, 122, "male"

"Alice Cooper", "123-666-0101", 21, 102, "female"

NEARBY_GENDER

Output format: user_1, user_2, distance

$>./likedb -q nearby_gender distance=20 gender=male

"Cory Virok", "Nikola Tesla", 19.8

"Steve Jobs", "Cory Virok", 11.9

"Steve Jobs", "Joel Spolsky", 15.0
