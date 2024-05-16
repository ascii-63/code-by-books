# Memory Management

## Figure 3-1. Overview of patterns for memory management
![Overview of patterns for memory management](./images/3-1.png)

## Patterns for memory management
- **Stack First:** Deciding the storage class and memory section (stack, heap, …) for variables is a decision every programmer has to make often. 
It gets exhausting if for each and every variable, the pros and cons of all possible alternatives have to be considered in detail.
Therefore, simply **put your variables on the stack by default to profit from automatic cleanup of stack variables**.
- **Eternal Memory:** Holding large amounts of data and transporting it between function calls is difficult because you have to
make sure that the memory for the data is large enough and that the lifetime extends across your function calls. 
Therefore, **put your data into memory that is available throughout the whole lifetime of your program.**
- **Lazy Cleanup:** Having dynamic memory is required if you need large amounts of memory and memory where you don’t know the required size beforehand. 
However, handling cleanup of dynamic memory is a hassle and is the source of many programming errors. 
Therefore, **allocate dynamic memory and let the operating system cope with deallocation by the end of your program.**
- **Dedicated Ownership:** The great power of using dynamic memory comes with the great responsibility of having to properly clean that memory up. 
In larger programs, it becomes difficult to make sure that all dynamic memory is cleaned up properly. 
Therefore, right at the time **when you implement memory allocation, clearly define and
document where it’s going to be cleaned up and who is going to do that.**
- **Allocation Wrapper:** Each allocation of dynamic memory might fail, so you should check allocations in your code to react accordingly. 
This is cumbersome because you have many places for such checks in your code. 
Therefore, **wrap the allocation and deallocation calls, and implement error handling or 
additional memory management organization in these wrapper functions.**
- **Pointer Check:** Programming errors that lead to accessing an invalid pointer cause uncontrolled program behavior, and
such errors are difficult to debug. However, because your code works with pointers frequently, there is a
good chance that you have introduced such programming errors. Therefore, **explicitly invalidate
uninitialized or freed pointers and always check pointers for validity before accessing them.**
- **Memory Pool:** Frequently allocating and deallocating objects from the heap leads to memory fragmentation. 
Therefore, **hold a large piece of memory throughout the whole lifetime of your program. 
At runtime, retrieve fixed-size chunks of that memory pool instead of directly allocating new memory from the heap.**

## Data Storage and Problems with Dynamic Memory

### Data Storage:
- **Stack:** The stack is a **fixed-size memory** reserved for each thread (**allocated when creating the thread**). 
When calling a function in such a thread, a block on the top of the stack is reserved for the function parameters
and automatic variables used by that function. 
**After the function call, that memory is automatically cleaned up.** 
To put data on the stack, simply declare variables in the functions where they are used. 
These variables can be accessed as long as they don’t run out of scope (when the function block ends)
```cpp
void main()
{
    int my_data;
}
```

- **Static memory:** The static memory is a **fixed-size memory** in which the allocation logic is fixed at compile time. 
To use the static memory, simply place the `static` keyword in front of your variable declaration. 
Such variables are **available throughout the whole lifetime of your program.** 
The same holds true for global variables, even without the `static` keyword:
```cpp
int my_global_data;
static int my_fileglobal_data;
void main()
{
    static int my_local_data;
}
```

- If your data is of **fixed size and immutable**, you can simply store it directly in the static memory where the code is stored. 
Quite often, fixed string values are stored this way. Such data is **available throughout the whole lifetime of your program** 
(even though, in the example below, the pointer to that data runs out of scope):
```cpp
void main()
{
    char* my_string = "Hello World";
}
```

- **Heap:** You can allocate dynamic memory on the heap to store the data. 
The heap is a global memory pool **available for all processes on the system**, and it is up to the
programmer to allocate and deallocate from that pool at any time:
```cpp
void main()
{
    void* my_data = malloc(1000);
    /* work with the allocated 1000 byte memory */
    free(my_data);
}
```

### Dynamic Memory Problems:
- **Memory leak:** If that happens frequently and your applications runs for a long time, you’ll end up having no additional memory.
- **Freeing memory more than once** is a problem and can lead to undefined program behavior.
- **Dangling pointer**: Trying to access freed memory is a problem as well. 
It is easy to free some memory and then later on make a mistake and dereference a pointer to that memory.
- You have to **cope with lifetime and ownership of allocated data.** You have to know who cleans up which data when. 
Because C don’t have destructors. We are not notified when a pointer runs out of scope and the memory should be cleaned up.
