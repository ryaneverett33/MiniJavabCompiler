IR language

# Instructions

## Control Flow Instructions

- ret <type> || ret <type> <value> || ret <type> <immediate> -> void
- br <label> -> void
- call <type> <function> (<typed args>) -> <function type>
- br_if <label> -> void

## Binary Operations

- add <type> <value>, <type> {<value> || <immediate>} -> <type>
- sub <type> <value>, <type> {<value> || <immediate>} -> <type>
- mul <type> <value>, <type> {<value> || <immediate>} -> <type>
- div <type> <value>, <type> {<value> || <immediate>} -> <type>
- or  <type> <value>, <type> {<value> || <immediate>} -> <type>
- and <type> <value>, <type> {<value> || <immediate>} -> <type>

## Memory Operations

- alloc <type> -> <type*>
- load <type> <value> -> <type>
- store <type> {<value> || <immediate>}, <arg> -> void
- getptr <type*> <value>, {<immediate> || <arg>} -> <type*>
- cmp <operator>, <value>, {<value> || <immediate>} -> bool

# Intrinsics

- mj.println vector<i32>* <arg> -> void
- mj.factorial <arg> -> i32

# Types

- i8
- i32
- bool
- void
- vector<T>

# Examples

```
module "adder.java"

func i32 @add(i32 %0, i32 %1):
entry:
	%2 = add i32 %0, %1
	ret i32 %2
```

```
module "printIfTrue.java"
%testClass = type { i32, bool }

@".str.1" = vector<i32> "Test Passed!\00"
@".str.2" = vector<i32> "Test Failed!\00"

func void @printIfTrue(%testClass* %self):
entry:
	%self.local = alloc %testClass*
	store %testClass* %self, %testClass** %self.local
	%0 = load %testClass* %self.local
	%1 = getptr bool* %0, 1
	%2 = load bool %1
	%3 = cmp eq, bool %2, bool true
	br_if %label1
	br %label2
label1:
	%4 = getptr vector<i32>* @.str.1, 0
	call void @mj.println(vector<i32>* %4)
	br %exit
label2:
	%5 = getptr vector<i32>* @.str.2, 0
	call void @mj.println(vector<i32>* %5)
	br %exit
exit:
	ret void
```