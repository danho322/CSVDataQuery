Daniel Ho
danho322@gmail.com
8/4/2013
Lumos Labs Coding Challenge

This program is pretty straight forward - parse the arguments and populate the correct variables, read in the csv files, and display the proper output.  The user data is stored in different ways depending on the query type.  If it is the targeted likes query, the user data is stored in a map so that the data can be retrieved by name.  If it is the nearby genders query, the users are stored in vectors depending on their gender so they can be iterated over for distance comparison.  The likes are stored as a map containing vectors containing the names of the users that like that particular thing.  This way for the targeted likes query we only look over the users we need to.  I used Xcode for this project so it can be opened as an Xcode project, with the arguments inputed by editing the scheme.