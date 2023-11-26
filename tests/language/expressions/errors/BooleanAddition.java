class Main {
    public static void main (String[] a) {
        System.out.print(new Test().run());
    }
}
class Test {
    public int run() {
        boolean b;
        // Main.java:9: error: bad operand types for binary operator '+'
        b = true + false;
        return -1;
    }
}