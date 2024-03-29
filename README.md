# Get_next_line42

🔧 C, Makefile </br>
🌍 MacOs

This is a reinterpretation of the fgets() function. Its purpose is to code a function that opens a file, reads a predetermined number (buffer) of characters, and returns the text in the standard output, read from a file descriptor, separated by line breaks. It works with concepts such as the use of data buffers, static variables, file descriptors, as well as double pointer with different use of arrays.

## Use:

🚧 project:<br/>
```
42Libft $ make
```
:shower: Clean Obj files:<br/>
```
42Libft $ make clean
```
:shower: :shower: Clean All (obj files + binary):<br/>
```
42Libft $ make fclean
```
:shower: :shower: 🚧 Clean All + build:<br/>
```
42Libft $ make re
```

<br/>See Makefile<br/>

<h2><b>Main Idea</b></h2>

Here, a simple drawning about the main idea: copy buffer until find a '\n', keeping the residual for the next call.

![gnl_idea](imgs/gnl_idea.png)

<h2><b>Logic</b></h2>

Below, a get_next_line's flowchart - Before final version:
(Note: This diagram is not complete. After reading the file, there is no residue, that is, when EOF is reached, the buffer is still checked by repeating the buffer breaking process if there is '/ n'. This diagram served more for an initial understanding. The final version, below in this document, is more detailed and assertive.)

![gnl_flowchart](imgs/gnl_flowchart.png)

<h2><b>GNL Vars</b></h2>

The get_next_line's variables. 
Note that the bonus part (The part that treats with various files at same time), uses an string''s array, like shows the figure below, called by residual[fd]. Where each position referes to particular FD. 
On the simple get_next_line, the mandatory part, this is a simple string var.(residual).

<b>Var list:</b>

- <b>buff:</b> Read buffer (used on read function, to keep the read part)
- <b>residual:</b> residue buffer (has the same size of buff, and keep the residue of buff, after the buff is append on the line)
- <b>oneline:</b> Flag that indicates that function reach a line

(Note: As the buffer variable is only used within gnl_core, I chose to use a simple pointer, that is, I don't need its reference outside the scope of this function. So, the correct thing in this diagram is just buf and * buf. Like the diagram above, this was only used to understand the data structure.)

![gnl_vars](imgs/gnl_vars.png)

<h2><b>FINAL VERSION</b></h2>

To according with moulinette, i had to split my function, because it had more than 70 lines. So, i've created a "gnl_core", that resumes the main logic of the code. Some functions, had your names changed to seem more useful to understanding.

![gnl_new_flowchart](imgs/gnl_new_flowchart.png)
![gnl_new_flowchart_labels](imgs/gnl_new_flowchart_labels.png)

<h2><b>testers</b></h2>

[42TESTERS-GNL](https://github.com/Mazoise/42TESTERS-GNL)

[42cursus_gnl_tests](https://github.com/mrjvs/42cursus_gnl_tests)

[GNL_Lover](https://github.com/charMstr/GNL_lover)

[Get_Next_Line_Tester](https://github.com/Hellio404/Get_Next_Line_Tester)

[gnl_tester](https://github.com/lgrellie/gnl_tester)

