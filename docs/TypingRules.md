# Type Reduction and Acceptance Rules

This document describes the typing rules for the MiniJava♭ programming language; specifically the reduction rules for expressions and acceptance rules for statements.

# Primitive Types

- Integer
- Boolean

# Complex Types

- Object
- Array

# Non-reducible Types

- Void
- Method ??

# Type reductions

## Unary expressions

| Operator | Type    | Reduction |
|----------|---------|-----------|
| `+`      | Integer | Integer   |
| `-`      | Integer | Integer   |
| `!`      | Boolean | Boolean   |

### Examples

```java
+5;      // Integer -> Integer
-5;      // Integer -> Integer
!5;      // Integer -> Integer
!true;   // Boolean -> Boolean
```

## Binary expressions

| Operator | TypeA   | TypeB   | Reduction |
|----------|---------|---------|-----------|
| `&&`     | Boolean | Boolean | Boolean   |
| `\|\|`   | Boolean | Boolean | Boolean   |
| `!=`     | Boolean | Boolean | Boolean   |
|          | Integer | Integer | Integer   |
| `<=`     | Integer | Integer | Integer   |
| `>=`     | Integer | Integer | Integer   |
| `<`      | Integer | Integer | Integer   |
| `>`      | Integer | Integer | Integer   |
| `+`      | Integer | Integer | Integer   |
| `-`      | Integer | Integer | Integer   |
| `*`      | Integer | Integer | Integer   |
| `/`      | Integer | Integer | Integer   |

### Examples

```java
true && false;  // Boolean, Boolean -> Boolean
true || false;  // Boolean, Boolean -> Boolean
true != false;  // Boolean, Boolean -> Boolean
5 != 6;         // Integer, Integer -> Boolean
5 <= 6;         // Integer, Integer -> Boolean
5 >= 6;         // Integer, Integer -> Boolean
5 < 6;          // Integer, Integer -> Integer
5 > 6;          // Integer, Integer -> Integer
5 + 5;          // Integer, Integer -> Integer
5 - 5;          // Integer, Integer -> Integer
5 * 5;          // Integer, Integer -> Integer
5 / 5;          // Integer, Integer -> Integer
```

## `.length` expressions

| Type   | Reduction |
|--------|-----------|
| String | Integer   |
| Array  | Integer   |

### Examples

```java
"hello".length; // String -> Integer
arr.length;     // Array -> Integer
```

## Literal expressions

| Type    | Reduction |
|---------|-----------|
| String  | String    |
| Integer | Integer   |
| Boolean | Boolean   |

## Indexed expressions

Indexed expressions accept Array types and resolve to either another Array or a singular type.

If the dimensions of the indexed expression match the dimensions of the array type, the singular type is reduced.

```java
int[] arr;     // Type: Array[Integer]
return arr[0]; // Type: Integer
```

If the dimensions of the indexed expression are less than the dimensions of the array type, an array type is reduced.

```java
int[][] arr;   // Type: Array[Integer][Integer]
return arr[0]; // Type: Array[Integer]
```

## Method Call expressions

Method call expressions reduce to the method type itself.

```java
int get() {     // Type: Integer
    return 5;
}

return get();   // Type: Integer
```

## Nested expressions

A nested expression reduces to its interior type.

```java
return (5);     // Type: Integer
```

## Object expressions


| Expression     | Reduction |
|----------------|-----------|
| `new Object`   | Object    |
| `new Object[]` | Array     |
| `object`       | Object    |
| `this`         | Object    |

### Examples

```java
new Blah();     // -> Object
new Blah[5];    // -> Array
return b;       // -> Object
return this;    // -> Object
```

# Statement Acceptance Rules

## Print Statement

| Statement          | Accepted Type |
|--------------------|---------------|
| System.out.print   | String        |
|                    | Integer       |
| System.out.println | String        |
|                    | Integer       |

## Return Statement

A return statement accepts its method type.

```java
int doThing()   // Type: Integer
{
    return 5;   // Accepted Type: Integer
}
```

## Nested Statement

A nested statement accepts any type.

```java
int doThing()
{
    {
        {
            {
                System.out.println("blah");
            }
        }
    }
}
```

## While Statement

A while statement accepts a `Boolean` in its conditional and any type in its body.

```java
while (true)   // Accepted Type: Boolean
{
    System.out.println("help i'm stuck in a fortune cookie factory");
}
```

## If Statement

An if statement accepts a `Boolean` in its conditional and any type in its body blocks.

```java
if (1 + 1 == 2) // Accepted Type: Boolean
{
    System.out.println("everythingisokay");
}
else 
{
    System.out.println("sweetbolognano");
}
```

## Assignment Statement

An assignment statement accepts its variable type.

```java
int a;   // Type: Integer
a = 5;   // Accepted Type: Integer
```