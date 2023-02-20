## Run instructions
- To compile this program navigate to the directory that the HW02.c file is in and run make.
- Once compiled you can run the program by typing in ./hw02 and then whatever args you want to pass in. 

## Testing
- I tested this code for all the flags in the instructions and the different combinations for them. I tested it on the projects folder
given in the instructions and also on multiple local directories. It worked for every case I could find including symbolic links. 

## Design
- I wrote my code in a dynamic way where I did not hardcode my conditional statements for each flag and it is easy for flags to be 
added or removed. This way was a bit more complex than just some hardcoded conditional statements with all possibilities accounted for
but this way it does not get exponentially more complex as you add more cases. 

## Bonus
- I did the symbolic links bonus
- I did the function pointer bonus
- I did the -t bonus