// from https://git.scc.kit.edu/IPDSnelting/mjtest-tests/-/blob/master/semantic/ArgsOtherScope.valid.mj?ref_type=heads
class c {
    public static void main(String[] args) {
        d obj = new d();
        obj.args = 0;
        obj.args(obj.args);
    }
}

class d {
    public int args;
    public void args(int args) { }
}
