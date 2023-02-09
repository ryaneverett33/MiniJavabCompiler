class WhileLoop {
    public static void main(String[] args) {
        System.out.println(new Test().test());
    }
}
class Test {
    int i;
    public int test() {
        i = 0;
        if (i == 0) {
            i = i + 1;
            if (((i) * 2) == (-1 * (-1))) {
                return 1;
            }
            else {}
        }
        else {
            return -1;
        }
        return 0;
    }
}