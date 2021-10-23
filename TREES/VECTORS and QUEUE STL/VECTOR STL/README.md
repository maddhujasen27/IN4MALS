# VECTORS

Since we have already learnt about arrays, Lets move on to `vector`. 
> `vector` is nothing but a sort of *Dynamic array*.
The main point to note is that, once the `vector` is full, it automatically doubles up its previous size. We will learn that later.

#### Implementation of `vector`.
`#include<iostream>` <br>
`#include<vector>` <br>
`int main()` <br>
`{` <br>
  `vector<int> v; \\this is for static allocation` <br>
  `vector<int> *v = new vector<int>(); \\this is for dynamic allocation`   <br>
`}` <br>

We will only be using the static memory allocation method in this section.

##### Inserting elements
*Function* :- `push_back(element);`<br>
For example:-<br>
`int main()`<br>
`{`<br>
`vector<int> v;`<br>
`v.push_back(10);`<br>
`v.push_back(20);`<br>
`}`<br>

By this code, we make a `vector` v, having 2 elements- 0th position= 10 and 1st position=20.

### Some important things to keep in mind~
- We can modify the vector values by using bracket notation. For example, <br>
 `int main()`<br>
`{`<br>
`vector<int> v;`<br>
`v.push_back(10);`<br>
`v.push_back(20);`<br>
`v[1]=30;`<br>
`}`<br>

In this code, initially, `vector` v has `[10|20]` , but after `v[1]=30;`, it modifies the value at 1st position and changes to 30. Hence the final value of v is  `[10|30]`

- We can print the elements of vector using ***bracket notation*** in the same way as we print an array.

- ***Do not use bracket notation([]) for inserting in a vector. Why?? lets see***

In the table below, I have written the code and the respective expected operation happening in the background.<br>
|Line of code|Expected processing|
|---|---|
|v.push_back(10)|[10]|
|v.push_back(20)|[10,20]|
|v.push_back(30)|[10,20,30]|
|v[1]=100|[10,100,30]|
|v[3]=1002|[10,100,30,1002]|
|v[4]=1234|[10,100,30,1002,1234]|
|v.push_back(23)|[10,100,30.1002,1234,23]|

 When we print the datas from v[0]-v[5], we EXPECT:<br>

|postion|value|
|---|---|
|v[0]|10|
|v[1]|100|
|v[2]|30|
|v[3]|1002|
|v[4]|1234|
|v[5]|23|

***But we are wrong! Thats not what actually happens*** <br>
|Line of code|Actual processing|
|---|---|
|v.push_back(10)|[10]|
|v.push_back(20)|[10,20]|
|v.push_back(30)|[10,20,30]|
|v[1]=100|[10,100,30]|
|**v[3]=1002**|**[10,100,30] since there is no 3 position, it Won't do anything**|
|**v[4]=1234**|**[10,100,30] Same here**|
|**v.push_back(23)**|**[10,100,30,23]**|

So When we print the datas from v[0]-v[5], **WE GET**:<br>

|postion|value|
|---|---|
|v[0]|10|
|v[1]|100|
|v[2]|30|
|v[3]|23|
|v[4]|garbe value|
|v[5]|garbage value|

> :smile: Hope everythings clear upto now! :smile:

- **`v.size()` function is used to return the size of the array.*** In the above example, it would return **4** .
See above. In the above example, when we do `cout<<v[4]` or `cout<<v[5]` , It returns us a garbage value, since nothing is present there. ***A better aletrnative to this is to use `v.at(postion) function`*** <br>
Now, usingg the `at()` function, if we want to print the `vector` elements:-<br>
`for(int i=0;i<=v.size();i++)`<br>
`{`<br>
`cout<<v.at(i)<<" ";`<br>
`}`<br>

It would print:- 10 100 30 23

If we try to do **`v.at(5)`** , instead of giving a garbage value, it will return **OUT OF RANGE** exception.<br>

> ***Hence we can safely conclude that using `.at()` function is much suitavle than using the [] notation***

- Function ***`pop_back()`*** removes the last element of the vector. For example, after using `v.pop_back()`, v will become [10,100,30]

> #### :face_with_spiral_eyes: We have almost reached the end. Just 1 more function  :tired_face:

- **`.capacity()`** function:-
While `.size()` function returns the number of elements in the vector, `.capacity()` function returns the actually capacity of the vector
Confused?? Run this code in your editor!	:space_invader:<br>
<br>
for(int i=0;i<100;i++)
{
cout<<v.capacity()<<" "<<v.size()<<endl;
v.push_back(i);
}
***OUTPUT***
|capacity|size|
|---|---|
|0|0|
|1|1|
|2|2|
|4|3|
|4|4|
|8|5|
|8|6|
|8|7|
|8|8|
|16|9|
|16|10|

and so on.....

Try to understand the trend first by your own!
Figured out!
> ***HINT:- see in the beginning of the section, i have mentioned that once the vector is full, it doubles up its size***
#### Solution
1. no element, size and capacity 0
2. 1 element inserted, 1 size and 1 capacity
3. since vector is full, it will double up the size, ie Capacity x 2 occurs(1*2=2). 2nd element inserted, size 2.
4. since vector is full, it will double up the size, ie Capacity x 2 occurs(2*2=4). 3rd element insrted, size 3.
5. 4th element inserted, size and capacity=4.
6. since vector is full, it will double up the size, ie Capacity x 2 occurs(4*2=8).5th element inserted, size 5.
 and so on...
 
> ## Well, we have reached the end. If I have missed any Important function, make sure to add it by calling a pull request. ***Signing off*** :smile_cat:

## Authors

- [@buffer-reader](https://www.github.com/buffer-reader)









