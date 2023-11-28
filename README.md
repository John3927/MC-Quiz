### Intro

Hello. This is a simple CLI multiple-choice style reviewer. It takes in a text file location and starts asking you questions.

### Format

Each line in the text file should look like this

```Question=Answer```

Everything before the first = will be the question, everything after will be the answer. For example, if I want to ask about capitals of countries I would have something like
```
China=Beijing

USA=Washington

Russia=Moscow

Norway=Oslo

```

Then the program will ask you to choose the correct capital for some countries.

Make sure you have at least 4 question-answer pairs.

An example text file is included which contains the 50 US states and their capitals.

### Directions

In your terminal do

```(path to exe) (path to text file)```

For example, if the executable is called quiz.exe, the questions file is called text.txt, they are in the same folder, and my current directory is in that folder, then I will do (on windows)

```.\quiz.exe .\text.txt```

#### Commands

Commands are the digits 0 to 9, q, and p. 

0-9 answers a question.  
  q quits the program  
  p prints out all the questions-answers pairs

Entering multiple characters will result in the program reading them as separate commands in succession, which might cause unintended behaviors.

Remember, you can always ctrl-c to terminate the program.
