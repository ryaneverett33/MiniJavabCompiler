// From https://git.scc.kit.edu/IPDSnelting/mjtest-tests/-/blob/master/syntax/ElseOneBrace.invalid.mj?ref_type=heads
class Test {
    public void m() {
        if (x > y)
            return;
        else {
            return;
    }
}