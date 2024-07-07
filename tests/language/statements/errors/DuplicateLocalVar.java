// From https://git.scc.kit.edu/IPDSnelting/mjtest-tests/-/blob/master/semantic/DuplicateLocalVarInIf.invalid.mj?ref_type=heads
class c {
    public static void main(String[] args) {
        {}
    }
}

class a {
    public int m() {
        int i;
        int i;

        i = 1;
        return i;
    }
}