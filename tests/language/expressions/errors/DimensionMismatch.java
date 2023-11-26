class Main {
    public static void main (String[] a) {
        System.out.print(new Test().run());
    }
}
class Test {
    int[][] arr;
    public int run() {
        // Main.java:9: error: incompatible types: int[] cannot be converted to int[][]
        arr = new int[5];
        return -1;
    }
}