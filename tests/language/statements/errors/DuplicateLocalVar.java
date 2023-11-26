// From https://git.scc.kit.edu/IPDSnelting/mjtest-tests/-/blob/master/semantic/DuplicateLocalVarInIf.invalid.mj?ref_type=heads
class c {
    public static void main(String[] args) {}
}

class a {
    public void m() {
        int i;
        if (false) {
            int i;
            i = 0;
        }
    }
}