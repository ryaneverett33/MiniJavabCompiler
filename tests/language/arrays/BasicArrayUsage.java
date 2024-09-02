class MainClass {
    public static void main (String[] argv) {
        System.out.println(new Tester().Test());
    }
}

class Tester {
    int[] GlobalA;
    int[][] GlobalB;

    public int Test() {
        this.TestLocal();
        this.TestGlobal();
        return 0;
    }

    public int TestLocal() {
        int[] localA;
        int[][] localB;

        localA = new int[5];
        localB = new int[5][5];
        System.out.println(localA.length);
        System.out.println(localB.length);
        System.out.println(localB[0].length);

        localA[0] = 15;
        System.out.println(localA[0])
        return localA[0];
    }
    public int TestGlobal() {
        GlobalA = new int[5];
        GlobalB = new int[5][5];
        System.out.println(GlobalA.length);
        System.out.println(GlobalA.length);
        System.out.println(GlobalB[0].length);

        GlobalA[0] = 15;
        System.out.println(GlobalA[0])
        return GlobalB[0];
    }
}