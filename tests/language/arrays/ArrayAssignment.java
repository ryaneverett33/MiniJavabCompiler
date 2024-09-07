class MainClass {
    public static void main (String[] argv) {
        System.out.println(new Tester().Test());
    }
}

class Tester {
    public int Test() {
        int[][] multiArray;

        multiArray = new int[1][1];
        // should print 1,1
        System.out.println(multiArray.length)
        System.out.println(multiArray[0].length);

        multiArray[0] = new int[5];
        // should print 1,5
        System.out.println(multiArray.length)
        System.out.println(multiArray[0].length);

        multiArray[0][0] = 6;
        // should print 6
        System.out.println(multiArray[0][0]);

        multiArray = new int[5][5];
        // should print 5,5
        System.out.println(multiArray.length)
        System.out.println(multiArray[0].length);

        // should print 0
        System.out.println(multiArray[0][0]);

        return 0;
    }
}