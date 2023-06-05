# CN3
## Project Description
In this project we implement DVRP and LSRP routing algorithms with CPP and compared them. 
 
## How It Works?
You can compile oroject using `g++ CA3.cpp` and after that, run project using `.\a.out` <br> 
The main function get commands from user while user enters `exit`command. <br>
The list of all commands explained in project description file.<br> 
for simplicity in wokring, you can add your commands in `inputs.txt` file then run project.<br>

## Code Explanation
At first we read commands line by line from `inputs.txt` file and parse the input command in `processInput` function.<br>
if command matches with any of valid commands, the code of that part will run and otherwise the input ignores.<br>
We defined a global variable called `graph` with maximum size of `graphSize` to store netrwork topology and execute algorithms .<br>
This variable has type of `Node` which includes and `id:int` and `neighbors:vector<Edge>` and `Edge` type includes an int variable to store cost and another int variable to sotre neigbor id.<br>
the code of every command (in processInput function) explained below:
### `set-max int:number`
We add this command at the first of inputs file to declare maximum number of graph nodes.<br>
this part will re-allocate graph variable size to input number size and assigns the numbers respectively as graph Ids. 
### `topology <i1:int-i2:int-i3:input>+`
when this command calls, a bi-directional edge between i1-i2 nodes with i3 cost adds. this happens with calling `addEdge` method and adds on `graph` variable. <br>
if inputs were wrong the `wrong input` error shows.<br>
we added this topology as an input example <br>
![i1](https://github.com/Mohammadreza6pari/CN/assets/94805623/9a21f902-95e4-4046-a49e-d8fc1d5ac17f)

### `show`
this command prints adjancy matrix with calling same name method.as the name suggests, this method makes adjancy matrix and prints that.<br>
the output for mentioned example shown below<br>
![i2](https://github.com/Mohammadreza6pari/CN/assets/94805623/8101febf-8b11-4a9b-9dca-a36beb77ddc6)

### `remove <i1:int-i2:int>`
this command uses for removing an edge between two nodes. the method checks the path between two node exist or not, if exist deletes that.<br>
the metioned network after removing network 0-4 edge shown below.<br>
![i3](https://github.com/Mohammadreza6pari/CN/assets/94805623/fc0cd42b-4e51-436c-86bc-bdf85ec7f179)
 
 ### `modify <i1:int-i2:int-cost:int>`
 this command adds an edge between i1-i2 nodes and in error checking checks the input edges don't be the same too.<br>
 
 ### `lsrp source(optional):int`
this command executes lsrp algorithm on graph network and prints the cost in each step between source and all other nodes<br>
if the command executes without argument, this will runs lsrp for all nodes as source<br>
the printed value (just two last steps) for that graoh for source=1 shown below<br>
![i4](https://github.com/Mohammadreza6pari/CN/assets/94805623/fb66b2f1-835d-41a0-9c74-ffc96008898e)

### `dvrp <source(optional):int>`
this command executes dvrp algorithm on graph network and prints the distance,shortest path and next hop from source to all other nodes<br>
the printed value for mentioned network for source=1 shown below<br>
![i4](https://github.com/Mohammadreza6pari/CN/assets/94805623/9a840ce2-1407-45f1-9985-a89d03c3ef5a)

## Result Compares


