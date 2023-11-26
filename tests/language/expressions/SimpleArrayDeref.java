// From https://git.scc.kit.edu/IPDSnelting/mjtest-tests/-/blob/master/compile-only/UbSimpleArrayDeref.mj?ref_type=heads
class UbSimpleArrayDeref {
    public static void main(String[] main) {
        // will result in runtime error
        int p = (new int[33][])[0][3];
        System.out.println(p);
    }
}