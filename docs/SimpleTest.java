class TestCase {
    public int NumberInSuite;
    public boolean Result;
    public boolean HasRun;
    public void RunTest();
    public boolean HasRunTest();
}

class SimpleTest extends TestCase {
    public void RunTest();
}