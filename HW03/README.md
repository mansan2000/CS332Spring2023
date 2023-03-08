## Run instructions
- To compile this program navigate to the directory that the HW03.c file is in and run make.
- Once compiled you can run the program by typing in ./hw02 and then whatever args you want to pass in. 
- Note that if you want to pass in a path to another directory to run this script on then it needs to be the first argument 
passed in. e.g. "./hw02 ../hw01 -S -e "ls -l""

## Testing
- I tested this code for all the flags in the instructions and the different combinations for them. I tested it on the projects folder
given in the instructions and also on multiple local directories. It worked for every case I could find including symbolic links. 
- For HW03 I added the -e flag and tested it with any command that could be executed with the filename as the last parameter to execvp

## Design
- I wrote my code in a dynamic way where I did not hardcode my conditional statements for each flag and it is easy for flags to be 
added or removed. This way was a bit more complex than just some hardcoded conditional statements with all possibilities accounted for
but this way it does not get exponentially more complex as you add more cases. 
- This dynamic way helped this code be really easy to modify for HW03 and adding the -e flag. I only had to add a few lines 
of code to handle the flag along with the forking function. 
