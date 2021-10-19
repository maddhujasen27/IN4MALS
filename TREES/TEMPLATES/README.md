# TEMPLATES
> #### ***:warning: In the Code Screenshot or in the Writing, wherever it is written `pair`, please change it to `Pair` (P in capital letter)***
Templates are an important tool in C++ which is basically used to ***pass Data Type as arguements.***<br>
Let us Understand this with an example:-

<p align="center">
  <img src="https://github.com/maddhujasen27/IN4MALS/blob/main/TREES/TEMPLATES/ignore_pics/temp1.png" width="300"/>
</p>

In the above code, all variables are of datatype `int`, So if we need to create the same program for `double`or `float` datatype, we have to write the whole thing again.

> ### ***Alternative?***

We use ***TEMPLATE*** to counter this problem. To use TEMPLATE, we use the **Syntax**:<br>
`template <typename T>`

USAGE:


<p align="center">
  <img src="https://github.com/maddhujasen27/IN4MALS/blob/main/TREES/TEMPLATES/ignore_pics/temp2.png" width="300"/>
</p>

Basically, what all is need to be done is that, replace the datatypes with the `typename` variable, and pass the datatype as an arguement to the class for filling the template.
The method of implementing and excecuting the template and the `class Pair` in the `main` is described below.

<p align="center">
  <img src="https://github.com/maddhujasen27/IN4MALS/blob/main/TREES/TEMPLATES/ignore_pics/temp23.png" width="300"/>
</p>

Here , the line `Pair < int > P1` creates an Object `P1` with a datatype of `int` of class `Pair`.

> **Can we use 2 datatypes in pair?**

Of Course. we can definitely do that. Suppose there are two types of data, T and V.
`template <typename T, typename V>`

This creates a template using two kinds of DataType.

<p align="center">
  <img src="https://github.com/maddhujasen27/IN4MALS/blob/main/TREES/TEMPLATES/ignore_pics/tempDouble.png" width="300"/>
</p>

> **Lastly, can we make a triplet using the Pair class?**

Yes, we can form a triplet by using the Pair Class.<br>
`Pair< Pair <int, int>, int> P2`.

The structure, thus formed, is depicted in the picture given below.

<p align="center">
  <img src="https://github.com/maddhujasen27/IN4MALS/blob/main/TREES/TEMPLATES/ignore_pics/tempTriplet2.jpg" width="500"/>
</p>

By the statement `Pair< Pair <int, int>, int> P2`, we form `Pair` object `P2`, having datatype V as int, and datatype T as another `Pair` object, having int and int datatype.
### How can we set the data in P2?
In case of Y, we can set it directly by calling `setY()` function.<br>
`P2.setY(10);`<br>
**BUT**, In case of X, we cannot do that, the reason being that, variable x is actually another `Pair` object. In order to resolve this , *We need to create another `Pair` Object, and assign it to the x variable.*
The full code is written down in the figure below.
### How to get data from P2?
- For `y`, we can directly do it from `getY()` function.
- For `x`, we cannot do it from just one `getX()` function. Since we have made `x` as a pair object, we need to perform `getX()` and `getY()` in it too.
> ### The full illustration of triplet is given down below:-

<p align="center">
  <img src="https://github.com/maddhujasen27/IN4MALS/blob/main/TREES/TEMPLATES/ignore_pics/tempTriplet.jpg" width="500"/>
</p>

> #### The full code is depicted down below.
> 
<p align="center">
  <img src="https://github.com/maddhujasen27/IN4MALS/blob/main/TREES/TEMPLATES/ignore_pics/tempfinal.png" width="300"/>
</p>

> ### ***:telescope:Run the code in your editor and see if the output is as per expectation***

## Authors

- [@buffer-reader](https://www.github.com/buffer-reader)
