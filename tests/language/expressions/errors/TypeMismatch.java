class Main {
    public static void main (String[] a) {
        System.out.print(new Test().run());
    }
}
class Test {
    int[][] arr;
    public int run() {
        // Main.java:9: error: incompatible types: boolean[][] cannot be converted to int[][]
        arr = new boolean[5][5];
        return -1;
    }
}