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
![1](https://github.com/Mohammad-6pari/RoutingComputerNetworks/assets/122674773/cceef258-cc36-45e4-8672-03614c78b778)

### `show`
this command prints adjancy matrix with calling same name method.as the name suggests, this method makes adjancy matrix and prints that.<br>
the output for mentioned example shown below<br>
![2](https://github.com/Mohammad-6pari/RoutingComputerNetworks/assets/122674773/9c2dffe3-1721-41a7-9f3d-5a1d0a1fe3d8)

### `remove <i1:int-i2:int>`
this command uses for removing an edge between two nodes. the method checks the path between two node exist or not, if exist deletes that.<br>
the metioned network after removing network 0-4 edge shown below.<br>
![3](https://github.com/Mohammad-6pari/RoutingComputerNetworks/assets/122674773/bbfb746f-a3b4-4e78-8873-93b3cf57decd)
 
 ### `modify <i1:int-i2:int-cost:int>`
 this command adds an edge between i1-i2 nodes and in error checking checks the input edges don't be the same too.<br>
 
 ### `lsrp source(optional):int`
this command executes lsrp algorithm on graph network and prints the cost in each step between source and all other nodes<br>
if the command executes without argument, this will runs lsrp for all nodes as source<br>
the printed value (just two last steps) for that graoh for source=1 shown below<br>
![4](https://github.com/Mohammad-6pari/RoutingComputerNetworks/assets/122674773/ec11ec4c-d6b1-4efe-addc-904d6b098f62)

### `dvrp <source(optional):int>`
this command executes dvrp algorithm on graph network and prints the distance,shortest path and next hop from source to all other nodes<br>
the printed value for mentioned network for source=1 shown below<br>
![5](https://github.com/Mohammad-6pari/RoutingComputerNetworks/assets/122674773/50a1c72d-1207-40ba-9e70-00e5b7db8a3c)

## Result Compares
for node with id=1 , LSRP and DVRP algorithms before and after removing 4-10 edge is like as below :

## DVRP (Before Removing)
![6](https://github.com/Mohammad-6pari/RoutingComputerNetworks/assets/122674773/80d0739b-d1a5-47ca-a958-471b23279b1e)
<br>

## DVRP (After Removing)
![7](https://github.com/Mohammad-6pari/RoutingComputerNetworks/assets/122674773/bd4b4d71-281b-4590-b54f-69c6eafeb1f2)

<br>
as we see, after removing link the shortest path cost between 1,4 increases and as we expected, in DVRP the next hop for souce=1 and destination= 4 changes.  

## LSRP (Before Removing)
![8](https://github.com/Mohammad-6pari/RoutingComputerNetworks/assets/122674773/b94cdd47-7f46-46fb-a892-235a8bd6abf0)
<br>

## LSRP (After Removing)
![9](https://github.com/Mohammad-6pari/RoutingComputerNetworks/assets/122674773/0382ad60-4d05-47b5-9a16-e11eaf858c25)

<br>
as we see, the steps didn't change because the number of nodes It is the same as before. and like DVRP part the min cost between 1 and 4 increased.
