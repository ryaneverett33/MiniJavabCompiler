class Adder {
    public static void main (String[] args) {
        System.out.println(new Math().add());
    }
}

class Math {
    public int add() {
        int x;
        int y;

        x = 1;
        y = 2;
        x = x + y;
        return x;
    }
}
// Math_add()
// entry:
//      %x = alloc i32
//      %y = alloc i32
//      store i32 1, i32* %x
//      store i32 2, i32* %y
//      %2 = load i32, i32* %x
//      %3 = load i32, i32* %y
//      %4 = add i32, i32 %2, i32 %3
//      store i32 %4, i32* %x
//      %5 = load i32, i32* %x
//      ret i32 %5