package CS284Homework.HW4;

// Yash Yagnik
// I plegde my honor that I have abided by the Stevens Honor System.
import org.junit.Test;
import org.junit.jupiter.api.BeforeEach;

import static org.junit.jupiter.api.Assertions.*;
public class JUNITtesting {


        private Treap<Integer> test = new Treap<Integer>();


        @BeforeEach
        public void setUp() {
            test = new Treap<>();
        }

        @Test
        public void testEmptyConstructor() {
            Treap<Integer> treap = new Treap<Integer>();
            assertNotNull(treap);
            System.out.println("Empty Constructor: Passed");
        }

        @Test
        public void testSeedConstructor() {
            long seed = 12345;
            Treap<Integer> treap = new Treap<Integer>(seed);
            assertNotNull(treap);
            System.out.println("Seed Constructor: Passed");
        }


        /**
         * test function for the add function without priority
         */
        @Test
        public void testAddwithoutPriority() {
            Treap<Integer> test = new Treap<Integer>();
            assertTrue(test.add(6));
            assertTrue(test.add(3));
            assertTrue(test.add(1));
            assertTrue(test.add(2));
            assertTrue(test.add(4));
            assertTrue(test.add(7));
            assertFalse(test.add(2));
            System.out.println("Add without priority: Passed");
        }

        /**
         * test function for the add function with priority
         */
        @Test
        public void testAdd() {
            Treap<Integer> test = new Treap<Integer>();
            assertTrue(test.add(4, 23));
            assertTrue(test.add(2, 31));
            assertTrue(test.add(6, 55));
            assertTrue(test.add(1, 19));
            assertTrue(test.add(3, 12));
            assertTrue(test.add(5, 53));
            assertTrue(test.add(7, 26));
            assertFalse(test.add(4, 77));
            System.out.println("Add with priority: Passed");
        }


        /**
         * test function for the delete function
         */
        @Test
        public void testDelete() {
            Treap<Integer> test = new Treap<Integer>();
            test.add(3, 19);
            test.add(2, 31);
            test.add(6, 70);
            test.add(9, 84);
            test.add(1, 12);
            test.add(5, 83);
            test.add(7, 26);
            assertFalse(test.delete(0));
            assertTrue(test.delete(2));
            assertTrue(test.delete(3));
            assertTrue(test.delete(1));
            assertTrue(test.delete(9));
            assertTrue(test.delete(5));
            assertTrue(test.delete(6));
            assertTrue(test.delete(7));
            System.out.println("Delete: Passed");
        }


        /**
         * test function for the find function
         */
        @Test
        public void testFind() {
            Treap<Integer> test = new Treap<Integer>();
            test.add(4, 9);
            test.add(5, 21);
            test.add(6, 70);
            test.add(9, 89);
            test.add(3, 76);
            test.add(2, 23);
            test.add(7, 26);
            assertFalse(test.find(99));
            assertTrue(test.find(7));
            assertTrue(test.find(2));
            assertTrue(test.find(3));
            assertTrue(test.find(5));
            assertTrue(test.find(4));
            assertTrue(test.find(6));
            assertTrue(test.find(9));
        }


        /**
         * test function for the toString function
         */
        @Test
        public void testToString() {
            Treap<Integer> test = new Treap<Integer>();
            test.add(4, 54);
            test.add(2, 93);
            test.add(6, 46);
            test.add(1, 12);
            test.add(3, 84);
            test.add(5, 82);
            test.add(7, 3);
            String expectedoutput = ("(key=2, priority=93)\n" +
                    " (key=1, priority=12)\n" +
                    "  null\n" +
                    "  null\n" +
                    " (key=3, priority=84)\n" +
                    "  null\n" +
                    "  (key=5, priority=82)\n" +
                    "   (key=4, priority=54)\n" +
                    "    null\n" +
                    "    null\n" +
                    "   (key=6, priority=46)\n" +
                    "    null\n" +
                    "    (key=7, priority=3)\n" +
                    "     null\n" +
                    "     null\n");
            assertEquals(expectedoutput, test.toString());
        }
}
