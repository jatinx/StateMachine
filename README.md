# Linear State Machine
Implements a State Machine in C++
A workflow that simulates a step by step modification on a data, which can be flexible, reversible and supports Async execution.

# How to use StateMachine in your code
StateMachine uses states to describe a pipeline. A state can be thought of as a step in a pipeline.
Each state has the functions described below:
 - init : initialize step of each state
 - process : actual work of the state
 - exit : clean up after the state is done processing

 These functions use a bool value to show if an error has occured (true meaning no error).
 If error does occur, state has a function called `error` which will be executed, inorder to handle any error.
 

 To make your your own state inherit `States::State` class. `process` function is the only one which is mandatory, rest all are optional to implement.

 
 After declaring custom states, create a StateMachine object via `States::StateMachine` class, constructor takes an optional input to describe if the execution will be `sync` or `async`.
 The data which needs to be transformed needs to be cast as void* and to be set in `States::StateMachine` object via `setData`.
 Start the execution by calling the function `run`.

 ## Sample
 ```cpp
 class SampleState : public States::State{
    ...
   public:
    bool process(void *data) override { ... } 
 };
 ```

 # Disclaimer
 This is a very much work in progress. Please feel free to tinker with it, open a bug, raise a pull request.