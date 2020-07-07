# Questions

## What is pneumonoultramicroscopicsilicovolcanoconiosis?

Pneumonoultramicroscopicsilicovolcanoconiosis is another name for the lung disease silicosis. It is also recogocnised as the longest word in the English language.

## According to its man page, what does `getrusage` do?

'getrusage' returns statistical reports on resouces used by different operations/functions of a program e.g. A process in it's entirety, all subprocesses (descendants) or a thread in it's entirety.
Resources include: time (both user and CPU), and memory usage by different parts of aforementioned operations/functions.

## Per that same man page, how many members are in a variable of type `struct rusage`?

16

## Why do you think we pass `before` and `after` by reference (instead of by value) to `calculate`, even though we're not changing their contents?

It is more memory/space efficient to pass the actual structs. Passing by value would cause the function to create a copy of the rusage struct which uses unnecessary space on the stack (particularly so because the 'rusage' structs are relatively large).

## Explain as precisely as possible, in a paragraph or more, how `main` goes about reading words from a file. In other words, convince us that you indeed understand how that function's `for` loop works.

Using a 'for loop', the main function reads each char from a file sequentially from the beginning until it reaches the EOF. The loop tests the char against the necessary criteria for it to exist as part of a word. In this instance, the loop checks whether the char is either alphabetical or an apostrophe (it discounts apostrophe's occurring as the first letter of a string). If it meets the criteria the char is assigned to the n'th position of the array 'word' and n (index) is incremented.
After the char is appended, 'word' is checked to ensure it hasn't exceeded the maximum length of a word (45 chars). If it has exceeded 45, the current string and its remainder is discounted. Assuming the char hasn't qualified thus far, the loop then checks that it is not a number. If it is, it's discounted.
If the char still hasn't met the criteria to exist in a word, the program concludes that it must have encountered either a 'white-space character' or some other form of punctuation. The word is then terminated via '\0' and then the array is passed into the 'check' function to test it's correctness. If the word has been misspelled, the user is informed and then the loop starts over for the next word.

## Why do you think we used `fgetc` to read each word's characters one at a time rather than use `fscanf` with a format string like `"%s"` to read whole words at a time? Put another way, what problems might arise by relying on `fscanf` alone?

Fscanf would attempt to assign a string of whatever length into the array 'word'. Word has a fixed size so if the read string exceeds this it could lead to a segmentation fault. In addition to this, fgetc allows us to easily keep track of how many characters have been read.
Ultimately, if entire strings were read in via fscanf, each element would need to be analysed anyway so it's not that much more costly to read in each character individually.


## Why do you think we declared the parameters for `check` and `load` as `const` (which means "constant")?

Declaring const char * (as opposed to char *) is a safe move. It ensures that the actual value(s) passed in to the check and load functions cannot be altered over the course of their operation. This is important because it could affect the functions output value and could ultimately cause the program to malfunction or misperform.
