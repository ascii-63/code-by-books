# Returning Error Information

## Figure 2-1. Overview of patterns for returning error information
![Overview of patterns for returning error information](./images/2-1.png)

## Patterns for returning error information
- **Return Status Code:** Use the Return Value of a function to return status information. 
Return a value that represents a specific status. 
Both of you as the callee and the caller must have a mutual understanding of what the value means.
- **Return Relevant Errors:** Only return error information to the caller if that information is relevant to the caller. 
Error information is only relevant to the caller if the caller can react to that information.
- **Special Return Value:** Use the Return Value of your function to return the data computed by the function. 
Reserve one or more special values to be returned if an error occurs.
- **Log Errors**: Use different channels to return error information that is relevant for
the calling code and error information that is relevant for the developer

## Tips:
1. **Define the numeric status identifiers in your API as an `enum` or by using `#define`.** 
Give the status identifiers a meaningful name and document their meaning with
comments. 
Make sure to name your status codes in a consistent way across your APIs.
```cpp
// Callee API providing status codes
typedef enum
{
    MINOR_ERROR,
    MAJOR_ERROR,
    OK
}ErrorCode;
ErrorCode func();

// Callee implementation providing status codes
ErrorCode func()
{
    if(minorErrorOccurs())
    {
        return MINOR_ERROR;
    }
    else if(majorErrorOccurs())
    {
        return MAJOR_ERROR;
    }
    else
    {
        return OK;
    }
}

// Caller’s code using status codes
ErrorCode status = func();
if(status == MAJOR_ERROR)
{
    /* abort program */
}
else if(status == MINOR_ERROR)
{
    /* handle error */
}
else if(status == OK)
{
    /* continue normal execution */
}


```

2. **Only return error information to the caller if that information is relevant to the caller.** 
Error information is only relevant to the caller if the caller can react to that information.
```cpp
//Caller’s code
ErrorCode status = func();
if(status == MAJOR_ERROR || status == UNKNOWN_ERROR)
{
    /* abort program */
}
else if(status == MINOR_ERROR)
{
    /* handle error */
}
else if(status == OK)
{
    /* continue normal execution*/
}

// API
typedef enum
{
    MINOR_ERROR,
    MAJOR_ERROR,
    UNKNOWN_ERROR,
    OK
}ErrorCode;
ErrorCode func();

//Implementation
ErrorCode func()
{
    if(minorErrorOccurs())
    {
        return MINOR_ERROR;
    }
    else if(majorErrorOccurs())
    {
        return MAJOR_ERROR;
    }
    else if(internalError1Occurs() || internalError2Occurs())
    {
        /*
        You return the same error information if internalError1Occurs or internal
        Error2Occurs because it is irrelevant to the caller which of the two
        implementation-specific errors occurs. The caller would react to both errors in
        the same way (in the preceding example, the reaction is to abort the program).
        */
        return UNKNOWN_ERROR;
    }
    else
    {
        return OK;
    }
}
```

3. **Use the Return Value of your function to return the data computed by the function. 
Reserve one or more special values to be returned if an error occurs.**
You have to make sure to document in the API which returned special value has which meaning. 
In some cases, a common convention settles which special values indicate errors.
```cpp
// Callee implementation
void* func()
{
    if(somethingGoesWrong())
    {
        return NULL;
    }
    else
    {
        return some_pointer;
    }
}

// Caller’s code
pointer = func();
if(pointer != NULL)
{
    /* operate on the pointer */
}
else
{
    /* handle error */
}
```

4. **Use different channels to provide error information that is relevant for 
the calling code and error information that is relevant for the developer.** 
For example, write debug error information into a log file and don’t return 
the detailed debug error information to the caller.

The C language comes with special
macros to get information about the current line number (`__LINE__`), the current
function (`__func__`), or the current file (`__FILE__`). 
The following code uses the `__func__` macro for logging:
```cpp
void someFunction()
{
    if(something_goes_wrong)
    {
        logInFile("something went wrong", ERROR_CODE, __func__);
    }
}
```
To get more detailed logging, you could even trace your function calls and log their return information. 
That makes it easier to reverse-engineer error situations with these logs, 
but of course that logging also introduces computational overhead. 
For tracing return values of your function calls, you can use the following code:
```cpp
#define RETURN(x)           \
do {                        \
    logInFile(__func__, x); \
    return x;               \
} while (0)

int soneFunction()
{
    RETURN(-1);
}
```

## Tricks:
1. **Multiline Macros**

By having a do/while loop around the statements in a macro, you can avoid problems like the one shown in the following code:
```cpp
#define MACRO(x)    \
x=1;                \
x=2;                \

if(x==0)
    MACRO(x)
```
The code does not use curly braces around its if body, and when reading the code
you might think that the thing in the macro is only executed in case `x==0`. 
But actually when the macro expands, you end up with the following code:
```cpp
if(x==0)
    x=1;
x=2;
```
The last line of the code is not inside the body of the if statement, which is not what was intended. 
To avoid problems like this one, it is a best practice to have a `do`/`while` loop around the statements in a macro.