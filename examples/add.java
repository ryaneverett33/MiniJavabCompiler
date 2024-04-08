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